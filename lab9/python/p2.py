import tab_func as tf
import utility as util
import matplotlib.pyplot as plot
import numpy as np


def print_func_and_splines(splines: list[util.Spline], func: callable, func_as_str: str) -> None:
    plot.title(f"{func_as_str} и {len(splines)} сплайна")
    plot.xlabel("x")
    plot.ylabel("y")

    colors = ["red", "blue", "green", "yellow"]
    max_x: list[float] = list()

    for i in range(len(splines)):
        spline = splines[i]

        spline_x: list[float] = list()
        spline_y: list[float] = list()
        spline_base_x: list[float] = list()
        spline_base_y: list[float] = list()

        for point in spline.spline_points:
            spline_x.append(point.x)
            spline_y.append(point.y)

        for base_point in spline.spline_base_points:
            spline_base_x.append(base_point.x)
            spline_base_y.append(base_point.y)

        if len(spline_x) > len(max_x):
            max_x = spline_x

        plot.plot(spline_x, spline_y, label=f"Сплайн от {len(spline.spline_base_points)} узлов", color=colors[i])
        plot.plot(spline_base_x, spline_base_y, linestyle="none", marker=".", color=colors[i])

    y: list[float] = list()
    for i in range(len(max_x)):
        y.append(func(max_x[i]))

    plot.plot(max_x, y, label=func_as_str)
    plot.legend()
    plot.show()


def print_error(splines: list[util.Spline], func: callable, func_as_str: str) -> None:
    plot.title(f"Ошибка для {func_as_str} и {len(splines)} сплайнов")
    plot.xlabel("x")
    plot.ylabel("y")
    for spline in splines:
        x: list[float] = list()
        dy: list[float] = list()
        for point in spline.spline_points:
            x.append(point.x)
            dy.append(abs(func(point.x) - point.y))

        plot.plot(x, dy, label=f"Ошибка для сплайна от {len(spline.spline_base_points)} узлов")

    plot.legend()
    plot.show()


def analyze(func_id: int, splines: list[util.Spline]):

    if func_id == 1:
        print_func_and_splines(splines, tf.func_1, tf.func_1_str())
        print_error(splines, tf.func_1, tf.func_1_str())
    else:
        print_func_and_splines(splines, tf.func_2, tf.func_2_str())
        print_error(splines, tf.func_2, tf.func_2_str())
