#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>


// ����� ������ ��������� ���������
typedef std::vector<std::vector<long double>> Matrix;
typedef std::vector<long double> LinMatrix;

// Utility ������� ��� ������������ �������� ��� ���������

LinMatrix operator*(Matrix A, LinMatrix x);
LinMatrix operator+(LinMatrix A, LinMatrix B);
LinMatrix operator-(LinMatrix A, LinMatrix B);
LinMatrix operator/(LinMatrix A, long double a);
long double norm(LinMatrix A);

class LinEquation {
	// A * x = b
	Matrix A;
	LinMatrix b;
	LinMatrix x;
	size_t dim;

	// ����������� ����� � ���������
	long double a;

	// ��������
	long double epsilon;

	/**
	 * \brief �������, ��������� ����� ����������� �� ������ �������
	 * \param x - ������ �����������
	 * \return ����� �����������
	 */
	LinMatrix doOneIteration(LinMatrix& x);

	/**
	 * \brief �������, �����������, ������ �� ����� �������� ����� �������������, ��� �������
	 * \param x1 - ����� �����������
	 * \param x0 - ������ �����������
	 * \return ������ �� ����� �� ���, ��� �������
	 */
	bool isConditionMet(LinMatrix& x1, LinMatrix& x0);
public:
	/**
	 * \brief ����������� �� ���������
	 */
	LinEquation() = default;
	/**
	 * \brief ����������� ������
	 * \param A - ������� �������
	 * \param b - ��������� ����
	 * \param l1 - ������ ����������� �����
	 * \param ln - ��������� ����������� �����
	 */
	LinEquation(Matrix& A, LinMatrix& b, long double l1, long double ln);

	/**
	* \brief �������, ������������ ������� A
	* \return ������� A
	*/
	const Matrix& getA() const;
	/**
	* \brief �������, ������������ ������� b
	* \return ������� b
	*/
	const LinMatrix& getb() const;
	/**
	* \brief �������, ������������ ������
	* \return ������ ���������
	*/
	const LinMatrix& getx() const;

	/**
	* \brief �������, ��������� ������ ���� � ������� ������ �������
	* \param epsilon - �������� ����������
	*/
	void solve(long double epsilon);
};

