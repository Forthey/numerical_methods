#include "lin_equation.hpp"

LinEquation::LinEquation(Matrix& A, LinMatrix& b, long double conditionalityNumber) : A(A), b(b), conditionalityNumber(conditionalityNumber) {
    x.resize(b.size());
}

const Matrix& LinEquation::getA() const {
	return A;
}

const LinMatrix& LinEquation::getb() const {
	return b;
}

const LinMatrix& LinEquation::getx() const {
    return x;
}

const long double LinEquation::getConditionalityNumber() const {
	return conditionalityNumber;
}

LinMatrix LinEquation::doOneIteration(LinMatrix& x)
{
	for (size_t i = 0; i < x.size(); i++) {
	}
	return LinMatrix();
}

void LinEquation::solve()
{
}