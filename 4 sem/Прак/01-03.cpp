#include <iostream>
#include <string>

int main()
{
    char liter, check_num = 0, check_null = 0;
    std::string res;
    while (std::cin >> std::noskipws >> liter) {
        if (liter >= '0' && liter <= '9') {
            if (liter == '0') {
                if (check_num) {
                    res.push_back(liter);
                } else {
                    check_null = 1;
                }
            } else {
                check_num = 1;
            }
        } else {
            if (check_null) {
                res.push_back('0');
            }
            check_num = 0;
        }
        if (liter != '0') {
            check_null = 0;
            res.push_back(liter);
        }
    }
    if (check_null) {
        res.push_back('0');
    }
    std::cout << res;
    return 0;
}