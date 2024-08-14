#include "quadratic_spline.hpp"

#include <iostream>


std::string quadPolyToStr(QuadPoly const& quadPoly) {
    return "{ a=" + str(quadPoly.a) + ", b=" + str(quadPoly.b) + ", c=" + str(quadPoly.c) +
           " on (" + str(quadPoly.x0) + ", " + str(quadPoly.x1) +")}";
}

std::string pointToStr(Point const& point) {
    return "(" + str(point.x) + "; " + str(point.y) + ")";
}


void QuadraticSpline::addPointToTabFunc(double x, double y) {
    tabFunc.emplace_back(x, y);
}


double QuadraticSpline::quadPolyY(QuadPoly const& quadPoly, double x) {
    return quadPoly.a * x * x + quadPoly.b * x + quadPoly.c;
}

double QuadraticSpline::splineY(const std::vector<QuadPoly> &spline, double x) {
    for (auto& quadPoly : spline) {
        if (quadPoly.x0 <= x && x <= quadPoly.x1) {
            return quadPolyY(quadPoly, x);
        }
    }

    return 0.0;
}


double QuadraticSpline::derFromCoefs(double a, double b, double x) {
    return 2.0 * a * x + b;
}

QuadPoly QuadraticSpline::evalLocalCoefficients(double x1, double x0, double y1, double y0, double d0) {
    double dx = x1 - x0, dy = y1 - y0;
    double dy_div_dx = dy / dx;

    // Посчитаны на бумаге
    double a = dy_div_dx / dx - d0 / dx;
    double b = dy_div_dx - a * (x1 + x0);
    double c = y0 - b * x0 - a * x0 * x0;

    return {a, b, c, x0, x1};
}


QuadPoly QuadraticSpline::evalFirstCoefficients(double x2, double x1, double x0, double y2, double y1, double y0) {
    // Посчитаны на бумаге
    double a = (-x0*y1 + x0*y2 + x1*y0 - x1*y2 - x2*y0 + x2*y1) / ((x1 - x0)*(x2 - x0)*(x1 - x2));
    double b = (y1 - y0) / (x1 - x0) - (x1 + x0) * a;
    double c = y0 - b * x0 - a * x0 * x0;

    return {a, b, c, x0, x1};
}


std::vector<Point> const &QuadraticSpline::getPoints() {
    return tabFunc;
}


std::vector<QuadPoly> QuadraticSpline::evaluateCoefficients() {
    std::vector<QuadPoly> spline;

    if (tabFunc.size() < 3) {
        std::cout << "Cannot evaluate spline: only " << tabFunc.size() << " dots have been received" << std::endl;
        return {};
    }

    QuadPoly missedQoefsPoly = evalFirstCoefficients(tabFunc[2].x, tabFunc[1].x, tabFunc[0].x,
                                                     tabFunc[2].y, tabFunc[1].y, tabFunc[0].y);

    // Так как полиномы тождественные
    spline.push_back(missedQoefsPoly);
    missedQoefsPoly.x0 = tabFunc[1].x;
    missedQoefsPoly.x1 = tabFunc[2].x;
    spline.push_back(missedQoefsPoly);

    QuadPoly evalQuadPoly;
    for (int i = 2; i < tabFunc.size() - 1; i++) {
        double d0 = derFromCoefs(spline[i - 1].a, spline[i - 1].b, tabFunc[i].x);

        evalQuadPoly = evalLocalCoefficients(tabFunc[i + 1].x, tabFunc[i].x,
                                             tabFunc[i + 1].y, tabFunc[i].y, d0);

        spline.push_back(evalQuadPoly);
    }

    PrettyStl<QuadPoly> pretty;
    pretty.setElementOutput(quadPolyToStr);
    pretty.print(spline, " --> ", "[ ", " ]\n");

    return spline;
}


std::vector<Point> QuadraticSpline::getSplineValues(std::vector<QuadPoly> const& spline, long pointsCnt) {
    if (spline.empty()) {
        return {};
    }

    std::cout << "Eval actual values" << std::endl;
    std::vector<Point> splineValues;

    double left = spline[0].x0, right = spline[spline.size() - 1].x1;
    double step = (right - left) / double(pointsCnt - 1);
    double prevX = left;

    splineValues.emplace_back(left, splineY(spline, left));
    for (long i = 1; i < pointsCnt; i++) {
        double x = prevX + step;
        prevX = x;
        splineValues.emplace_back(x, splineY(spline, x));
    }

    return splineValues;
}
