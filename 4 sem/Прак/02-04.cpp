#include <iostream>

int main()
{
    char a = 0, a_pr;
    int count = 1, oct_check = 0, c_flag = 1; 
    
    while (std::cin >> std::noskipws >> a) {
        if (c_flag) {
            a_pr = a;
            if (a == '#') oct_check = 1;
            c_flag = 0;
        } else {        
            if (a_pr == a) {
                count++;
                a_pr = a;
            } else {
                if (oct_check) {
                    std::cout << "##" << std::hex << count << '#';
                    count = 1;
                } else {
                    if (count > 4) {
                        std::cout << '#' << a_pr << std::hex << count << '#';
                    } else {
                        for (int i = 0; i < count; i++) {
                            std::cout << a_pr;
                        }
                    }
                    count = 1;
                }
            
                if (a == '#') {
                    oct_check = 1;
                } else {
                    oct_check = 0;
                }
                a_pr = a;
            }
        }
    }
    if (!c_flag) {
        if (oct_check) {
            std::cout << "##" << std::hex << count << '#';
        } else {
            if (count > 4) {
                std::cout << '#' << a_pr << std::hex << count << '#';
            } else {
                for (int i = 0; i < count; i++) {
                    std::cout << a_pr;
                }
            }
        }            
    }
    return 0;
}