#include <iostream>
#include <vector>

void process (const std::vector <unsigned long long> &v1, std::vector <unsigned long long> &v2, int i) {
    if (!v1.empty() && !v2.empty()) {
        auto i2 = v2.end() - 1;
        for (auto i1 = v1.begin(); i1 < v1.end() && i2 >= v2.begin(); i1 += i) {
            *i2 += *i1;
            i2--;
        }
    }
}