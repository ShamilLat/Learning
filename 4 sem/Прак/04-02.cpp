#include <iostream>
#include <vector>

void process (std::vector<long long> &v, long long n) {
    if (!v.empty()) {
        v.reserve(2 * v.size());
        auto i = v.end() - 1;
        auto i_begin = v.begin();
        for(; i >= i_begin; i--) {
            if (*i >= n) v.push_back(*i);
        }
    }
}