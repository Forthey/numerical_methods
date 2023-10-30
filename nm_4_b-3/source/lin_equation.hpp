#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>


// Класс одного линейного уравнения
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
	 * \brief Конструктор по умолчанию
	 */
	LinEquation() = default;
	/**
	 * \brief Конструктор класса
	 * \param A - матрица системы
	 * \param b - свободный член
	 * \param conditionalityNumber - число обуслвленности
	 */
	LinEquation(Matrix& A, LinMatrix& b, long double l1, long double ln, long double conditionalityNumber);

	/**
	* \brief Функция, возвращающая матрицу A
	* \return матрица A
	*/
	const Matrix& getA() const;
	/**
	* \brief Функция, возвращающая матрицу b
	* \return матрица b
	*/
	const LinMatrix& getb() const;
	/**
	* \brief Функция, возвращающая корень
	* \return корень уравнения
	*/
	const LinMatrix& getx() const;
	/**
	* \brief Функция, возвращающая число обуцсловленности
	* \return число обусловленности
	*/
	const long double getConditionalityNumber() const;

	void buildIterator();

	/**
	* \brief Фукнция, считающая корень СЛАУ с помощью метода Зейделя
	*/
	void solve();
};

