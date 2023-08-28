#include <iostream>
#include <algorithm>

int main()
{
    int m, n;
    std::cin >> m >> n;
    int r1, c1, r2, c2;
    while (std::cin >> r1 >> c1 >> r2 >> c2) {
        if (r1 > r2) std::swap(r1, r2);
        if (c1 > c2) std::swap(c1, c2);

        std::cout << std::min(r2 - r1, r1 + m - r2) + std::min(c2 - c1, c1 + n - c2) << std::endl;
    }
}