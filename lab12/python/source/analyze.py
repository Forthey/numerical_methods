import numpy as np
from matplotlib import pyplot as plt

from source.file import ResultP1DTO, ResultP2DTO, read_from_file_p1, read_from_file_p2


def precise_solution(x: np.ndarray | float) -> np.ndarray | float:
    return np.e ** (x ** 2) - x ** 2 - 1


def print_plots(results: list[ResultP1DTO.SingleResult]):
    plt.title("Графики зависимости точного и полученного значений")
    plt.xlabel("x")
    plt.ylabel("y")

    x: np.ndarray = np.array(results[0].x)
    real_y: np.ndarray = precise_solution(x)

    plt.plot(x, real_y, label="Точное")
    for result in results:
        plt.plot(result.x, result.y, label=f"h0={result.h0}")
    plt.legend()
    plt.show()


def print_errors(results: list[ResultP1DTO.SingleResult]):
    plt.title("Графики зависимости относительной ошибки от x")
    plt.xlabel("x")
    plt.ylabel("Ошибка")
    for result in results:
        plt.plot(result.x, abs(result.y - precise_solution(np.array(result.x))) / result.y, label=f"h0={result.h0}")
    plt.legend()
    plt.show()


def print_steps(results: list[ResultP2DTO.SingleResult]):
    plt.title(f"График изменения шага h по отрезку для точности {results[0].epsilon}")
    plt.xlabel("x")
    plt.ylabel("h")
    plt.plot(results[0].x[1:], results[0].h[1:])
    plt.show()


def print_max_errors(results: list[ResultP2DTO.SingleResult]):
    plt.title("График зависимости максимальной ошибки от заданной точности")
    plt.xlabel("Точность")
    plt.ylabel("Ошибка")

    epsilons: list[float] = []
    max_errors: list[float] = []

    for result in results:
        max_error = 0
        for i in range(len(result.x)):
            if abs(result.x[i] - precise_solution(result.x[i])) > max_error:
                max_error = abs(result.y[i] - precise_solution(result.x[i]))

        epsilons.append(result.epsilon)
        max_errors.append(max_error)
    plt.loglog(epsilons, epsilons, linestyle="dotted")
    plt.loglog(epsilons, max_errors)
    plt.show()


def analyze_p1(results: list[ResultP1DTO.SingleResult]):
    if len(results) == 0:
        return

    print_plots(results)
    print_errors(results)


def analyze_p2(results: list[ResultP2DTO.SingleResult]):
    if len(results) == 0:
        return
    print_steps(results)
    print_max_errors(results)


print("Номер параграфа: ")
p = int(input())

if p == 1:
    analyze_p1(read_from_file_p1().results)
elif p == 2:
    analyze_p2(read_from_file_p2().results)
