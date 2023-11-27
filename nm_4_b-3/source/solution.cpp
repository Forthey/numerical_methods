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
	for (int matrIndex = 0; matrIndex < equationsCount; matrIndex++) {
		file >> matrixSize >> eigenvalue1 >> eigenvaluen;

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
		linEquations.push_back(LinEquation(A, b, eigenvalue1, eigenvaluen));
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

	const long double fixedEpsilon = pow(10, -10);

	for (size_t i = 0; i < equationsCount; i++) {
		LinEquation &linEquation = linEquations[i];
		if (i == 0) {
			for (int j = 1; j <= 12; j++) {
				LinEquation tmp = linEquation;

				linEquation.solve(pow(10, -j));
				LinMatrix x = linEquation.getx();
				for (auto& row : x) {
					file << std::setprecision(15) << row << " ";
				}
				file << "\n";

				linEquation = tmp;
			}
			std::cout << std::endl;
		}
		linEquation.solve(fixedEpsilon);
		//print(linEquation.getx());
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
