import random
import matplotlib.pyplot as plot
import numpy as np

from grpc_files.main_pb2_grpc import *
import grpc_files.main_pb2 as pb
import tab_func as tf
import utility as util

EXP_CNT = 20
POINTS_CNT = 20

basic_perturbations = [0.01, 0.02, 0.03, 0.04, 0.05]
exp_num_for_perturbation = 20
perturbations = list()


def send_for_dop(func_id: int, left: float, right: float) -> list[util.Spline]:
    request = pb.TabFuncs()

    for max_perturbation in basic_perturbations:
        for i in range(EXP_CNT):
            max_perturbation = max_perturbation

            points_cnt = POINTS_CNT
            x = np.linspace(left, right, points_cnt)
            y: list[float] = list()

            avg_perturbation: float = 0
            for j in range(len(x)):

                perturbation = random.random() * max_perturbation
                avg_perturbation += abs(perturbation)
                if func_id == 1:
                    y.append(tf.func_1(x[j]) * (1 + perturbation))
                else:
                    y.append(tf.func_2(x[j]) * (1 + perturbation))
            avg_perturbation = avg_perturbation / len(x)
            perturbations.append(avg_perturbation)

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


def print_perturbation(splines: list[util.Spline], func: callable, func_as_str: str):
    plot.xlim(0, 0.06)
    plot.title(f"Возмущение данных для {func_as_str}")
    plot.xlabel("Возмущение")
    plot.ylabel("Относительная ошибка")

    for i in range(len(basic_perturbations)):
        max_errors: list[float] = list()
        for j in range(len(splines)):
            if perturbations[j] > basic_perturbations[i] or \
                    (i > 0 and perturbations[j] > basic_perturbations[i - 1]):
                continue

            max_error: float = 0
            for point in splines[j].spline_points:
                if point.x > splines[i].spline_base_points[len(splines[i].spline_base_points) - 1].x:
                    continue
                error: float = abs((func(point.x) - point.y) / point.y)
                if error > max_error:
                    max_error = error

            max_errors.append(max_error)

        plot.boxplot(max_errors, positions=[int(basic_perturbations[i] * 1000) / 1000], widths=0.003, showfliers=False)

    plot.show()


def analyze(func_id: int, splines: list[util.Spline]):
    if func_id == 1:
        print_perturbation(splines, tf.func_1, tf.func_1_str())
    else:
        print_perturbation(splines, tf.func_2, tf.func_2_str())
    perturbations.clear()
