#pragma once
#include <functional>
#include <vector>


struct Point {
    double x;
    double y;
};

using TabFunc = std::vector<Point>;

class RungeKuttaSolver {
    std::function<double(double, double)> f;
    std::vector<double> segSteps;

    [[nodiscard]] double getNextY(double const x, double const y, double const h, bool getBaseFromCache) const;
public:
    explicit RungeKuttaSolver(std::function<double(double, double)> f) : f(std::move(f)) {};

    [[nodiscard]] TabFunc solve(Point const& cauchyInit, double const endX, double const epsilon);
    [[nodiscard]] TabFunc solveConst(Point const& cauchyInit, double const endX, double const h0);
    [[nodiscard]] std::vector<double> const& getLastSegSteps() const { return segSteps; }
};
