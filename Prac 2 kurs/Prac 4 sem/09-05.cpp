#include <iostream>
#include <cmath>
#include <algorithm>

enum 
{
    YEAR = 365,
    MONTH_IN_Y = 12,
    LEAP_Y = 4
};

int func(int y, int m, int d)
{
    int month[MONTH_IN_Y] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y % LEAP_Y == 0) month[1] = 29;
    int sum = y * YEAR;
    for (int i = 0; i < m - 1; i++) {
        sum += month[i];
    }
    sum += d;
    return sum;
}

int main()
{
    int y1, m1, d1, y2, m2, d2;
    unsigned int res = 0;
    char a;
    std::cin >> y1 >> a >> m1 >> a >> d1;
    while (std::cin >> y2 >> a >> m2 >> a >> d2) {
        for (int i = std::min(y1, y2) + 1; i < std::max(y1, y2); i++) {
            if (i % 4 == 0) res++;
        }
        res += std::abs(func(y1, m1, d1) - func(y2, m2, d2));
        y1 = y2, m1 = m2, d1 = d2;
    }
    std::cout << res << std::endl;
}