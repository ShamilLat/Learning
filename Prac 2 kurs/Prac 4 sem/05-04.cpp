#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

template <typename It, typename It2>
It2 myremove (It b1, It e1, It2 b2, It2 e2)
{
    std::vector<int> v;
    for (auto i = b1; i != e1; i++) {
        v.push_back(*i);
    }
    std::sort(v.begin(), v.end());
    std::vector<int>::iterator i1 = std::unique(v.begin(), v.end());
    v.erase(i1, v.end());
    
    for (auto i = v.end() - 1; i >= v.begin(); i--) {
        if (*i < e2 - b2 && *i >= 0) {
            e2--;
            for (auto j = b2 + *i; j < e2; ) {
                std::swap(*j, *(j++));
            }
        }
    }
    return e2;    
}