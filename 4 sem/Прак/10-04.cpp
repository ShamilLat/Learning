/*
    S -> aSd | bAc
    A -> bAc | eps
*/

#include <iostream>

enum {FALSE = 0xfffffffe};

void rec_A(int cnt)
{
    std::cout << 'b';
    if (cnt) rec_A(cnt - 1);
    std::cout << 'c';
}

void rec_S(int k, unsigned int cnt)
{
    std::cout << 'a';
    if (k > 0) rec_S(k - 1, cnt & FALSE);
    else rec_A((cnt >> 1) - 1);
    std::cout << 'd';
    if ((cnt & 1) && k > 0) {
        std::cout << "\n";
        rec_S(k - 1, cnt + 2);
    }
}


int main()
{
    int k;
    std::cin >> k;
    if (k % 2 == 0 && k > 2) rec_S((k - 2) / 2 - 1, 3);
    std::cout << "\n";
}