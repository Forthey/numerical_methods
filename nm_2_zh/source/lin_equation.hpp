#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

// Ax = b
class LinEquation {
	std::vector<std::vector<long double>> A;
	std::vector<long double> b;
	long double conditionalityNumber;
	std::vector<long double> x;

	std::vector<std::vector<long double>> L;
	std::vector<long double> D;

	void makeLDLt();
public:
	LinEquation() = default;
	LinEquation(std::vector<std::vector<long double>>& A, std::vector<long double>& b, long double conditionalityNumber);

	const std::vector<std::vector<long double>>& getA() const;
	const std::vector<long double>& getb() const;
	const std::vector<long double>& getx() const;
	const long double getConditionalityNumber() const;

	static void displayMatrix(std::vector<std::vector<long double>> matrix);
	static void displayMatrix(std::vector<long double> matrix);

	void solve();
};

