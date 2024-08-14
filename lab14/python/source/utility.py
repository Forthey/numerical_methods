from pydantic import BaseModel

from grpc_files.main_pb2_grpc import *
import grpc_files.main_pb2 as pb


class Vector2(BaseModel):
    y: float
    dy: float


class Requirements(BaseModel):
    a: float
    b: float
    homo_cauchy: Vector2
    cauchy: Vector2
    epsilon: float


class RequirementsConst(BaseModel):
    a: float
    b: float
    homo_cauchy: Vector2
    cauchy: Vector2
    h0: float


class Point(BaseModel):
    x: float
    y: float


class TabFunc(BaseModel):
    points: list[Point] = list()
    h0: float


class TabFuncWithH(BaseModel):
    points: list[Point] = list()
    h: list[float] = list()
    epsilon: float


def generate_requirements[Type](request: list[Type]) -> Type:
    for sub_request in request:
        yield sub_request


def send(request: list[Requirements]) -> list[TabFuncWithH]:

    grpc_request: list[pb.Requirements] = [pb.Requirements(**sub_req.model_dump()) for sub_req in request]

    tab_funcs: list[TabFuncWithH] = []

    with grpc.insecure_channel("localhost:4040") as channel:
        stub = EvaluateBoundaryStub(channel)

        print(f"Sending {len(grpc_request)} to calculate")

        i = 0
        for response in stub.Evaluate(generate_requirements(grpc_request)):
            if response == grpc.aio.EOF:
                break

            points: list[Point] = []
            for point in response.points:
                points.append(Point(x=point.x, y=point.y))
            tab_funcs.append(TabFuncWithH(
                points=points,
                h=[*response.h],
                epsilon=grpc_request[i].epsilon
            ))
            i += 1

    print(f"Receive {len(tab_funcs)} to analyze")
    return tab_funcs


def send_const(request: list[RequirementsConst]) -> list[TabFunc]:
    grpc_request: list[pb.RequirementsConst] = [pb.RequirementsConst(**sub_req.model_dump()) for sub_req in request]

    tab_funcs: list[TabFunc] = []

    with grpc.insecure_channel("localhost:4040") as channel:
        stub = EvaluateBoundaryStub(channel)

        print(f"Sending {len(grpc_request)} to calculate")

        i = 0
        for response in stub.EvaluateConst(generate_requirements(grpc_request)):
            if response == grpc.aio.EOF:
                break

            points: list[Point] = []
            for point in response.points:
                points.append(Point(x=point.x, y=point.y))
            tab_funcs.append(TabFunc(
                points=points,
                h0=grpc_request[i].h0
            ))
            i += 1

    print(f"Receive {len(tab_funcs)} to analyze")
    return tab_funcs
