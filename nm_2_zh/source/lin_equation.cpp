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

void LinEquation::makeLDLt() {
    const int size = A.size();
    D.resize(size);
    L.resize(size);
    for (auto& row : L) {
        row.resize(size);
    }

    long double sum = 0;
    for (int j = 0; j < size; j++)
        for (int i = j; i < size; i++)
        {
            sum = A[i][j];
            for (int k = 0; k < j; k++)
                sum = sum - L[j][k] * D[k] * L[i][k];
            if (j == i)
            {
                D[j] = sum;
                L[j][j] = 1;
            }
            else if (D[j] == 0) {
                throw std::runtime_error("A norm is zero");
            }
            else {
                L[i][j] = sum / D[j];
            }
        }
}


void LinEquation::solve()
{
    makeLDLt();

    int size = L.size();
    LinMatrix c;
    c.resize(size);

    // L * c = b
    for (int i = 0; i < size; i++) {
        c[i] = b[i];
        for (int j = 0; j < i; j++) {
            c[i] -= L[i][j] * c[j];
        }
    }

    // Lt * x = D^-1 * c = c'
    for (int i = 0; i < size; i++) {
        c[i] = c[i] / D[i];
    }

    // Lt * x = c'
    for (int i = size - 1; i >= 0; i--) {
        x[i] = c[i];
        for (int j = size - 1; j > i; j--) {
            x[i] -= L[j][i] * x[j];
        }
    }

    L.clear();
    D.clear();
}