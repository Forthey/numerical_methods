import numpy as np
import copy

import grpc
from grpc_files.main_pb2_grpc import *
import grpc_files.main_pb2 as pb
import tab_func as tf

X_COUNT = 10000


class Point:
    x: float
    y: float

    def __init__(self, x: float, y: float) -> None:
        self.x = x
        self.y = y


class Spline:
    spline_base_points: list[Point] = list()
    spline_points: list[Point] = list()

    def __init__(self, spline_base_points=None, spline_points=None) -> None:
        if spline_points is None:
            spline_points = list()
        if spline_base_points is None:
            spline_base_points = list()
        self.spline_base_points = spline_base_points
        self.spline_points = spline_points

    def __copy__(self):
        return type(self)(self.spline_base_points.copy(), self.spline_points.copy())


def send(func_id: int, left: float, right: float,
         exp_cnt: int, exp_min: int, exp_step: int) -> list[Spline]:
    request = pb.TabFuncs()

    for i in range(exp_cnt):
        points_cnt = exp_min + exp_step * i
        x = np.linspace(left, right, points_cnt)
        y: np.ndarray

        if func_id == 1:
            y = tf.func_1(x)
        else:
            y = tf.func_2(x)

        tab_func = request.tab_funcs.add()
        tab_func.expand_to = X_COUNT
        for j in range(len(x)):
            point = tab_func.points.add()
            point.x = float(x[j])
            point.y = float(y[j])

    splines: list[Spline] = list()
    i = 0

    with grpc.insecure_channel("localhost:4040") as channel:
        stub = ComputeSplineStub(channel)

        print(f"Send to evaluate {len(request.tab_funcs)} tab funcs")

        for response in stub.Evaluate(request):
            if response == grpc.aio.EOF:
                break
            print(f"Receive {len(response.base_points)}-root spline")
            splines.append(Spline())

            for point in response.points:
                splines[i].spline_points.append(Point(point.x, point.y))
            for base_point in response.base_points:
                splines[i].spline_base_points.append(Point(base_point.x, base_point.y))

            print(f"Parse a {len(splines[i].spline_base_points)}-{len(splines[i].spline_points)}-point spline")
            i += 1

    print(f"Parse {len(splines)} splines")
    return splines
