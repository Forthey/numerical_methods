#include <iostream>
#include <fstream>
#include <iomanip>


class Matrix {
	double A[10][10];
	bool initialized = false;

public:
	void readFromFile(std::string filename) {
		std::ifstream file;
		file.open(filename, std::ifstream::in);
		if (!file.is_open()) {
			std::cout << "Cannot open the file " << filename << ": not exist" << std::endl;
			return;
		}
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				file >> A[i][j];
			}
		initialized = true;
	}

	void display() {
		if (!initialized) {
			std::cout << "<Matrix is not initialized>" << std::endl;
			return;
		}
		for (int i = 0; i < 10; i++) {
			std::cout << "{ ";
			for (int j = 0; j < 10; j++) {
				std::cout << std::setw(3) << A[i][j] << " ";
			}
			std::cout << "}" << std::endl;
		}
	}
};

int main()
{
	Matrix matrix;
	matrix.readFromFile("matrix.matr");
	matrix.display();
	return 0;
}
