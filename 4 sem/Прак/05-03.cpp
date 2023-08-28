#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>

template <typename It, typename f>
void myapply(It begin, It end, f func)
{
    for (It i = begin; i < end; i++) {
        func(*i);
    }
}

template <typename Type, typename f>
void myapply(Type *begin, Type *end, f func)
{
    for (Type *i = begin; i < end; i++) {
        func(*i);
    }
}

template <typename It, typename F>
std::vector <std::reference_wrapper <typename It::value_type> > myfilter2 (It begin, It end, F func)
{
    std::vector <std::reference_wrapper <typename It::value_type> > new_v;
    for (It it = begin; it != end; it++) {
        if (func(*it)) {
            new_v.insert(new_v.end(), *it);
        }
    }
    return new_v;
}

template <typename Type, typename F>
std::vector <std::reference_wrapper <Type> > myfilter2 (Type *begin, Type *end, F func)
{
    std::vector <std::reference_wrapper <Type> > new_v;
    for (Type *it = begin; it != end; it++) {
        if (func(*it)) {
            new_v.insert(new_v.end(), *it);
        }
    }
    return new_v;
}