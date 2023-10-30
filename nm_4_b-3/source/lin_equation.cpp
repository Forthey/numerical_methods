#include "lin_equation.hpp"

LinEquation::LinEquation(Matrix& A, LinMatrix& b, long double l1, long double ln, long double conditionalityNumber) : A(A), b(b), a(2.0/(l1+ln)), conditionalityNumber(conditionalityNumber), dim(0) {
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

void LinEquation::buildIterator()
{
	C.resize(dim);
	g.resize(dim);

	for (size_t i = 0; i < dim; i++) {
		C[i].resize(dim);
		for (size_t j = 0; j < dim; j++) {
			C[i][j] = -a * A[i][j];
		}
		g[i] = -a * b[i];
	}
	C1.resize(dim);
	C2.resize(dim);
	for (size_t i = 0; i < dim; i++) {
		C1[i].resize(dim);
		C2[i].resize(dim);
		for (size_t j = 0; j < dim; j++) {
			if (i == j) {
				C1[i][j] = 0;
				C2[i][j] = C[i][j];
			}
			else if (i > j) {
				C1[i][j] = 0;
				C2[i][j] = C[i][j];
			}
			else {
				C1[i][j] = C[i][j];
				C2[i][j] = 0;
			}
		}
	}
}

LinMatrix LinEquation::doOneIteration(LinMatrix& x)
{
	return C1 * x + C2 * x + b;
}

void LinEquation::solve()
{
	buildIterator();
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
	LinMatrix sum;
	for (size_t i = 0; i < A.size(); i++) {
		sum[i] = A[i] + B[i];
	}

	return sum;
}