#include "poly.hpp"

Poly::Poly(PolyCoefs polyCoefs) : coefficients(std::move(polyCoefs)) {
}


Poly::Poly(size_t degree) : coefficients(degree + 1) {
}


PolyCoefs const &Poly::getCoefs() const {
    return coefficients;
}


size_t Poly::degree() const {
    return coefficients.size() - 1;
}


std::string Poly::formattedNumber(const long double number) {
    return (number >= 0 ? " + " : " - ") + (std::abs(number) == 1.0 ? "" : std::to_string(std::abs(number)));
}


void Poly::display() const {
    std::cout << (std::abs((*this)[degree()]) == 1.0 ? "" : std::to_string((*this)[degree()]))
              << "x^" << this->degree();
    if (this->degree() == 0) {
        return;
    }
    for (size_t curDegree = this->degree() - 1; curDegree > 0; curDegree--) {
        std::cout << formattedNumber(coefficients[curDegree]) << "x"
                  << (curDegree == 1 ? "" : ("^" + std::to_string(curDegree)));
    }
    std::cout << formattedNumber(coefficients[0]) << std::endl;
}


Poly Poly::operator+(Poly const &poly) const {
    size_t const degree = std::max(poly.degree(), this->degree());
    Poly polySum(degree);

    for (size_t curDeg = 0; curDeg <= degree; curDeg++) {
        if (curDeg > poly.degree()) {
            polySum[curDeg] = (*this)[curDeg];
        } else if (curDeg > this->degree()) {
            polySum[curDeg] = poly[curDeg];
        } else {
            polySum[curDeg] = poly[curDeg] + (*this)[curDeg];
        }
    }

    return polySum;
}


Poly &Poly::operator+=(const Poly &poly) {
    for (size_t curDeg = 0; curDeg <= poly.degree(); curDeg++) {
        if (this->degree() < curDeg) {
            this->coefficients.push_back(poly[curDeg]);
        } else {
            (*this)[curDeg] += poly[curDeg];
        }
    }

    return *this;
}

Poly Poly::operator%(long double root) const {
    if (this->degree() == 0) {
        return *this;
    }
    Poly polyResult(this->degree() - 1);

    polyResult[polyResult.degree()] = (*this)[degree()];
    for (size_t curDeg = degree() - 1; curDeg > 0; curDeg--) {
        polyResult[curDeg - 1] = polyResult[curDeg] * root + (*this)[curDeg];
    }

    return polyResult;
}

Poly Poly::operator*(long double number) const {
    Poly multipliedPoly(this->coefficients);

    for (auto &coefficient : multipliedPoly.coefficients) {
        coefficient *= number;
    }
    return multipliedPoly;
}

long double &Poly::operator[](size_t index) {
    return coefficients[index];
}

long double const &Poly::operator[](size_t index) const {
    return coefficients[index];
}