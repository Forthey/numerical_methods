import math

import numpy as np
from matplotlib import pyplot as plot
from sympy import expand, abc

import analyze.tab_func as tf
import analyze.utility as util


def get_error_y(x: np.ndarray | float, mn: float, n: int, grid: list[float]) -> np.ndarray | float:
    root_poly = abc.x / abc.x

    for grid_x in grid:
        root_poly *= (abc.x - grid_x)

    root_poly = expand(root_poly)

    y: list[float] = list()

    for cur_x in x:
        cur_y = root_poly.evalf(subs={abc.x: cur_x})
        y.append(abs(cur_y))

    result = mn / math.factorial(n) * np.array(y)

    return result


def print_estimated_error(func_id: int, grid: list[float], left: float, right: float) -> None:
    x = util.uni_grid(left + util.OFFSET_LEFT, right - util.OFFSET_RIGHT, util.X_COUNT)

    mn = 0.0
    if func_id == 1:
        mn = 1.0
    elif func_id == 2:
        mn = 0.0
    y = get_error_y(x, mn, len(grid), grid)

    plot.plot(x, y, label=f"Оценка для полинома {len(grid) - 1}й степени")


def print_func_and_polys(func_id: int, polys: list[list[float]], func: callable, left: float, right: float, func_as_str: str) -> None:
    x = util.uni_grid(left + util.OFFSET_LEFT, right - util.OFFSET_RIGHT, util.X_COUNT)

    y = func(x)
    plot.title(f"{func_as_str} и {len(polys)} полинома")
    plot.xlabel("x")
    plot.ylabel("y")
    plot.plot(x, y, label=func_as_str)

    colors = ["red", "blue", "green", "yellow", "blue"]
    grids: list[np.array] = list()

    for i in range(len(polys)):
        grid = util.read_written_grid(func_id, 3, i + 1)
        grids.append(np.array(grid))

        y = util.poly_y(polys[i], x)
        plot.plot(x, y, label=f"Полином {len(polys[i]) - 1}й степени", color=colors[i])

    for i in range(len(grids)):
        y = util.poly_y(polys[i], grids[i])
        plot.plot(grids[i], y, linestyle="dotted", marker=".", color=colors[i])

    plot.legend()


def print_error(polys: list[list[float]], func: callable, left: float, right: float, func_as_str: str) -> None:
    x = util.uni_grid(left + util.OFFSET_LEFT, right - util.OFFSET_RIGHT, util.X_COUNT)

    plot.title(f"Ошибка для {func_as_str} и {len(polys)} полиномов")
    plot.xlabel("x")
    plot.ylabel("y")
    real_y = func(x)
    for poly in polys:
        y = util.poly_y(poly, x)
        plot.plot(x, abs(y - real_y), label=f"Ошибка для полинома {len(poly) - 1}й степени")


def analyze(func_id: int, left: float, right: float) -> None:
    polys = util.read(func_id, 3)

    if func_id == 1:
        print_func_and_polys(func_id, polys, tf.func_1, left, right, tf.func_1_str())
        plot.savefig(f"../plots/p3_{func_id}_funcs.png")
        plot.close()

        print_error(polys, tf.func_1, left, right, tf.func_1_str())
    else:
        print_func_and_polys(func_id, polys, tf.func_2, left, right, tf.func_2_str())
        plot.savefig(f"../plots/p3_{func_id}_funcs.png")
        plot.close()

        print_error(polys, tf.func_2, left, right, tf.func_2_str())

    grid: list[float] = util.read_written_grid(func_id, 3, 1)
    print_estimated_error(func_id, grid, left, right)
    plot.legend()
    plot.savefig(f"../plots/p3_{func_id}_error.png")
    plot.close()
