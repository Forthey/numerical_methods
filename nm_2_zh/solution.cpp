#include "solution.hpp"

void Solution::readEquationsFromFile(const std::string& filename) {
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << filename << ": not exist" << std::endl;
		return;
	}

	file >> equationMatrixSize >> eMin >> eMax;

	equationsCount = abs(eMax - eMin) + 1;

	std::vector<std::vector<long double>> A;
	std::vector<long double> b;
	A.resize(equationMatrixSize);
	b.resize(equationMatrixSize);
	for (auto& row : A) {
		row.resize(equationMatrixSize);
	}
	long double conditionalityNumber;

	for (int matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		file >> conditionalityNumber;
		for (int i = 0; i < equationMatrixSize; i++) {
			for (int j = 0; j < equationMatrixSize; j++) {
				file >> A[i][j];
			}
		}
		for (int i = 0; i < equationMatrixSize; i++) {
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
	for (int matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		const LinEquation& linEquation = linEquations[matrIndex];

		std::cout << matrIndex + 1 << ". Matrix conditionality number = " << linEquation.getConditionalityNumber() << std::endl;
		for (int i = 0; i < equationMatrixSize; i++) {
			std::cout << "{ ";
			for (int j = 0; j < equationMatrixSize; j++) {
				std::cout << std::setw(15) << linEquation.getA()[i][j] << " ";
			}
			std::cout << "}\t{ " << linEquation.getb()[i] << " }" << std::endl;
		}
	}
}

void Solution::writeMatrices(const std::string& filename) {
	std::ofstream file;
	file.open(filename, std::ofstream::out);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << filename << ": not exist" << std::endl;
		return;
	}

	for (auto& linEquation : linEquations) {
		std::vector<long double> x = linEquation.getx();
		for (auto& row : x) {
			file << std::setprecision(20) << row << " ";
		}
		file << "\n";
	}
}

void Solution::begin(const std::string& inFilename, const std::string& outFilename) {
	try {
		readEquationsFromFile(inFilename);

		for (auto& linEquation : linEquations) {
			linEquation.solve();
		}

		writeMatrices(outFilename);
	}
	catch (std::exception& exception) {
		const std::string what = exception.what();
		if (what == "A norm is zero") {
			std::cout << "Looks like some of A matrices have zero norm, exiting..." << std::endl;
		}
		return;
	}
}