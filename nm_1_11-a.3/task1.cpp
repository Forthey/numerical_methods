#include "Task1.hpp"

Result findRoot(double(&f)(double), double a, double b, double epsilon) {
	if (a > b || epsilon < 0)
		throw "wrong input";

	unsigned iter = 0;
	while (b - a > epsilon && iter < MAX_ITER_NUM) {
		const double c = (a + b) / 2;
		if (f(a) * f(c) > 0)
			a = c;
		else
			b = c;
		iter++;
	}

	return Result(iter, (a + b) / 2);
}

Result findRootForPolynom(double(&f)(double), const double epsilon)
{
	const double a = 0.26, b = 0.5, M = 15, m = 5.93, q = (M - m) / (M + m), alpha = 2 / (m + M);
	double x1 = a, x2 = b;
	unsigned iter = 0;

	while (fabs(q / (1 - q) * (x2 - x1)) > epsilon)
	{
		const double tmp = x1;
		x1 = x2 - alpha * f(x2);
		x2 = tmp;
		iter++;
	}
	return Result(iter, (x1 + x2) / 2);
}

Result findRootForComplex(double(&f)(double), const double epsilon)
{
	const double a = -6, b = -4, M = -0.88, m = -0.95, q = (M - m) / (M + m), alpha = 2 / (m + M);
	double x1 = a, x2 = b;
	unsigned iter = 0;

	while (fabs(q / (1 - q) * (x2 - x1)) > epsilon)
	{
		const double tmp = x1;
		x1 = x2 - alpha * f(x2);
		x2 = tmp;
		iter++;
	}
	return Result(iter, (x1 + x2) / 2);
}
