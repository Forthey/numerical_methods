import numpy as np


def func_1(_x: np.ndarray | float) -> np.ndarray | float:
    return 3 * _x - np.cos(_x)


def func_1_str() -> str:
    return "3x - cos(x) - 1"


def func_2(_x: np.ndarray | float) -> np.ndarray | float:
    return _x ** 3 - np.sign(_x) * _x ** 2 + 6 * _x + 3


def func_2_str() -> str:
    return "x^3 - sign(x)x^2 + 6x + 3"
