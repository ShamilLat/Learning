#include <iostream>
#include <vector>
#include <stdint.h>

void process(std::vector<uint64_t> &v, uint32_t s)
{
    std::vector <uint64_t> v1;
    v1.reserve(v.size() + v.size() / s);
    uint32_t cnt = 0;
    auto poz = v.begin();
    auto poz1 = v1.begin();
    auto i = v.begin();
    bool flag = 0;
    for (; i != v.end(); i++) {
        if (cnt == s) {
            cnt = 0;
            uint64_t sum = 0;
            for (auto j = poz; j < i; j++) {
                sum += *j;
            }
            if (flag) {
                sum += *poz1; 
            }
            flag = 1;
            poz = i;
            i--;
            poz1 = v1.end();
            v1.push_back(sum);

        } else {
            v1.push_back(*i);
            cnt++;
        }
    }
    if (cnt == s) {
        uint64_t sum = 0;
        for (auto j = poz; j != i; j++) {
            sum += *j;
        }
        if (flag) {
            sum += *poz1; 
        }
        v1.push_back(sum);
    }
    v.reserve(v.size() + v.size() / s);
    v = v1;
}