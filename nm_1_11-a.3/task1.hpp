#pragma once
#include <iostream>

/// Класс, который имеет два поля - для хранения числа итераций и для хранения корня
class Result {
public:
	explicit Result(unsigned iterNumber, double root) : iterNumber(iterNumber), root(root) {};

	const unsigned iterNumber = 0;
	const double root;
};

#define MAX_ITER_NUM ULLONG_MAX
/**
 * \brief Функция находит корень в заданном промежутке методом ПД с точностью эпсилон
 * @param f функция, с у которой ищется корень
 * @param a левая граница
 * @param b правая граница
 * @param epsilon точность
 * @return тип Result в котором содержатся два поля - корень и число итераций
 */
Result findRoot(double(&f)(double), double a, double b, double epsilon);

/**
 * \brief Функция находит корень в заданном промежутке методом простых итераций с точностью эпсилон для полинома
 * @param f полином
 * @param epsilon точность
 * @return тип Result в котором содержатся два поля - корень и число итераций
 */
Result findRootForPolynom(double(&f)(double), double epsilon);
/**
 * \brief Функция находит корень в заданном промежутке методом простых итераций с точностью эпсилон для трансцендентой функции
 * @param f трансцендентная функция
 * @param epsilon точность
 * @return тип Result в котором содержатся два поля - корень и число итераций
 */
Result findRootForComplex(double(&f)(double), double epsilon);