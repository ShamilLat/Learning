#include <iostream>
#include <ctype.h>

int main()
{
    char s;
    int one_cnt = 0, null_cnt = 0, check_r = 1, last_s = 0, curr_one_cnt = 0, curr_null_cnt = 0;
    int flag = 1, check_output = 0;
    while (std::cin >> std::noskipws >> s) {
        if (!isspace(s)) {
            if (s != '1' && s != '0')
                flag = 0;
            check_output = 1;
            if (check_r) {
                if (s == '0') {
                    if (last_s) {
                        curr_null_cnt = 1;
                        check_r = 0;
                        last_s = 0;
                    } else {
                        null_cnt++;
                    }
                } else if (s == '1') { 
                    one_cnt++;
                    last_s = 1;
                }
            } else {
                if (s == '0') {
                    if (last_s) {
                        if (curr_one_cnt != one_cnt || curr_null_cnt != null_cnt) {
                            flag = 0;
                        } else {
                            curr_null_cnt = 1;
                            curr_one_cnt = 0;
                        }
                        last_s = 0;
                    } else {
                        curr_null_cnt++;
                    }
                } else if (s == '1') {
                    curr_one_cnt++;
                    last_s = 1;
                }
            }
        } else if (check_output) {
            if (!null_cnt || !one_cnt) flag = 0;
            if ((curr_one_cnt || curr_null_cnt) && (curr_one_cnt != one_cnt || curr_null_cnt != null_cnt)) flag = 0;
            std::cout << flag << std::endl;
            check_output = 0;
            one_cnt = 0;
            null_cnt = 0;
            check_r = 1;
            last_s = 0;
            curr_one_cnt = 0;
            curr_null_cnt = 0;
            flag = 1;
        }
    }
    if (check_output) {
        if (!null_cnt || !one_cnt) flag = 0;
        if ((curr_one_cnt || curr_null_cnt) && (curr_one_cnt != one_cnt || curr_null_cnt != null_cnt)) flag = 0;
        std::cout << flag << std::endl;
    }
}