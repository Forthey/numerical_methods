//
// Created by 0Fort on 06.04.2024.
//
#include "integral.hpp"

#include <cmath>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>


int const IntegralCalculator::methodOrder = 4;
double const IntegralCalculator::rungeRuleDenominator = pow(2.0, methodOrder) - 1;


IntegralCalculator::IntegralCalculator(Function f) : func(f) {
}


bool IntegralCalculator::checkRungeRule(const double I_2n, const double I_n, const double epsilon) {
    return std::abs(I_2n - I_n) / rungeRuleDenominator <= epsilon;
}


IntegralCalculator::Result IntegralCalculator::calculateThreeEight(double a, double b, double epsilon) {
    FuncWithCallCnt f(func);

    int const n = 4; // общее разбиение для формулы 3/8 подотрезков
    int N = 1;  // число разбиений [a, b] на подотрезки
    double H = b - a; // Шаг по отрезку [a, b]
    double h = H / (n - 1); // Шаг по подотрезкам
    double coeff = 3 * h / 8; // Коэффициент перед каждым слагаемым
    double I_N, I_2N; // Интегралы для N и 2N разбиений

    // Для  сохранения вычисленных ранее значений функции
    // 1й массив хранит "старые значения", 2й массив будет строить новые значения для нового N
    std::vector<double> funcValues = {f(a), f(a + h), f(a + 2*h), f(a + 3*h)}, newFuncValues;

    // Первичный расчет интеграла
    I_2N = coeff * (funcValues[0] + 3*funcValues[1] + 3*funcValues[2] + funcValues[3]);

    do {
        I_N = I_2N;
        I_2N = 0;
        // Увеличиваем число точек
        N *= 2, H /= 2, h /= 2, coeff /= 2;

        newFuncValues.resize(funcValues.size() * 2 - 1);

        for (int i = 0; i < N; i++) {
            double sub_a = a + i * H;

            // Строим новый массив значений на основе старого
            if (i == 0) {
                newFuncValues[0] = funcValues[0];
            }
            for (int j = 1; j < n; j++) {
                int newIndex = 3 * i + j;
                int oldIndex = newIndex / 2;
                if (newIndex % 2 == 0) {
                    newFuncValues[newIndex] = funcValues[oldIndex];
                } else {
                    newFuncValues[newIndex] = f(sub_a + j * h);
                }
            }

            // Добавляем к интегралу значения функций на отрезке с коэффициентами
            I_2N += newFuncValues[3 * i] +
                    3 * newFuncValues[3 * i + 1] +
                    3 * newFuncValues[3 * i + 2] +
                    newFuncValues[3 * i + 3];
        }
        // Коэффициент 3h/8 перед всем интегралом
        I_2N *= coeff;
        // Новый массив значений теперь старый
        funcValues = std::move(newFuncValues);
    }
    while (!checkRungeRule(I_2N, I_N, epsilon));

    return {I_2N, f.getCallCnt()};
}


double IntegralCalculator::calculateGaussOnSubsection(double a, double b, int n, FuncWithCallCnt &f) {
    /// Хэш таблица, которая по заданному n дает пару массивов коэффициентов ti, Ai
    /// Все значения из-за статичности вычисляются лишь один раз на этапе компиляции
    static std::unordered_map<int, std::pair<std::vector<double>, std::vector<double>>> const nodeNumToCoefficients = {
            {2,
                    {
                            {-1.0/std::sqrt(3.0), 1.0/std::sqrt(3.0)},
                            {1.0, 1.0}
                    }
            },
            {3,
                    {
                            {0, -std::sqrt(3.0/5.0), std::sqrt(3.0/5.0)},
                            {8.0/9.0, 5.0/9.0, 5.0/9.0}
                    }
            },
            {4,
                    {
                            {-std::sqrt(3.0/7.0 - 2.0/7.0*std::sqrt(6.0/5.0)), std::sqrt(3.0/7.0 - 2.0/7.0*std::sqrt(6.0/5.0)), -std::sqrt(3.0/7.0 + 2.0/7.0*std::sqrt(6.0/5.0)), std::sqrt(3.0/7.0 + 2.0/7.0*std::sqrt(6.0/5.0))},
                            {(18.0 + std::sqrt(30.0))/36.0, (18.0 + std::sqrt(30.0))/36.0, (18.0 - std::sqrt(30.0))/36.0, (18.0 - std::sqrt(30.0))/36.0}
                    }
            },
            {5,
                    {
                            {0, -1.0/3.0*std::sqrt(5.0 - 2*std::sqrt(10.0/7.0)), 1.0/3.0*std::sqrt(5.0 - 2*std::sqrt(10.0/7.0)), -1.0/3.0*std::sqrt(5.0 + 2*std::sqrt(10.0/7.0)), 1.0/3.0*std::sqrt(5.0 + 2*std::sqrt(10.0/7.0))},
                            {128.0/225.0, (322.0 + 13.0 * std::sqrt(70.0)) / 900.0, (322.0 + 13.0 * std::sqrt(70.0)) / 900.0, (322.0 - 13.0 * std::sqrt(70.0)) / 900.0, (322.0 - 13.0 * std::sqrt(70.0)) / 900.0}
                    }
            }
    };

    n = std::max(2, std::min(5, n));
    double integral = 0.0;

    for (int i = 0; i < nodeNumToCoefficients.at(n).first.size(); i++) {
        integral += nodeNumToCoefficients.at(n).second[i] * f(convert_t_to_ab(nodeNumToCoefficients.at(n).first[i], a, b));
    }
    return (b - a) / 2.0 * integral;
}

double IntegralCalculator::calculateGaussRec(double a, double b, double epsilon, FuncWithCallCnt &f) {
    double value = 0.0, prevValue = calculateGaussOnSubsection(a, b, 2, f);

    for (int i = 3; i <= 5; i++) {
        value = calculateGaussOnSubsection(a, b, i, f);
        if (std::abs(value - prevValue) < epsilon) {
            return value;
        }
        prevValue = value;
    }

    double c = (a + b) / 2.0;
    return calculateGaussRec(a, c, epsilon, f) + calculateGaussRec(c, b, epsilon, f);
}

IntegralCalculator::Result IntegralCalculator::calculateGauss(double a, double b, double epsilon) {
    FuncWithCallCnt f(func);
    double integral = calculateGaussRec(a, b, epsilon, f);

    return IntegralCalculator::Result(integral, f.getCallCnt());
}


