#include <iostream>

void f (int a)
{
	a = 5;
}

void f1 (int *a)
{
	*a = 5;
}

int main()
{
	int a = 6;
	f(a);
	std::cout << a << std::endl;
	f1(&a);
	std::cout << a << std::endl;
}