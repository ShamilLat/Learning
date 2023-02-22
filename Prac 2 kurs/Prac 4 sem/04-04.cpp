#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct M {
    double count{0}, sum{0};
    void operator() (double n) {
        sum += n;
        count++;
    }
};

int main() {
    
    std::vector <double> vec;
    double num;
    int count = 0;
    while (std::cin >> num) {
        vec.push_back(num);
        count++;
    }
    int del_cnt = count / 10;
    
    count -= 2 * del_cnt;
    int del_m = count / 10;

    std::sort(vec.begin() + del_cnt, vec.end() - del_cnt);
    M res = std::for_each(vec.begin() + del_cnt + del_m, vec.end() - del_cnt - del_m, M());

    std::cout << std::setprecision(10) << res.sum / res.count << std::endl;
    
}