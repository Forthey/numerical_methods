#pragma once
#include <vector>
#include <functional>

#include "Vector.hpp"

struct VectorPoint {
    double x;
    Vector<2> y;
};

using VectorTabFunc = std::vector<VectorPoint>;
using VectorFunction = std::function<Vector<2>(double const, Vector<2> const&)>;
using ConstantFormula = std::function<double(double, double, double, double)>;

struct VectorTabFuncsWithH {
    std::pair<VectorTabFunc, VectorTabFunc> tabFuncs;
    std::vector<double> h;
};

class CauchySolver {
    VectorFunction f;

    [[nodiscard]] Vector<2> getNextY(double const x, Vector<2> const y, double const h, bool getBaseFromCache) const;
public:
    explicit CauchySolver(VectorFunction f) : f(std::move(f)) {};

    [[nodiscard]] VectorTabFuncsWithH solve(double const a, double const b,
                                      Vector<2> const& cauchyInitHomogeneous,
                                      Vector<2> const& cauchyInit,
                                      double const epsilon,
                                      const ConstantFormula& formulaC);
    [[nodiscard]] std::pair<VectorTabFunc, VectorTabFunc> solveConst(double const a, double const b,
                                           Vector<2> const& cauchyInitHomogeneous,
                                           Vector<2> const& cauchyInit,
                                           double const h0);
};
