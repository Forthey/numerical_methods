#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

// ����� �������
typedef std::vector<long double> Vector;
typedef std::vector<Vector> Matrix;
typedef std::pair<long double, int> LyambdaPair;
class Solution {
	// �������
	Matrix A;
	// ������ ��� �.�. - ����� ��������
	std::vector<LyambdaPair> minLyambdas;
	// ������ ����������� ��������
	std::vector<Vector> vectors;

	// ����, � �� �������� ����������� �������
	const std::string inFilename;
	// ����, � ������� ������������ �������
	const std::string outFilename;
	// �������� �������� ������� (10^e_min;10^e_max)
	int e_min = 0, e_max = 0;
	const long double minEpsilon = pow(10, -13);
	bool initialized = false;

	/**
	 * \brief �������, ����������� ������� �� ��������� �����
	 */
	void readMatrixFromFile();
	/**
	 * \brief �������, ������������ ����������� �.�. � �������� ����
	 */
	void writeLyambdasAndVectors();

	/**
	 * \brief �������, ��������� ������������ �.�. ������� ��������� ������������
	 * \param A - �������, � ������� ���� ��������� �.�.
	 * \param normed - ����� �� ����������� �������
	 * \param epsilon - �������� �����
	 */
	std::pair<LyambdaPair, Vector> findLyambda(const Matrix& A, bool normed, long double epsilon);
	/**
	 * \brief �������, ��������� ����������� �.�. ������� ��������� ������������
	 * \param epsilon - �������� �����
	 */
	std::pair<long double, int> findLyambdas(long double epsilon);

	Vector normalize(const Vector& X);
	long double len(const Vector& X);
public:
	/**
	 * \brief ����������� ������
	 * \param inFilename - ����, �� �������� ����������� �������
	 * \param outFilename - ����, � ������� ������������ �������
	 */
	explicit Solution(const std::string& inFilename, const std::string& outFilename);

	/**
	 * \brief �������, ��������� �.�. � �������
	 */
	void begin();

	/**
	 * \brief �������, ���������� ��� ���������� ����������
	 */
	void end();
};
