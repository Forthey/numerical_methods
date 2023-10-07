#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

#include "lin_equation.hpp"

class Solution {
	std::vector<LinEquation> linEquations;
	bool initialized = false;

	size_t eMin, eMax;
	size_t equationMatrixSize;
	size_t equationsCount;
public:
	void readEquationsFromFile(std::string filename);
	void displayMatrices();
};
