#pragma once
#include <vector>

// Ax = b
class LinEquation {
	std::vector<std::vector<double>> A;
	std::vector<double> b;
	double conditionalityNumber;

	std::vector<double> x;
public:
	LinEquation() = default;
	LinEquation(std::vector<std::vector<double>>& A, std::vector<double>& b, double conditionalityNumber);

	const std::vector<std::vector<double>>& getA() const;
	const std::vector<double>& getb() const;
	const double getConditionalityNumber() const;

	std::vector<double>& solve();
};

