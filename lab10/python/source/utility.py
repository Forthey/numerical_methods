from pydantic import BaseModel

from grpc_files.main_pb2_grpc import *
import grpc_files.main_pb2 as pb


class Requirements(BaseModel):
    a: float
    b: float
    epsilon: float


class CalcResult(BaseModel):
    value: float
    iter_cnt: int
    h: float
    requirements: Requirements


def generate_requirements(request: list[pb.Requirements]) -> pb.Requirements:
    for sub_request in request:
        yield sub_request


def send(request: list[Requirements]) -> list[CalcResult]:

    grpc_request: list[pb.Requirements] = [pb.Requirements(**sub_req.model_dump()) for sub_req in request]

    calc_results: list[CalcResult] = []

    with grpc.insecure_channel("localhost:4040") as channel:
        stub = EvaluateIntegralStub(channel)

        print(f"Sending {len(grpc_request)} to calculate")

        i = 0
        for response in stub.Evaluate(generate_requirements(grpc_request)):
            if response == grpc.aio.EOF:
                break

            calc_results.append(CalcResult(
                value=response.value,
                iter_cnt=response.iter_cnt,
                h=response.h,
                requirements=request[i]
            ))
            i += 1

    print(f"Receive {len(calc_results)} to analyze")
    return calc_results
