import numpy as np

from analyze.tab_func import *
import analyze.tab_func as tf

X_COUNT = 10000
EXPAND_X_COUNT = 10000
OFFSET_LEFT = 0.000005
OFFSET_RIGHT = 0.000005


def uni_grid(left: float, right: float, point_cnt: int) -> np.ndarray:
    return np.linspace(left, right, point_cnt)


def cheb_grid(left: float, right: float, point_cnt: int) -> np.ndarray:
    k = np.linspace(1, point_cnt, point_cnt)
    return (right + left) / 2 + (right - left) / 2 * np.cos((2 * k - 1) / (2 * point_cnt) * np.pi)


def centered_grid(left: float, right: float, center_point: int, point_cnt: int):
    x = np.linspace(left, right, point_cnt)
    return (x - center_point) * np.sqrt(np.sqrt(np.sqrt(abs(x - center_point) / (right - left))))


def write(func_id: int, paragraph: int,
          exp_cnt: int, min_points_cnt: int,
          step: int, left: float, right: float,
          grid_id: int) -> None:
    with open(f"../data/in_{func_id}_{paragraph}.tf", "w") as file:
        file.write(f"{exp_cnt}\n")
        for i in range(exp_cnt):
            x: np.ndarray = np.ndarray(0)

            if grid_id == 0:
                x = uni_grid(left, right, min_points_cnt + step * i)
            elif grid_id == 1:
                x = cheb_grid(left, right, min_points_cnt + step * i)
            else:
                x = centered_grid(left, right, 0, min_points_cnt + step * i)

            file.write(f"{min_points_cnt + step * i}\n")
            x.tofile(file, " ")
            file.write("\n")
            if func_id == 1:
                y = tf.func_1(x)
            else:
                y = tf.func_2(x)
            y.tofile(file, " ")
            file.write("\n")


def read_written_grid(func_id: int, paragraph: int, exp_num: int) -> list[float]:
    with open(f"../data/in_{func_id}_{paragraph}.tf", "r") as file:
        exp_cnt: int = int(file.readline())
        if exp_cnt < exp_num:
            return list()

        for i in range(exp_num - 1):
            for j in range(3):
                line = file.readline()

        # Skipping grid size
        file.readline()
        grid_as_str: list[str] = file.readline().split(" ")

        grid: list[float] = list()
        for x_str in grid_as_str:
            grid.append(float(x_str))

        return grid


def read(func_id: int, paragraph: int) -> list[list[float]]:
    with open(f"../data/out_{func_id}_{paragraph}.cf", "r") as file:
        poly_cnt = int(file.readline())
        polys = list(list())

        for i in range(poly_cnt):
            polys.append(list())

            degree = int(file.readline())
            poly_as_str = file.readline().split(" ")
            for coeff in poly_as_str:
                if coeff != "" and coeff != "\n":
                    polys[i].append(float(coeff))
        return polys


def poly_y(poly: list[float], x: np.ndarray | float) -> np.ndarray | float:
    y = 0.0
    for deg in poly:
        y = y * x + deg
    return y
