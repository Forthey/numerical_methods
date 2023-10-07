#include "lin_equation.hpp"

LinEquation::LinEquation(std::vector<std::vector<double>>& A, std::vector<double>& b, double conditionalityNumber) : A(A), b(b), conditionalityNumber(conditionalityNumber) {
}

const std::vector<std::vector<double>>& LinEquation::getA() const {
	return A;
}

const std::vector<double>& LinEquation::getb() const {
	return b;
}

const double LinEquation::getConditionalityNumber() const {
	return conditionalityNumber;
}

std::vector<double>& LinEquation::solve()
{

	return x;
}
