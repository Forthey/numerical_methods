#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

// Класс решения
typedef std::vector<long double> Vector;
typedef std::vector<Vector> Matrix;
class Solution {
	// матрица
	Matrix A;
	std::vector<std::pair<long double, int>> minLyambdas;

	// Файл, в из которого сичтывается матрицы
	const std::string inFilename;
	// Файл, в который записывается матрицы
	const std::string outFilename;
	// Диапазон значений эпсилон (10^e_min;10^e_max)
	long double e_min = 0, e_max = 0;
	const long double minEpsilon = pow(10, -13);
	bool initialized = false;

	/**
	 * \brief Функция, считывающая матрицу из заданного файла
	 */
	void readMatrixFromFile();
	/**
	 * \brief Функция, записывающая минимальное с.ч. в заданный файл
	 */
	void writeLyambdas();

	/**
	 * \brief Функция, считающая максимальное с.ч. методом скалярных произведений
	 * \param A - матрица, у которой надо посчитать с.ч.
	 * \param normed - нужно ли нормировать векторы
	 * \param epsilon - точность числа
	 */
	std::pair<long double, int> findLyambda(const Matrix& A, bool normed, long double epsilon);
	/**
	 * \brief Функция, считающая минимальное с.ч. методом скалярных произведений
	 */
	std::pair<long double, int> findLyambdas(long double epsilon);

	Vector normalize(const Vector& X);
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
