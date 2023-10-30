#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>


// ����� ������ ��������� ���������
typedef std::vector<std::vector<long double>> Matrix;
typedef std::vector<long double> LinMatrix;

LinMatrix operator*(Matrix A, LinMatrix x);
LinMatrix operator+(LinMatrix A, LinMatrix B);

class LinEquation {
	// A * x = b
	Matrix A;
	LinMatrix b;
	long double conditionalityNumber;
	LinMatrix x;
	size_t dim;
	long double a;
	Matrix C, C1, C2;
	LinMatrix g;

	/**
	 * \brief ...
	 */
	LinMatrix doOneIteration(LinMatrix& x);
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
	LinEquation(Matrix& A, LinMatrix& b, long double l1, long double ln, long double conditionalityNumber);

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

	void buildIterator();

	/**
	* \brief �������, ��������� ������ ���� � ������� ������ �������
	*/
	void solve();
};

