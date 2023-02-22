#include <iostream>

template <typename stl> typename stl::value_type process (const stl &v)
{
    typename stl::value_type sum = typename stl::value_type();
    if (!v.empty()) {
        int i = 0;
        for (typename stl::const_reverse_iterator it = v.rbegin(); it != v.rend() && i < 5; it++) {
            if (i % 2 == 0) {
                sum += *it;
            }
            i++;
        }
    }
    return sum;
}