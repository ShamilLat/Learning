#include <iostream>
#include <map>

enum { MOD_NUM = 4294967161 };

int main()
{
    std::map<unsigned int, std::map<unsigned int, unsigned long long >> m1, m2;
    unsigned int str = 0, st = 0, m_num = 0;
    unsigned long long num = 0;
    while (std::cin >> str >> st >> num) {
        if (num == MOD_NUM) {
            m_num = 1;
            continue;
        }
        if (!m_num) {
            m1[st][str] = num;
        } else {
            unsigned int i2 = 0;
            for (auto & i : m1[str]) {
                i2 = i.first;
                m2[i2][st] = (m2[i2][st] + i.second * num) % MOD_NUM;
                if (m2[i2][st] == 0) {
                    m2[i2].erase(st);
                }
            }
        }
    }
    for (auto & i : m2) {
        for (auto & j : i.second) {
            std::cout << i.first << " " << j.first << " " << j.second << std::endl;
        }
    }
}