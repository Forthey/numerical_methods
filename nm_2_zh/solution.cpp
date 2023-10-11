#include "solution.hpp"

Solution::Solution(const std::string& inFilename, const std::string& outFilename) : inFilename(inFilename), outFilename(outFilename) {

}

void Solution::readEquationsFromFile() {
	std::ifstream file;
	file.open(inFilename, std::ifstream::in);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << inFilename << ": not exist" << std::endl;
		return;
	}

	file >> eMin >> eMax;

	equationsCount = abs(eMax - eMin) + 1;

	std::vector<std::vector<long double>> A;
	std::vector<long double> b;
	long double conditionalityNumber;
	int matrixSize;
	for (int matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		file >> matrixSize >> conditionalityNumber;

		A.resize(matrixSize);
		for (int i = 0; i < matrixSize; i++) {
			A[i].resize(matrixSize);
			for (int j = 0; j < matrixSize; j++) {
				file >> A[i][j];
			}
		}
		b.resize(matrixSize);
		for (int i = 0; i < matrixSize; i++) {
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
		const int matrixSize = linEquation.getA().size();

		std::cout << matrIndex + 1 << ". Matrix conditionality number = " << linEquation.getConditionalityNumber() << std::endl;
		for (int i = 0; i < matrixSize; i++) {
			std::cout << "{ ";
			for (int j = 0; j < matrixSize; j++) {
				std::cout << std::setw(15) << linEquation.getA()[i][j] << " ";
			}
			std::cout << "}\t{ " << linEquation.getb()[i] << " }" << std::endl;
		}
	}
}

void Solution::writeMatrices() {
	std::ofstream file;
	file.open(outFilename, std::ofstream::out);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << outFilename << ": not exist" << std::endl;
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

void Solution::parseError(const std::string& error)
{
	if (error == "A norm is zero") {
		std::cout << "Looks like some of A matrices have zero norm, exiting..." << std::endl;
	}
}

void Solution::begin() {
	try {
		readEquationsFromFile();

		if (!initialized) {
			std::cout << "Solution is not initialized, exiting..." << std::endl;
			return;
		}

		for (auto& linEquation : linEquations) {
			linEquation.solve();
		}

		writeMatrices();
	}
	catch (std::exception& exception) {
		parseError(exception.what());	
		end();
		return;
	}
}

void Solution::end()
{
	linEquations.clear();
	initialized = false;
}
