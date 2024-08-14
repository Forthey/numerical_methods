#include "poly_interpolator.hpp"

PolyInterpolator::PolyInterpolator(const std::string &postfix) {
    std::ifstream fileIn(std::format("{}/in{}.tf", dataDirPath, postfix));
    std::ofstream fileOut(std::format("{}/out{}.cf", dataDirPath, postfix));

    if (!fileIn.is_open() || !fileOut.is_open()) {
        std::cout << "Cannot open data files, exiting..." << std::endl;
        return;
    }

    size_t experimentsCnt;
    fileIn >> experimentsCnt;
    fileOut << experimentsCnt << std::endl;
    for (size_t curExperiment = 0; curExperiment < experimentsCnt; curExperiment++) {
        size_t rootsCnt;

        fileIn >> rootsCnt;
        fileOut << rootsCnt << std::endl;

        long double x, y;
        for (size_t index = 0; index < rootsCnt; index++) {
            fileIn >> x;
            if (x == 0.0) {
                std::cout << std::format("Looks like you have 0 in your grid. Program will replace it with {}\n", zeroReplacer);
                x = zeroReplacer;
            }
            tabFunc.grid.push_back(x);
        }
        for (size_t index = 0; index < rootsCnt; index++) {
            fileIn >> y;
            tabFunc.gridFunc.push_back(y);
        }

        Poly polyLagrange = findPolyLagrange();
        polyLagrange.display();
        for (size_t i = polyLagrange.getCoefs().size(); i > 0; i--) {
            fileOut << polyLagrange[i - 1] << " ";
        }
        fileOut << std::endl;

        tabFunc.grid.clear();
        tabFunc.gridFunc.clear();
    }

    fileIn.close();
    fileOut.close();
}


Poly PolyInterpolator::findRootPoly() {
    size_t const degree = tabFunc.grid.size();
    Poly rootPoly(degree);

    // Начинаем с единичного полинома
    rootPoly[0] = 1;
    // Перебираем все корни
    for (auto &xk : tabFunc.grid) {
        // Нужно предыдущую версию полинома домножить на (x - xk)
        for (size_t curDegree = degree; curDegree > 0; curDegree--) {
            rootPoly[curDegree] = rootPoly[curDegree - 1] - xk * rootPoly[curDegree];
        }
        rootPoly[0] *= -xk;
    }
    return rootPoly;
}


long double PolyInterpolator::findDenomFor(size_t index) {
    long double denominator = 1.0;
    for (size_t i = 0; i < tabFunc.grid.size(); i++) {
        if (i != index) {
            denominator *= tabFunc.grid[index] - tabFunc.grid[i];
        }
    }
    return denominator;
}


Poly PolyInterpolator::findPolyLagrange() {
    Poly rootPoly = findRootPoly();
    Poly polyLagrange;

    for (size_t i = 0; i < rootPoly.degree(); i++) {
        polyLagrange += rootPoly * tabFunc.gridFunc[i] % tabFunc.grid[i] * (1.0 / findDenomFor(i));
    }
    return polyLagrange;
}