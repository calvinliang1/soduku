#include <iostream>
#include <cassert>
#include <fstream>
#include "Subroku.h"
int main()
{
	Subroku a(3);
	a.solvedSoduku();
	std::ofstream output_file1("Solved.txt");
	assert(output_file1.is_open());
	output_file1<<a;
	a.createSoduku();
	std::cout<<a;
}