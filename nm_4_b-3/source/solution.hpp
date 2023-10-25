#pragma once
#include <fstream>

#include "lin_equation.hpp"

// Класс решения
class Solution {
	// Массив всех СЛАУ
	std::vector<LinEquation> linEquations;
	// Файл, в из которого сичтываются СЛАУ
	const std::string inFilename;
	// Файл, в который записываются СЛАУ
	const std::string outFilename;

	bool initialized = false;
	int eMin = 0, eMax = 0;
	int equationsCount = 0;

	/**
	 * \brief Функция, сичтывающая матрицы из заданного файла
	 */
	void readEquationsFromFile();
	/**
	 * \brief Функция, записывающая матрицы в заданный файл
	 */
	void writeMatrices();
	/**
	 * \brief Функция обработки ошибок
	 * \param error - ошибка
	 */
	void parseError(const std::string& error);
public:
	/**
	 * \brief Конструктор класса
	 * \param inFilename - файл, из которого считываются матрицы
	 * \param outFilename - файл, в который записываются матрицы
	 */
	explicit Solution(const std::string& inFilename, const std::string& outFilename);

	/**
	 * \brief Функция, считающая корни у всех СЛАУ
	 */
	void begin();

	/**
	 * \brief Функция, вызываемая при завершении вычислений
	 */
	void end();

	/**
	 * \brief Деструктор класса
	 */
	~Solution();
};
