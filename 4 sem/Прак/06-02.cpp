#include <iostream>
#include <map>

enum { MOD_NUM = 4294967161 };

int main()
{
    std::map<std::pair <unsigned int, unsigned int>, unsigned long long> m;
    unsigned int str = 0, st = 0, m_num = 0;
    unsigned long long num = 0;
    while (std::cin >> str >> st >> num) {
        if (num == MOD_NUM) {
            m_num = 1;
            continue;
        }
        if (!m_num) {
            m[{str, st}] = num;
        } else if (m.find({str, st}) != m.end()){
            m[{str, st}] = (m[{str, st}] + num) % MOD_NUM;
            if (m[{str, st}] == 0) {
                m.erase({str, st});
            }
        } else {
            m[{str, st}] = num;
        }
    }
    
    for (auto & i : m) {
        std::cout << i.first.first << " " << i.first.second << " " << i.second << std::endl;
    }
}