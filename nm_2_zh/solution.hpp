#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

#include "lin_equation.hpp"

class Solution {
	std::vector<LinEquation> linEquations;
	const std::string inFilename;
	const std::string outFilename;
	bool initialized = false;
	int eMin = 0, eMax = 0;
	int equationsCount = 0;

	void readEquationsFromFile();
	void displayMatrices();
	void writeMatrices();

	void parseError(const std::string& error);
public:
	explicit Solution(const std::string& inFilename, const std::string& outFilename);

	void begin();
	void end();
};
