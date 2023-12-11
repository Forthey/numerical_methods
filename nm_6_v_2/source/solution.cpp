#include "solution.hpp"

template <typename T>
void print(const T& what) {
	std::cout << what << std::endl;
}

void print(const Matrix& A) {
	for (auto& row : A) {
		for (auto& el : row) {
			std::cout << el << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

long double operator*(const Vector& A, const Vector& B);
Vector operator*(const Matrix& A, const Vector& B);
Matrix operator*(long double k, const Matrix& A);
Vector operator*(long double k, const Vector& A);

Matrix operator-(const Matrix& A, const Matrix& B) {
	Matrix AmB = A;
	for (size_t i = 0; i < A.size(); i++) {
		for (size_t j = 0; j < A.size(); j++) {
			AmB[i][j] = A[i][j] - B[i][j];
		}
	}
	return AmB;
}

Vector operator*(const Matrix& A, const Vector& B)
{
	size_t size = A.size();
	Vector Ans(size);
	if (A.size() != B.size()) {
		return Ans;
	}
	for (size_t i = 0; i < size; i++) {
		Ans[i] = 0;
		for (size_t j = 0; j < size; j++) {
			Ans[i] += A[i][j] * B[j];
		}
	}
	return Ans;
}

Matrix operator*(long double k, const Matrix& A)
{
	Matrix kA = A;
	for (auto& row : kA) {
		for (auto& el : row) {
			el *= k;
		}
	}
	return kA;
}

Vector operator*(long double k, const Vector& A)
{
	Vector kA = A;
	for (auto& el : kA) {
		el *= k;
	}
	return kA;
}

long double operator*(const Vector& A, const Vector& B)
{
	long double answer = 0;
	if (A.size() != B.size()) {
		return 0.0;
	}
	for (size_t i = 0; i < A.size(); i++) {
		answer += A[i] * B[i];
	}
	return answer;
}

Matrix E(size_t size) {
	Matrix A(size);
	for (size_t i = 0; i < size; i++) {
		A[i].resize(size);
		A[i][i] = 1;
	}
	return A;
}

Solution::Solution(const std::string& inFilename, const std::string& outFilename) : inFilename(inFilename), outFilename(outFilename) {
	e_min = e_max = 0;
}

void Solution::readMatrixFromFile() {
	std::ifstream file;
	file.open(inFilename, std::ifstream::in);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << inFilename << ": not exist" << std::endl;
		return;
	}

	file >> e_max >> e_min;

	int matrixSize;
	file >> matrixSize;
	A.resize(matrixSize);
	for (int i = 0; i < matrixSize; i++) {
		A[i].resize(matrixSize);
		for (int j = 0; j < matrixSize; j++) {
			file >> A[i][j];
		}
	}
	file.close();
	initialized = true;
}

void Solution::writeLyambdas() {
	std::ofstream file;
	file.open(outFilename, std::ofstream::out);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << outFilename << ": not exist" << std::endl;
		return;
	}

	for (int i = minLyambdas.size() - 1; i >= 0; i--) {
		file << std::setprecision(15) << minLyambdas[i].first << std::endl;
		std::cout << minLyambdas[i].second << " ";
	}
}

std::pair<long double, int> Solution::findLyambda(const Matrix& A, bool normed, long double epsilon)
{
	long double lyambda = 0, newLyambda = 0;
	int iter = 0;
	Vector X = A[0];
	if (normed) {
		do {
			lyambda = newLyambda;
			Vector Y = normalize(X);
			X = A * Y;
			newLyambda = X * Y;
			iter++;
		} while (abs(newLyambda - lyambda) > epsilon);
	}
	else {
		do {
			lyambda = newLyambda;
			Vector Y = X;
			X = A * Y;
			newLyambda = X * X / (X * Y);
			iter++;
		} while (abs(newLyambda - lyambda) > epsilon);
	}
	return { newLyambda, iter };
}

std::pair<long double, int> Solution::findLyambdas(long double epsilon)
{
	std::pair<long double, int> answer1, answer2;

	answer1 = findLyambda(A, true, epsilon);
	Matrix B = A - answer1.first * E(A.size());
	answer2 = findLyambda(B, true, epsilon / A.size() / A.size());

	return { answer1.first + answer2.first, answer1.second + answer2.second };
}

Vector Solution::normalize(const Vector& X)
{
	Vector normedX = X;
	long double normX = len(X);
	for (auto& x : normedX) {
		x /= normX;
	}
	return normedX;
}

long double Solution::len(const Vector& X)
{
	long double length = 0;
	for (auto& el : X) {
		length += el * el;
	}
	return sqrt(length);
}

void Solution::begin() {
	readMatrixFromFile();

	if (!initialized) {
		std::cout << "Solution is not initialized, exiting..." << std::endl;
		return;
	}

	for (int i = e_min; i <= e_max; i++) {
		int index = i - e_min;
		minLyambdas.push_back(findLyambdas(pow(10, i)));
	}
	writeLyambdas();
	end();
}

void Solution::end()
{
	A.clear();
	initialized = false;
}
