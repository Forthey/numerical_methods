#include <iostream>
#include "CauchySolver.hpp"

void print(Vector<2> const& v) {
    std::cout << "(" << v[0] << " " << v[1] << ")\n";
}

Vector<2> CauchySolver::getNextY(double const x, Vector<2> const y, double const h, bool getBaseFromCache = false) const {
    static Vector<2> cache = f(x, y) * h;
    Vector<2> k1 = (getBaseFromCache) ? (cache) : (cache = f(x, y) * h);
    print(k1);
    Vector<2> k2 = f(x + h / 2.0, y + k1 / 2.0) * h;
    print(k2);
    Vector<2> k3 = f(x + h, y - k1 + k2 * 2.0) * h;
    print(k3);
    print(y + (k1 + k2 * 4.0 + k3) / 6.0);
    return y + (k1 + k2 * 4.0 + k3) / 6.0 ;
}


VectorTabFuncsWithH CauchySolver::solve(double const a, double const b,
                                  Vector<2> const& cauchyInitHomogeneous,
                                  Vector<2> const& cauchyInit,
                                  double const epsilon,
                                  const ConstantFormula& formulaC) {
    VectorTabFunc homoResult, result;
    std::vector<double> hs;
    double x = a;
    Vector<2> homoY = cauchyInitHomogeneous, y = cauchyInit;
    double h = (b - a) / 2.0;

    // Грубая оценка константы c
    Vector<2>
            homo_cy = getNextY(a + h, getNextY(a, cauchyInitHomogeneous, h), h),
            cy = getNextY(a + h, getNextY(a, cauchyInit, h), h);
    double const c = formulaC(homo_cy[0], homo_cy[1], cy[0], cy[1]);

    homoResult.emplace_back(x, homoY);
    result.emplace_back(x, y);
    while (x < b) {
        if (x + h > b) {
            // Корректируем последний шаг, чтобы покрыть весь отрезок
            h = b - x;
        }

        Vector<2> homoY1 = getNextY(x, homoY, h);
        Vector<2> homoY2 = getNextY(x, homoY, h / 2.0, false);
        homoY2 = getNextY(x + h / 2.0, homoY2, h / 2.0);

        Vector<2> y1 = getNextY(x, y, h);
        Vector<2> y2 = getNextY(x, y, h / 2.0, false);
        y2 = getNextY(x + h / 2.0, y2, h / 2.0);

        double rungeError = abs(homoY1 + y1 * c - homoY2 - y2 * c) / 7.0;

        if (rungeError <= epsilon) {
            // Принимаем шаг
            x += h;
            y = y1;
            homoY = homoY1;

            hs.emplace_back(h);
            homoResult.emplace_back(x, homoY);
            result.emplace_back(x, y);

            if (rungeError <= epsilon / 100) {
                h *= 2.0;
            }
        }
        else {
            h /= 2.0;
        }
    }

    return {{std::move(homoResult), std::move(result)}, std::move(hs)};
}


std::pair<VectorTabFunc, VectorTabFunc> CauchySolver::solveConst(double const a, double const b,
                                       Vector<2> const& cauchyInitHomogeneous,
                                       Vector<2> const& cauchyInit,
                                       double const h0) {
    VectorTabFunc result, homoResult;
    Vector<2> homoY = cauchyInitHomogeneous, y = cauchyInit;
    double x = a;
    double h = h0;

    homoResult.emplace_back(x, homoY);
    result.emplace_back(x, y);
    while (x < b) {
        if (x + h > b) {
            // Корректируем последний шаг, чтобы покрыть весь отрезок
            h = b - x;
        }

        homoY = getNextY(x, homoY, h);
        y = getNextY(x, y, h);
        x += h;

        homoResult.emplace_back(x, homoY);
        result.emplace_back(x, y);
    }

    return {std::move(homoResult), std::move(result)};
}
