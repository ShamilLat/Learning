#include <iostream>
#include <vector>
#include <algorithm>

void process (const std::vector <int> &v1, std::vector <int> &v2) {
    if (!v1.empty() && !v2.empty()) {
        std::vector <int> v1_cpy;
        for (auto i = v1.begin(); i < v1.end(); i++) {
            v1_cpy.push_back(*i);
        }
        std::sort(v1_cpy.begin(), v1_cpy.end());
        std::vector<int>::iterator i1 = std::unique(v1_cpy.begin(), v1_cpy.end());
        v1_cpy.erase(i1, v1_cpy.end());
        
        i1 = v1_cpy.begin();

        int count_minus = 0, count_large = 0;
        while (i1 < v1_cpy.end()) {
            if (*i1 < 0)
                count_minus++;
            if (v2.begin() + *i1 >= v2.end())
                count_large++;
            i1++;
        }
        
        v1_cpy.erase(v1_cpy.begin(), v1_cpy.begin() + count_minus);
        v1_cpy.erase(v1_cpy.end() - count_large, v1_cpy.end());
        
        v2.reserve(2 * v2.size());
        i1 = v1_cpy.begin();
        std::vector<int>::iterator i2 =  v2.begin();
        std::vector<int>::iterator i2_end =  v2.end();
        
        if (v1_cpy.size()) {
            for (; i2 < i2_end; i2++) {
                if (i1 < v1_cpy.end() && i2 - v2.begin() == *i1) {
                    i1++;
                } else {
                    v2.push_back(*i2);
                }
            }
            v2.erase(v2.begin(), i2_end);
        }
    }
}