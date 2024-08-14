#pragma once
#include <iostream>
#include <vector>
#include <string>

using PolyCoefs = std::vector<long double>;

// Класс полинома, упрощающий предавление полинома и преобразования над ним
class Poly {
    PolyCoefs coefficients;

    static std::string formattedNumber(long double number);
public:
    explicit Poly(PolyCoefs polyCoefs = {0.0});
    explicit Poly(size_t degree);

    [[nodiscard]] PolyCoefs const & getCoefs() const;
    [[nodiscard]] size_t degree() const;

    // Различные переопределения операторов, позволяющие писать преобразования над полиномами в понятном виде и др.
    // Ex. p = p1 + p2 вместо p = sumPoly(p1, p2)

    Poly operator+(Poly const &poly) const;
    Poly & operator+=(Poly const &poly);
    Poly operator%(long double root) const;
    Poly operator*(long double number) const;
    long double & operator[](size_t index);
    long double const &operator[](size_t index) const;

    void display() const;
};