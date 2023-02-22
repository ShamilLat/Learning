#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdio.h>
#include <iomanip>
#include <map>
#include <vector>
#include <functional>

namespace numbers
{

    complex eval(const std::vector<std::string> &args, const complex &z)
    {
        int i = 0;
        std::map <char, std::function <void(void)> > op;
        complex_stack st;
        op['('] = [&st, &args, &i]() {
            complex a = complex(args[i]);
            st = st << a;
        };
        op['z'] = [&st, &z]() {
            st = st << z;
        };
        op['+'] = [&st]() {
            complex a = +st;
            st = ~st;
            complex b = +st;
            st = ~st;
            st = st << (a + b);
        };
        op['-'] = [&st]() {
            complex a = +st;
            st = ~st;
            complex b = +st;
            st = ~st;
            st = st << (b - a);
        };
        op['*'] = [&st]() {
            complex a = +st;
            st = ~st;
            complex b = +st;
            st = ~st;
            st = st << (a * b);
        };
        op['/'] = [&st]() {
            complex a = +st;
            st = ~st;
            complex b = +st;
            st = ~st;
            st = st << (b / a);
        };
        op['!'] = [&st]() {
            st = st << (+st);
        };
        op[';'] = [&st]() {
            st = ~st;
        };
        op['~'] = [&st]() {
            complex a = +st;
            st = ~st;
            st = st << ~a;
        };
        op['#'] = [&st]() {
            complex a = +st;
            st = ~st;
            st = st << -a;
        };
        int v_size = args.size();
        for (i = 0; i < v_size; i++) {
            op[args[i][0]]();
        }
        return +st;
    }
}