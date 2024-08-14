from matplotlib import pyplot as plot

import analyze.tab_func as tf
import analyze.utility as util


def print_2_dots_error(polys: list[list[float]], func: callable, x1: float, x2: float, func_as_str: str) -> None:
    degrees = list()
    x1_errors = list()
    x2_errors = list()
    for poly in polys:
        x1_errors.append(abs(util.poly_y(poly, x1) - func(x1)))
        x2_errors.append(abs(util.poly_y(poly, x2) - func(x2)))
        degrees.append(len(poly) - 1)

    plot.plot(degrees, x1_errors, label=f"x={x1}")
    plot.plot(degrees, x2_errors, label=f"x={x2}")
    plot.legend()
    plot.title(f"{func_as_str}")
    plot.xlabel("Степень полинома")
    plot.ylabel("Ошибка в точках")


def analyze(func_id: int, x1: float, x2: float) -> None:
    polys = util.read(func_id, 5)

    if func_id == 1:
        print_2_dots_error(polys, tf.func_1, x1, x2, tf.func_1_str())
    else:
        print_2_dots_error(polys, tf.func_2, x1, x2, tf.func_2_str())
    plot.savefig(f"../plots/p5_{func_id}.png")
    plot.close()
