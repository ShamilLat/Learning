#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int main(int argc, char *argv[])
{
    numbers::complex l(0,0);
    numbers::complex c(argv[1]);

    std::stringstream conv1(argv[2]);
    std::stringstream conv2(argv[3]);
    
    std::vector <std::string> st;
    
    double r;
    conv1 >> r;
    
    int n;
    conv2 >> n;
    
    for (int i = 4; i < argc; i++) {
        st.push_back(argv[i]);
    }

    numbers::complex now;
    numbers::complex prev = c + numbers::complex(r, 0);
    numbers::complex x_mid;

    for (int i = 0; i < n; i++) {
        now = c + numbers::complex(r * cos(M_PI * (2 * i + 2) / n), r * sin(M_PI * (2 * i + 2) / n));
        x_mid = c + numbers::complex(r * cos(M_PI * (2 * i + 1) / n), r * sin(M_PI * (2 * i + 1) / n));
        
        l = l + numbers::eval(st, x_mid) * (now - prev);
        
        prev = now;
    }
    std::cout << l.to_string() << std::endl;
    return 0;
}