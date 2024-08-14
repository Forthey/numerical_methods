import matplotlib.pyplot as plot
import numpy as np

from utility import CalcResult
from integral import real_integral


def eval_coefficient_via_mnk(x: list[float], y: list[float]) -> float:
    x = list(map(lambda x_val: np.log2(x_val), x))
    y = list(map(lambda y_val: np.log2(y_val), y))

    matr = np.vstack([x, np.ones(len(x))]).T
    b, c = np.linalg.lstsq(matr, y, rcond=None)[0]
    return b


def analyze(data: list[CalcResult]):
    errors: list[float] = []
    epsilons: list[float] = []
    iter_nums: list[float] = []
    hs: list[float] = []

    for data_el in data:
        errors.append(abs(data_el.value - real_integral(data_el.requirements.a, data_el.requirements.b)))
        epsilons.append(data_el.requirements.epsilon)
        iter_nums.append(data_el.iter_cnt)
        hs.append(data_el.h)

    # Параграф 3
    plot.title("Зависимость ошибки от точности")
    plot.xlabel("Точность")
    plot.ylabel("Ошибка")
    plot.grid(visible=True)
    plot.loglog(epsilons, errors, color="black")
    plot.loglog(epsilons, epsilons, linestyle="dotted", color="gray")
    # plot.loglog(epsilons, list(map(lambda e: e / 10, epsilons)), linestyle="dotted", color="gray")
    plot.show()

    # Параграф 4
    plot.title("Зависимость числа итераций от точности")
    plot.xlabel("Точность")
    plot.ylabel("Число итераций")
    plot.grid(visible=True)
    plot.semilogx(epsilons, iter_nums, color="black")
    plot.show()

    # Параграф 5
    plot.title("Зависимость ошибки от отрезка разбиения")
    plot.xlabel("Длина отрезка")
    plot.ylabel("Ошибка")
    plot.grid(visible=True)
    plot.loglog(hs, errors, base=2, color="black")
    plot.show()

    print(eval_coefficient_via_mnk(hs, errors))
