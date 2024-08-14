import matplotlib.pyplot as plt
import numpy as np
from matplotlib import transforms

from utility import TabFunc, TabFuncWithH
from func import solution


def print_plots(results: list[TabFunc]):
    plt.title("Графики зависимости точного и полученного значений")
    plt.xlabel("x")
    plt.ylabel("y")

    x: np.ndarray = np.array(list(map(lambda p: p.x, results[0].points)))
    real_y: np.ndarray = solution(x)

    plt.plot(x, real_y, label="Точное")
    for result in results:
        cur_x = list(map(lambda p: p.x, result.points))
        cur_y = list(map(lambda p: p.y, result.points))
        plt.plot(cur_x, cur_y, label=f"h0={result.h0}")
    plt.legend()
    plt.show()


def print_errors(results: list[TabFunc]):
    plt.title("Графики зависимости относительной ошибки от x")
    plt.xlabel("x")
    plt.ylabel("Ошибка")
    for result in results:
        cur_x = list(map(lambda p: p.x, result.points))
        cur_y = np.array(list(map(lambda p: p.y, result.points)))

        plt.plot(cur_x, abs(cur_y - solution(np.array(cur_x))), label=f"h0={result.h0}")
    plt.legend()
    plt.show()


def print_steps(results: list[TabFuncWithH]):
    plt.title(f"График изменения шага h по отрезку для точности {results[0].epsilon}")
    plt.xlabel("x")
    plt.ylabel("h")

    x = list(map(lambda p: p.x, results[0].points))
    plt.plot(x, results[0].h)
    plt.show()


def print_max_errors(results: list[TabFuncWithH]):
    plt.title("График зависимости максимальной ошибки от заданной точности")
    plt.xlabel("Точность")
    plt.ylabel("Ошибка")

    epsilons: list[float] = []
    max_errors: list[float] = []

    for result in results:
        max_error = 0
        cur_x = list(map(lambda p: p.x, result.points))
        for i in range(len(cur_x)):
            error = abs(result.points[i].y - solution(result.points[i].x))
            if error > max_error:
                max_error = error

        epsilons.append(result.epsilon)
        max_errors.append(max_error)

    plt.grid(linewidth=0.1)

    plt.loglog(epsilons, epsilons, linestyle="dotted")
    # plt.loglog(epsilons, max_errors)
    plt.show()


def analyze_const(data: list[TabFunc]):
    print_plots(data)
    print_errors(data)


def analyze(data: list[TabFuncWithH]):
    print_steps(data)
    print_max_errors(data)
