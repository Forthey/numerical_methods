import matplotlib.pyplot as plot
import numpy as np

from grpc_files.main_pb2_grpc import *
import grpc_files.main_pb2 as pb
import tab_func as tf
import utility as util


point_offsets: list[float] = list()
real_skip_root: util.Point = util.Point(0.0, 0.0)


def send_for_4(func_id: int, left: float, right: float, exp_num: int, points_cnt: int, step: float) -> list[util.Spline]:
    request = pb.TabFuncs()

    x = np.linspace(left, right, points_cnt)
    y: list[float] = list()

    for j in range(len(x)):
        if func_id == 1:
            y.append(tf.func_1(x[j]))
        else:
            y.append(tf.func_2(x[j]))

    real_skip_root.x = x[1]
    real_skip_root.y = y[1]


    for i in range(exp_num):
        offset: float = real_skip_root.y + (i - exp_num / 2) * step
        y[1] = offset
        point_offsets.append(offset)

        tab_func = request.tab_funcs.add()
        tab_func.expand_to = util.X_COUNT
        for j in range(len(x)):
            point = tab_func.points.add()
            point.x = float(x[j])
            point.y = float(y[j])

    splines: list[util.Spline] = list()
    i = 0

    with grpc.insecure_channel("localhost:4040") as channel:
        stub = ComputeSplineStub(channel)

        print(f"Send to evaluate {len(request.tab_funcs)} tab funcs")

        for response in stub.Evaluate(request):
            if response == grpc.aio.EOF:
                break
            print(f"Receive {len(response.base_points)}-root spline")
            splines.append(util.Spline())

            for point in response.points:
                splines[i].spline_points.append(util.Point(point.x, point.y))
            for base_point in response.base_points:
                splines[i].spline_base_points.append(util.Point(base_point.x, base_point.y))

            print(f"Parse a {len(splines[i].spline_base_points)}-{len(splines[i].spline_points)}-point spline")
            i += 1

    print(f"Parse {len(splines)} splines")
    return splines


def print_max_error(splines: list[util.Spline], func: callable, func_as_str: str):
    max_errors: list[float] = list()

    for spline in splines:
        max_error: float = 0
        for point in spline.spline_points:
            if point.x > spline.spline_base_points[len(spline.spline_base_points) - 1].x:
                continue
            error: float = abs(func(point.x) - point.y)
            if error > max_error:
                max_error = error

        max_errors.append(max_error)

    plot.title(f"Макс ошибка для {func_as_str}")
    plot.xlabel("Значение в пропадающем узле")
    plot.ylabel("Ошибка")
    plot.plot(point_offsets, max_errors, marker=".")
    #plot.plot(real_skip_root.y, 0, linestyle="none", marker=".")
    plot.show()

    point_offsets.clear()


def analyze(func_id: int, splines: list[util.Spline]):
    if func_id == 1:
        print_max_error(splines, tf.func_1, tf.func_1_str())
    else:
        print_max_error(splines, tf.func_2, tf.func_2_str())
