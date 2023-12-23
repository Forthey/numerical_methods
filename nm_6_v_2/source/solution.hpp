#pragma once
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

// Класс решения
typedef std::vector<long double> Vector;
typedef std::vector<Vector> Matrix;
typedef std::pair<long double, int> LyambdaPair;
class Solution {
	// матрица
	Matrix A;
	// массив пар с.ч. - число итераций
	std::vector<LyambdaPair> minLyambdas;
	// массив собственных векторов
	std::vector<Vector> vectors;
    std::vector<long double> notNormedMinLyambdas;

	// Файл, в из которого сичтывается матрицы
	const std::string inFilename;
	// Файл, в который записывается матрицы
	const std::string outFilename;
	// Диапазон значений эпсилон (10^e_min;10^e_max)
	int e_min = 0, e_max = 0;
	const long double minEpsilon = pow(10, -13);
	bool initialized = false;

	/**
	 * \brief Функция, считывающая матрицу из заданного файла
	 */
	void readMatrixFromFile();
	/**
	 * \brief Функция, записывающая минимальное с.ч. в заданный файл
	 */
	void writeLyambdasAndVectors();

	/**
	 * \brief Функция, считающая максимальное с.ч. методом скалярных произведений
	 * \param A - матрица, у которой надо посчитать с.ч.
	 * \param normed - нужно ли нормировать векторы
	 * \param epsilon - точность числа
	 * \return пару чисел - собственное число и число итераций
	 */
	std::pair<LyambdaPair, Vector> findLyambda(const Matrix& A, bool normed, long double epsilon);
	/**
	 * \brief Функция, считающая минимальное с.ч. методом скалярных произведений
	 * \param epsilon - точность числа
	 * \return пару чисел - собственное число и число итераций
	 */
	std::pair<long double, int> findLyambdas(long double epsilon);

	/**
	 * \brief Функция, нормированный вектор
	 * \param X - вектор
	 * \return нормир. вектор
	 */
	Vector normalize(const Vector& X);
	/**
	* \brief Функция, считающая длину вектора
	* \param X - вектора
	* \return длина вектора
	*/
	long double len(const Vector& X);
public:
	/**
	 * \brief Конструктор класса
	 * \param inFilename - файл, из которого считываются матрицы
	 * \param outFilename - файл, в который записываются матрицы
	 */
	explicit Solution(const std::string& inFilename, const std::string& outFilename);

	/**
	 * \brief Функция, считающая с.ч. у матрицы
	 */
	void begin();

	/**
	 * \brief Функция, вызываемая при завершении вычислений
	 */
	void end();
};
