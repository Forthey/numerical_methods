#include "lin_equation.hpp"

long double infNorm(Matrix& A) {
	long double maxRowSum = 0;
	for (auto& row : A) {
		long double curRowSum = 0;
		for (auto& el : row) {
			curRowSum += abs(el);
		}
		if (curRowSum > maxRowSum) {
			maxRowSum = curRowSum;
		}
	}
	return maxRowSum;
}

LinEquation::LinEquation(Matrix& A, LinMatrix& b, long double l1, long double ln) : A(A), b(b), a(2.0/(l1+ln)), dim(b.size()), epsilon(0) {
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

LinMatrix LinEquation::doOneIteration(LinMatrix& x)
{
	LinMatrix x1 = x;
	for (size_t i = 0; i < dim; i++) {
		for (size_t j = 0; j < i; j++) {
			x1[i] += -a * A[i][j] * x1[j];
		}

		for (size_t j = i; j < dim; j++) {
			x1[i] += -a * A[i][j] * x[j];
		}

		x1[i] += a * b[i];
	}
	return x1;
}

bool LinEquation::isConditionMet(LinMatrix& x1, LinMatrix& x0)
{
	return norm(x1 - x0) > epsilon;
}

void print(LinMatrix A) {
	for (auto& a : A) {
		std::cout << std::setprecision(10) << a << std::endl;;
	}
	std::cout << std::endl;
}

void print(Matrix A) {
	for (auto& row : A) {
		for (auto& a : row) {
			std::cout << std::setprecision(15) << a << " ";
		}
		std::cout << std::endl;
	}
}

void LinEquation::solve(long double epsilon)
{
	this->epsilon = epsilon;
	LinMatrix x1 = b, x0 = b, oldx0 = b;

	int iter = 0;
	do {
		x0 = oldx0;
		x1 = doOneIteration(x0);
		oldx0 = x1;
		iter++;
	} while (isConditionMet(x1, x0));

	std::cout << iter << " ";
	x = x1;
}

LinMatrix operator*(Matrix A, LinMatrix x)
{
	LinMatrix Ax(x.size());

	for (size_t i = 0; i < x.size(); i++) {
		for (size_t j = 0; j < x.size(); j++)
		{
			Ax[i] += x[j] * A[i][j];
		}	
	}
	return Ax;
}

LinMatrix operator+(LinMatrix A, LinMatrix B) {
	LinMatrix sum(A.size());
	for (size_t i = 0; i < A.size(); i++) {
		sum[i] = A[i] + B[i];
	}

	return sum;
}

LinMatrix operator-(LinMatrix A, LinMatrix B) {
	LinMatrix diff(A.size());
	for (size_t i = 0; i < A.size(); i++) {
		diff[i] = A[i] - B[i];
	}

	return diff;
}

LinMatrix operator/(LinMatrix A, long double a) {
	LinMatrix result(A.size());
	for (size_t i = 0; i < A.size(); i++) {
		result[i] = A[i] / a;
	}

	return result;
}

long double norm(LinMatrix A) {
	long double sumsq = 0;
	for (long double& a : A) {
		sumsq += a * a;
	}
	return sqrt(sumsq);
}