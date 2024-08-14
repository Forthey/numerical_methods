import matplotlib.pyplot as plot
import numpy as np

from utility import CalcResult
from integral import real_integral_cos, real_integral


def eval_coefficient_via_mnk(x: list[float], y: list[float]) -> float:
    x = list(map(lambda x_val: np.log2(x_val), x))
    y = list(map(lambda y_val: np.log2(y_val), y))

    matr = np.vstack([x, np.ones(len(x))]).T
    b, c = np.linalg.lstsq(matr, y, rcond=None)[0]
    return b


def analyze(data: list[CalcResult]):
    epsilons: list[float] = []
    errors_38: list[float] = []
    call_cnts_38: list[float] = []
    errors_gauss: list[float] = []
    call_cnts_gauss: list[float] = []

    for data_el in data:
        epsilons.append(data_el.requirements.epsilon)

        errors_38.append(abs(data_el.value_38 - real_integral_cos(data_el.requirements.a, data_el.requirements.b)))
        call_cnts_38.append(data_el.call_cnt_38)

        errors_gauss.append(abs(data_el.value_gauss - real_integral_cos(data_el.requirements.a, data_el.requirements.b)))
        call_cnts_gauss.append(data_el.call_cnt_gauss)


    # # Параграф 3
    # plot.title("Зависимость ошибки от точности")
    # plot.xlabel("Точность")
    # plot.ylabel("Ошибка")
    #
    # plot.loglog(epsilons, errors_38, color="black")
    # plot.loglog(epsilons, errors_gauss, color="green")
    # plot.loglog(epsilons, epsilons, linestyle="dotted", color="gray")
    # # plot.loglog(epsilons, list(map(lambda e: e / 10, epsilons)), linestyle="dotted", color="gray")
    # plot.show()

    # Параграф 4
    plot.title("Зависимость количества вызовов подынтегральной функции от точности")
    plot.xlabel("Точность")
    plot.ylabel("Количество вызовов")

    plot.semilogx(epsilons, call_cnts_38, color="black", label="Метод 3/8")
    plot.semilogx(epsilons, call_cnts_gauss, color="green", label="Метод Гаусса")

    plot.legend()
    plot.show()
