import tab_func as tf
import utility as util
import matplotlib.pyplot as plot


def print_max_error(splines: list[util.Spline], func: callable, func_as_str: str):
    roots: list[float] = list()
    max_errors: list[float] = list()

    for spline in splines:
        max_error: float = 0
        for point in spline.spline_points:
            error: float = abs(func(point.x) - point.y)
            if error > max_error:
                max_error = error

        roots.append(len(spline.spline_base_points))
        max_errors.append(max_error)

    plot.title(f"Макс ошибка для {func_as_str}")
    plot.xlabel("Число узлов")
    plot.ylabel("Ошибка")
    plot.loglog(roots, max_errors)
    plot.show()


def analyze(func_id: int, splines: list[util.Spline]):
    if func_id == 1:
        print_max_error(splines, tf.func_1, tf.func_1_str())
    else:
        print_max_error(splines, tf.func_2, tf.func_2_str())

