#include <iostream>
#include <iterator>
#include <functional>
#include <utility>

template <typename T>
using v_t = typename std::iterator_traits<T>::value_type;

template <class It1, class It2, class Func_M = std::function<v_t<It1>(v_t<It1>, v_t<It2>)>,
        class Func_A = std::function<v_t<It1>(v_t<It1>, v_t<It1>)> >
auto scalar_mul (It1 Ibeg, It1 Iend, It2 I2, v_t<It1> Init = v_t<It1>{}, 
        Func_M MulF = [](v_t<It1> a, v_t<It2> b){ return a * b; },
        Func_A AddF = [](v_t<It1> a, v_t<It1> b){ return a + b; })
{
    //auto res = Init;
    for (auto i1 = Ibeg; i1 != Iend; i1++) {
        Init = AddF(Init, MulF(*i1, *I2));
        I2++;
    }
    return Init;
}