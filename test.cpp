#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
bool found(int value)
{
	if(value>10)
	{
		value++;
		return true;
	}
	return false;
}
int main()
{
	std::cout<<"Hi"<<std::endl;
	found(5);
}