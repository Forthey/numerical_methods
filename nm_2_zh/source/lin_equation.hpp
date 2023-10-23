#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>


// ����� ������ ��������� ���������
typedef std::vector<std::vector<long double>> Matrix;
typedef std::vector<long double> LinMatrix;
class LinEquation {
	// A * x = b
	Matrix A;
	LinMatrix b;
	long double conditionalityNumber;
	LinMatrix x;
	// A = LDLt
	Matrix L;
	LinMatrix D;

	/**
	 * \brief ������� ������� ������ � �������� ���������� ������� �� � ��������� �������
	 */
	void makeLDLt();
public:
	/**
	 * \brief ����������� �� ���������
	 */
	LinEquation() = default;
	/**
	 * \brief ����������� ������
	 * \param A - ������� �������
	 * \param b - ��������� ����
	 * \param conditionalityNumber - ����� ��������������
	 */
	LinEquation(Matrix& A, LinMatrix& b, long double conditionalityNumber);

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
	* \brief �������, ������������ ����� ����������������
	* \return ����� ���������������
	*/
	const long double getConditionalityNumber() const;

	/**
	* \brief �������, ��������� ������ ���� � ������� LDLt ����������
	*/
	void solve();
};

