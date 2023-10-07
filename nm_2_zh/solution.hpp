#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

#include "lin_equation.hpp"

class Solution {
	std::vector<LinEquation> linEquations;
	bool initialized = false;

	int eMin, eMax;
	int equationMatrixSize;
	int equationsCount;

	void readEquationsFromFile(const std::string &filename);
public:
	void begin(const std::string& inFilename, const std::string& outFilename);
	void displayMatrices();
	void writeMatrices(const std::string& filename);
};
