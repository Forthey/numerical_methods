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

	Matrix A;
	LinMatrix b;
	int matrixSize;
	long double eigenvalue1, eigenvaluen;
	long double conditionalityNumber;
	for (int matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		file >> matrixSize >> eigenvalue1 >> eigenvaluen >> conditionalityNumber;

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
		linEquations.push_back(LinEquation(A, b, eigenvalue1, eigenvaluen, conditionalityNumber));
	}
	file.close();
	initialized = true;
}

void Solution::writeMatrices() {
	std::ofstream file;
	file.open(outFilename, std::ofstream::out);
	if (!file.is_open()) {
		std::cout << "Cannot open the file " << outFilename << ": not exist" << std::endl;
		return;
	}

	for (auto& linEquation : linEquations) {
		LinMatrix x = linEquation.getx();
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

Solution::~Solution()
{
	end();
}
