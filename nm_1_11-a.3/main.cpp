#include <vector>
#include <iomanip>

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

#define E_MIN 2
#define E_MAX 15

/**
 * \brief функция, считающая корень для полинома для различной точности и выводящая всё на экран 
 */
void testFirstFunc()
{
  drawLine(60);
  std::cout << "POLYNOM HPM" << std::endl;
  drawLine(60);
  const double a = 0.26, b = 0.5;
  std::vector<double> es;
  std::vector<unsigned> iters;
  std::vector<double> roots;

  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRoot(polyVar11, a, b, epsilon);
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
    roots.push_back(result.root);
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

  for (double& root : roots) {
      std::cout << root << " ";
  }
  std::cout << std::endl;

  es.clear();
  iters.clear();
  roots.clear();
  drawLine(60);
  std::cout << "POLYNOM FPI" << std::endl;
  drawLine(60);
  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRootForPolynom(polyVar11, pow(10, -i));
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
    roots.push_back(result.root);
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

  for (double& root : roots) {
      std::cout << root << " ";
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
  std::vector<double> roots;

  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRoot(complexVar11, a, b, epsilon);
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
    roots.push_back(result.root);
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

  for (double& root : roots) {
      std::cout << root << " ";
  }
  std::cout << std::endl;

  es.clear();
  iters.clear();
  roots.clear();
  drawLine(60);
  std::cout << "COMPLEX FPI" << std::endl;
  drawLine(60);
  for (int i = E_MIN; i <= E_MAX; i++) {
    const double epsilon = pow(10, -i);
    Result result = findRootForComplex(complexVar11, pow(10, -i));
    std::cout << epsilon << " " << result.root << " " << result.iterNumber << std::endl;
    es.push_back(epsilon);
    iters.push_back(result.iterNumber);
    roots.push_back(result.root);
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

  for (double& root : roots) {
      std::cout << root << " ";
  }
  std::cout << std::endl;

}


double testFunc(const double x)
{
  return x * x - 5;
}

Result findRoot_t(double(&f)(double), double a, double b, double epsilon) {
  if (a > b || epsilon < 0)
    throw "wrong input";

  unsigned iter = 0;
  while (b - a > epsilon && iter < MAX_ITER_NUM) {
    std::cout << "a = " << a << " b = " << b << " x = (a + b) / 2 = " << (a + b) / 2 << " dif = " << fabs(0.3065 - (a+b)/2) << std::endl;
    const double c = (a + b) / 2;
    if (f(a) * f(c) > 0)
      a = c;
    else
      b = c;
    iter++;
  }

  return Result(iter, (a + b) / 2);
}

Result findRootForPolynom_t(double(&f)(double), const double epsilon)
{
  const double a = 0.26, b = 0.5, M = 15, m = 5.93, q = (M - m) / (M + m), alpha = 2 / (m + M);
  double x1 = a, x2 = b;
  unsigned iter = 0;

  while (fabs(q / (1 - q) * (x2 - x1)) > epsilon)
  {
    const double tmp = x1;
    x1 = x2 - alpha * f(x2);
    x2 = tmp;
    std::cout << "x = " << x2 << " x* = " << x1 << " root = (x + x*) / 2 = " << (x2 + x1) / 2 << " dif = " << fabs(0.3065 - (x2 + x1) / 2) << std::endl;
    iter++;
  }
  return Result(iter, (x1 + x2) / 2);
}

void simulateCalc() {
  std::cout << "Simulating calc..." << std::endl;
  findRoot_t(polyVar11, 0.26, 0.5, 0.001);
  findRootForPolynom_t(polyVar11, 0.001);
} 
int main()
{
  std::cout << std::fixed;
  std::cout << std::setprecision(15);

  testFirstFunc();
  testSecondFunc();
  std::cout << std::setprecision(3);
  simulateCalc();
	return 0;
}
