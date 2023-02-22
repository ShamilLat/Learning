#include <iostream>
#include <array>
#include <complex>
#include <array>
#include <vector>
#include <limits>

namespace Equations
{
    template <typename M>
    auto quadratic(std::array<std::complex<M>, 3> & v)
    {
        std::vector<std::complex<M>> ans;
        std::complex<M> four(4.0, 0);
        std::complex<M> two(2.0, 0);
        double null = 32 * std::numeric_limits<M>::epsilon();
        bool f = true;
        if (!(std::norm(v[2]) < null)) {
            std::complex<M> d = v[1] * v[1] - four * v[0] * v[2];
            ans.push_back((- v[1] - std::sqrt(d)) / (two * v[2]));
            ans.push_back((- v[1] + std::sqrt(d)) / (two * v[2]));
        } else if (!(std::norm(v[1]) < null)) {
            ans.push_back(- v[0] / v[1]);
        } else if (std::norm(v[0]) < null) {
            f = false;
        }
        return std::make_pair(f, ans);
    }
}