import numpy as np
from matplotlib import pyplot as plot

import analyze.tab_func as tf
import analyze.utility as util


def print_max_error(polys: list[list[float]], func: callable, left: float, right: float, func_as_str: str) -> None:
    x = util.uni_grid(left, right, util.EXPAND_X_COUNT)
    degrees = list()
    max_errors = list()
    for poly in polys:
        max_error = 0
        for cur_x in x:
            cur_y = util.poly_y(poly, cur_x)
            fy = func(cur_x)
            if abs(cur_y - fy) > max_error:
                max_error = abs(cur_y - fy)

        degrees.append(len(poly) - 1)
        max_errors.append(max_error)

    plot.semilogy(degrees, max_errors)
    plot.title(f"{func_as_str}")
    plot.xlabel("Степень полинома")
    plot.ylabel("Макс. ошибка")


def analyze(func_id: int, left: float, right: float) -> None:
    polys = util.read(func_id, 4)

    if func_id == 1:
        print_max_error(polys, tf.func_1, left, right, tf.func_1_str())
    else:
        print_max_error(polys, tf.func_2, left, right, tf.func_2_str())
    plot.savefig(f"../plots/p4_{func_id}.png")
    plot.close()
