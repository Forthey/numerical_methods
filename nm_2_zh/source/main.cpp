#include "solution.hpp"

int main()
{
	Solution solution1("matrices/matrices.matrs", "matrices/roots.matrs");
	solution1.begin();
	solution1.end();

	Solution solution2("matrices/hilbert_matrices.matrs", "matrices/hilbert_roots.matrs");
	solution2.begin();
	solution2.end();

	Solution solution3("matrices/zero_matrices.matrs", "matrices/zero_roots.matrs");
	solution3.begin();
	solution3.end();
	return 0;
}
