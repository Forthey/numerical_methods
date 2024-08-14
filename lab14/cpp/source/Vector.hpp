#pragma once
#include <cstddef>
#include <array>
#include <cmath>


template<std::size_t dim>
class Vector {
    std::array<double, dim> data;
public:
    Vector() = default;
    Vector(Vector const& vector) = default;
    Vector& operator=(Vector const&) = default;

    template<typename ...Elements>
    explicit Vector(Elements&&...elements) : data{{static_cast<double>(std::forward<Elements>(elements))...}} {
    }

    Vector operator+(Vector const& vector) const {
        Vector<dim> result;
        for (std::size_t i = 0; i < dim; i++) {
            result[i] = data[i] + vector.data[i];
        }
        return result;
    }

    Vector& operator+=(Vector const& vector) {
        for (std::size_t i = 0; i < dim; i++) {
            data[i] += vector.data[i];
        }
        return *this;
    }

    Vector operator-(Vector const& vector) const {
        Vector<dim> result;
        for (std::size_t i = 0; i < dim; i++) {
            result[i] = data[i] - vector.data[i];
        }
        return result;
    }

    Vector& operator-=(Vector const& vector) {
        for (std::size_t i = 0; i < dim; i++) {
            data[i] -= vector.data[i];
        }
        return *this;
    }

    Vector operator*(double const value) const {
        Vector<dim> result;
        for (std::size_t i = 0; i < dim; i++) {
            result[i] = data[i] * value;
        }
        return result;
    }

    Vector& operator*=(double const& value) {
        for (std::size_t i = 0; i < dim; i++) {
            data[i] *= value;
        }
        return *this;
    }

    Vector operator/(double const& value) const {
        Vector<dim> result;
        for (std::size_t i = 0; i < dim; i++) {
            result[i] = data[i] / value;
        }
        return result;
    }

    Vector& operator/=(double const& value) {
        for (std::size_t i = 0; i < dim; i++) {
            data[i] /= value;
        }
        return *this;
    }

    double& operator[](std::size_t index) {
        return data[index];
    }

    double const& operator[](std::size_t index) const {
        return data[index];
    }
};

template<std::size_t dim>
double abs(Vector<dim> const& vector) {
    double result = 0.0;
    for (std::size_t i = 0; i < dim; i++) {
        result += vector[i] * vector[i];
    }
    return std::sqrt(result);
}
