#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>


// Класс одного линейного уравнения
typedef std::vector<std::vector<long double>> Matrix;
typedef std::vector<long double> LinMatrix;

// Utility функции для произведения операций над матрицами

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

	// Коэффициент альфа в итерациях
	long double a;

	// Точность
	long double epsilon;

	/**
	 * \brief Функция, считающая новое приближение на основе старого
	 * \param x - старое приближение
	 * \return новое приближение
	 */
	LinMatrix doOneIteration(LinMatrix& x);

	/**
	 * \brief функция, проверяющая, больше ли норма разности между приближениями, чем эпсилон
	 * \param x1 - новое приближение
	 * \param x0 - старое приближение
	 * \return больше ли норма всё еще, чем эпсилон
	 */
	bool isConditionMet(LinMatrix& x1, LinMatrix& x0);
public:
	/**
	 * \brief Конструктор по умолчанию
	 */
	LinEquation() = default;
	/**
	 * \brief Конструктор класса
	 * \param A - матрица системы
	 * \param b - свободный член
	 * \param l1 - первое собственное число
	 * \param ln - последнее собственное число
	 */
	LinEquation(Matrix& A, LinMatrix& b, long double l1, long double ln);

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
	* \brief Фукнция, считающая корень СЛАУ с помощью метода Зейделя
	* \param epsilon - точность нахождения
	*/
	void solve(long double epsilon);
};

