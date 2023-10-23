#include "lin_equation.hpp"

LinEquation::LinEquation(std::vector<std::vector<long double>>& A, std::vector<long double>& b, long double conditionalityNumber) : A(A), b(b), conditionalityNumber(conditionalityNumber) {
    x.resize(b.size());
}

const std::vector<std::vector<long double>>& LinEquation::getA() const {
	return A;
}

const std::vector<long double>& LinEquation::getb() const {
	return b;
}

const std::vector<long double>& LinEquation::getx() const {
    return x;
}

const long double LinEquation::getConditionalityNumber() const {
	return conditionalityNumber;
}

void LinEquation::displayMatrix(std::vector<std::vector<long double>> matrix)
{
    std::cout << "---- MATRIX ----" << std::endl;
    for (auto& row : matrix) {
        std::cout << "{";
        for (auto& element : row) {
            std::cout << std::setw(15) << element << " ";
        }
        std::cout << "}" << std::endl;
    }
}

void LinEquation::displayMatrix(std::vector<long double> matrix)
{
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
    std::vector<long double> c;
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