#include "solution.hpp"

int main()
{
	Solution solution;

	solution.readEquationsFromFile("matrices/matrices.matrs");
	solution.displayMatrices();
	return 0;
}
