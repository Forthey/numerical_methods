#include "runge_kutta.hpp"

#include <cmath>
#include <iostream>


double RungeKuttaSolver::getNextY(const double x, const double y, const double h, bool getBaseFromCache = false) const {
    static double cache = 0.0;
    double k1 = getBaseFromCache ? cache : (cache = f(x, y));
    double k2 = f(x + h / 2.0, y + h * k1 / 2.0);
    double k3 = f(x + h, y - h * k1 + h * 2.0 * k2);
    return y + h / 6.0 * (k1 + 4.0 * k2 + k3);
}


TabFunc RungeKuttaSolver::solve(Point const& cauchyInit, double const endX, double const epsilon) {
    TabFunc result;
    double x = cauchyInit.x;
    double y = cauchyInit.y;
    double h0 = (endX - cauchyInit.x);
    double h = h0;

    segSteps.clear();

    result.push_back({x, y});
    segSteps.push_back(h);
    while (x < endX) {
        if (x + h > endX) {
            // Корректируем последний шаг, чтобы покрыть весь отрезок
            h = endX - x;
        }

        // Один шаг с шагом h
        double y1 = getNextY(x, y, h);
        // Два шага с шагом h/2
        double y2 = getNextY(x, y, h / 2.0, true);
        y2 = getNextY(x + h / 2.0, y2, h / 2.0);

        double rungeError = std::abs(y1 - y2) / 7;

        if (rungeError <= epsilon) {
            // Принимаем шаг
            x += h;
            y = y1;
            result.push_back({x, y});

            segSteps.push_back(h);
            if (rungeError <= epsilon / 100.0) {
                h *= 2.0;
            }
        }
        else {
            h /= 2.0;
        }
    }

    return std::move(result);
}


TabFunc RungeKuttaSolver::solveConst(const Point &cauchyInit, const double endX, const double h0) {
    TabFunc result;
    double x = cauchyInit.x;
    double y = cauchyInit.y;
    double h = h0;

    result.push_back({x, y});
    while (x < endX) {
        if (x + h > endX) {
            // Корректируем последний шаг, чтобы покрыть весь отрезок
            h = endX - x;
        }

        y = getNextY(x, y, h);
        x += h;
        result.push_back({x, y});
    }

    return std::move(result);
}

