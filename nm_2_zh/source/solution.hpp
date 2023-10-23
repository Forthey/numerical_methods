#pragma once
#include <fstream>

#include "lin_equation.hpp"

// ����� �������
class Solution {
	// ������ ���� ����
	std::vector<LinEquation> linEquations;
	// ����, � �� �������� ����������� ����
	const std::string inFilename;
	// ����, � ������� ������������ ����
	const std::string outFilename;

	bool initialized = false;
	int eMin = 0, eMax = 0;
	int equationsCount = 0;

	/**
	 * \brief �������, ����������� ������� �� ��������� �����
	 */
	void readEquationsFromFile();
	/**
	 * \brief �������, ������������ ������� � �������� ����
	 */
	void writeMatrices();
	/**
	 * \brief ������� ��������� ������
	 * \param error - ������
	 */
	void parseError(const std::string& error);
public:
	/**
	 * \brief ����������� ������
	 * \param inFilename - ����, �� �������� ����������� �������
	 * \param outFilename - ����, � ������� ������������ �������
	 */
	explicit Solution(const std::string& inFilename, const std::string& outFilename);

	/**
	 * \brief �������, ��������� ����� � ���� ����
	 */
	void begin();

	/**
	 * \brief �������, ���������� ��� ���������� ����������
	 */
	void end();

	/**
	 * \brief ���������� ������
	 */
	~Solution();
};
