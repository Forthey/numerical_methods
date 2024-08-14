#include <iostream>
#include "BoundaryProblemSolver.hpp"


TabFunc BoundaryProblemSolver::solveConst(double const a, double const b,
                                          Vector<2> const& cauchyInitHomogeneous, Vector<2> const& cauchyInit,
                                          const ConstantFormula& formulaC, double const h0) {
    CauchySolver solver([this](double const x, Vector<2> const& y) -> Vector<2> {
        return Vector<2>(y[1], f(x, y[0], y[1]));
    });
    auto result_u_v = solver.solveConst(a, b, cauchyInitHomogeneous, cauchyInit, h0);
    VectorTabFunc u = std::move(result_u_v.first), v = std::move(result_u_v.second);
    TabFunc result(u.size());
    double const c = formulaC(u[u.size() - 1].y[0], u[u.size() - 1].y[1], v[v.size() - 1].y[0], v[v.size() - 1].y[1]);

    for (std::size_t i = 0; i < u.size(); i++) {
        result[i].x = u[i].x;
        result[i].y = u[i].y[0] + c * v[i].y[0];
    }

    return std::move(result);
}

TabFuncWithH BoundaryProblemSolver::solve(const double a, const double b, const Vector<2> &cauchyInitHomogeneous,
                                     const Vector<2> &cauchyInit, const ConstantFormula &formulaC,
                                     const double epsilon) {
    CauchySolver solver([this](double const x, Vector<2> const& y) -> Vector<2> {
        return Vector<2>(y[1], f(x, y[0], y[1]));
    });
    auto result_u_v = solver.solve(a, b, cauchyInitHomogeneous, cauchyInit, epsilon, formulaC);
    VectorTabFunc u = std::move(result_u_v.tabFuncs.first), v = std::move(result_u_v.tabFuncs.second);
    TabFunc result(u.size());
    double const c = formulaC(u[u.size() - 1].y[0], u[u.size() - 1].y[1], v[v.size() - 1].y[0], v[v.size() - 1].y[1]);

    for (std::size_t i = 0; i < u.size(); i++) {
        result[i].x = u[i].x;
        result[i].y = u[i].y[0] + c * v[i].y[0];
    }

    return {std::move(result), std::move(result_u_v.h)};
}
