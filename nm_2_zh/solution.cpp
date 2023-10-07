#include "solution.hpp"

void Solution::readEquationsFromFile(std::string filename) {
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << filename << ": not exist" << std::endl;
		return;
	}

	file >> equationMatrixSize >> eMin >> eMax;

	equationsCount = eMax - eMin + 1;

	std::vector<std::vector<double>> A;
	std::vector<double> b;
	A.resize(equationMatrixSize);
	b.resize(equationMatrixSize);
	for (auto& row : A) {
		row.resize(equationMatrixSize);
	}
	double conditionalityNumber;

	for (size_t matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		file >> conditionalityNumber;
		for (size_t i = 0; i < equationMatrixSize; i++) {
			for (size_t j = 0; j < equationMatrixSize; j++) {
				file >> A[i][j];
			}
		}
		for (size_t i = 0; i < equationMatrixSize; i++) {
			file >> b[i];
		}
		linEquations.push_back(LinEquation(A, b, conditionalityNumber));
	}
	file.close();
	initialized = true;
}

void Solution::displayMatrices() {
	if (!initialized) {
		std::cout << "<Matrix is not initialized>" << std::endl;
		return;
	}
	for (size_t matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		const LinEquation& linEquation = linEquations[matrIndex];

		std::cout << matrIndex + 1 << ". Matrix conditionality number = " << linEquation.getConditionalityNumber() << std::endl;
		for (size_t i = 0; i < equationMatrixSize; i++) {
			std::cout << "{ ";
			for (size_t j = 0; j < equationMatrixSize; j++) {
				std::cout << std::setw(15) << linEquation.getA()[i][j] << " ";
			}
			std::cout << "}\t{ " << linEquation.getb()[i] << " }" << std::endl;
		}
	}
}