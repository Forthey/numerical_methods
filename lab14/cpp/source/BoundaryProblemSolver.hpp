#pragma once

#include "CauchySolver.hpp"

struct Point {
    double x;
    double y;
};

using TabFunc = std::vector<Point>;

struct TabFuncWithH {
    TabFunc tabFunc;
    std::vector<double> h;
};

using Function = std::function<double(double, double, double)>;

class BoundaryProblemSolver {
    Function f;
public:
    explicit BoundaryProblemSolver(Function f) : f(std::move(f)) {}

    [[nodiscard]] TabFuncWithH solve(double const a, double const b,
                                Vector<2> const& cauchyInitHomogeneous, Vector<2> const& cauchyInit,
                                const ConstantFormula& formulaC, double const epsilon);

    [[nodiscard]] TabFunc solveConst(double const a, double const b,
                       Vector<2> const& cauchyInitHomogeneous, Vector<2> const& cauchyInit,
                       const ConstantFormula& formulaC, double const h0);
};
