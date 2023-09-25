#pragma once
#include <iostream>
#include <cmath>
#include <climits>

/// �����, ������� ����� ��� ���� - ��� �������� ����� �������� � ��� �������� �����
class Result {
public:
	explicit Result(unsigned iterNumber, double root) : iterNumber(iterNumber), root(root) {};

	const unsigned iterNumber = 0;
	const double root;
};

#define MAX_ITER_NUM ULLONG_MAX
/**
 * \brief ������� ������� ������ � �������� ���������� ������� �� � ��������� �������
 * @param f �������, � � ������� ������ ������
 * @param a ����� �������
 * @param b ������ �������
 * @param epsilon ��������
 * @return ��� Result � ������� ���������� ��� ���� - ������ � ����� ��������
 */
Result findRoot(double(&f)(double), double a, double b, double epsilon);

/**
 * \brief ������� ������� ������ � �������� ���������� ������� ������� �������� � ��������� ������� ��� ��������
 * @param f �������
 * @param epsilon ��������
 * @return ��� Result � ������� ���������� ��� ���� - ������ � ����� ��������
 */
Result findRootForPolynom(double(&f)(double), double epsilon);
/**
 * \brief ������� ������� ������ � �������� ���������� ������� ������� �������� � ��������� ������� ��� �������������� �������
 * @param f ��������������� �������
 * @param epsilon ��������
 * @return ��� Result � ������� ���������� ��� ���� - ������ � ����� ��������
 */
Result findRootForComplex(double(&f)(double), double epsilon);