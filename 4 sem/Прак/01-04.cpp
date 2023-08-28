#include <iostream>
#include <iomanip> 
#include <cmath>

int main()
{
    double rez1 = 0, rez2 = 0, num, count = 0;
    while (std::cin >> num) {
        rez1 += num;
        rez2 += num * num;
        count++;
    }
    rez2 -= rez1 * rez1 / count;
    std::cout << std::setprecision(10) << rez1 / count << std::endl;
    std::cout << std::setprecision(10) << sqrt(rez2 / count) << std::endl;
}