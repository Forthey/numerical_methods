from math import sin, cos


def F(x: float) -> float:
    return x ** 5 / 5 - (29 * x ** 4) / 40 + (13 * x ** 3) / 6 - (7 * x ** 2) / 2 - (27 * x) / 5


def F_cos(x: float) -> float:
    return x ** 4 * sin(x) * cos(x) - 1.45 * x ** 3 * sin(2 * x) + (x ** 3 - 1.5 * x) * cos(
        2 * x) + 3.25 * x ** 2 * sin(2 * x) + (-2.175 * x ** 2 + 3.25 * x - 0.6625) * cos(2 * x) - 3 * x ** 2 * sin(
        x) * cos(x) - 1.325 * x * sin(2 * x) - 4.325 * sin(2 * x) + 1.5 * sin(x) * cos(x)


def real_integral(a: float, b: float) -> float:
    return F(b) - F(a)


def real_integral_cos(a: float, b: float) -> float:
    return F_cos(b) - F_cos(a)
