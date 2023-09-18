﻿// nm_1_11-a.3.cpp: определяет точку входа для приложения.
//
#include <cmath>
#include <vector>
#include "task1.hpp"


/**
 * \brief функция, считающая значения полинома в точке x
 * \param x переменная
 * \return значение полинома в точке x
 */
double polyVar11(const double x) {
	return 2 * pow(x, 4) + 8 * pow(x, 3) + 8 * pow(x, 2) - 1;
}
/**
 * \brief функция, считающая значения транс фукнции в точке x
 * \param x переменная
 * \return значение функции в точке x
 */
double complexVar11(const double x)
{
  return 2 * atan(x) - x - 3;
}

void drawLine(unsigned length)
{
  for (unsigned i = 0; i < length; i++)
    std::cout << "-";
  std::cout << std::endl;
}

#define E_MIN 1
#define E_MAX 10

/**
 * \brief функция, считающая корень для полинома для различной точности и выводящая всё на экран 
 */
void testFirstFunc()
{
  drawLine(60);
  std::cout << "POLYNOM HPM" << std::endl;
  drawLine(60);
  const double a = 0.26, b = 1.85;
  std::vector<double> es;
  std::vector<unsigned> iters;

  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRoot(polyVar11, a, b, epsilon);
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
  }
  
  for (double &e : es)
  {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  for (unsigned &iter : iters)
  {
    std::cout << iter << " ";
  }
  std::cout << std::endl;

  es.clear();
  iters.clear();
  drawLine(60);
  std::cout << "POLYNOM FPI" << std::endl;
  drawLine(60);
  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRootForPolynom(polyVar11, pow(10, -i));
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
  }


  for (double& e : es)
  {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  for (unsigned& iter : iters)
  {
    std::cout << iter << " ";
  }
  std::cout << std::endl;
}

/**
 * \brief функция, считающая корень трансцедентной фукнции для различной точности и выводящая всё на экран
 */
void testSecondFunc()
{
  drawLine(60);
  std::cout << "COMPLEX HPM" << std::endl;
  drawLine(60);
  const double a = -6, b = -4;
  std::vector<double> es;
  std::vector<unsigned> iters;

  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRoot(complexVar11, a, b, epsilon);
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
  }

  for (double& e : es)
  {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  for (unsigned& iter : iters)
  {
    std::cout << iter << " ";
  }
  std::cout << std::endl;

  es.clear();
  iters.clear();
  drawLine(60);
  std::cout << "COMPLEX FPI" << std::endl;
  drawLine(60);
  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRootForComplex(complexVar11, pow(10, -i));
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
  }

  for (double& e : es)
  {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  for (unsigned& iter : iters)
  {
    std::cout << iter << " ";
  }
  std::cout << std::endl;
}

int main()
{
  testFirstFunc();
  testSecondFunc();

	return 0;
}
