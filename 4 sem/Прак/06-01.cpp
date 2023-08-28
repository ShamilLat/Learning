#include <iostream>
#include <iomanip>

int main() {
    int w1 = 0, w2 = 0;
    std::cin >> w1 >> w2;
    unsigned int num;
    double cnt = 0, likes = 0;
    while (std::cin >> num) {
        for (int i = 0; i < 32; i++) {
            if (num % 2) {
                likes++;
            }
            num = num >> 1;
            cnt++;
        }
    }
    
    if (w2 < likes) {
        std::cout << std::setprecision(10) << (double)(-1 + 2 * (likes - w2) / cnt) << " "; 
    } else {
        std::cout << -1 << " ";
    }

    if (w1 < cnt - likes) {
        std::cout << std::setprecision(10) << (double)(-1 + 2 * (likes + w1) / cnt) << std::endl;
    } else {
        std::cout << 1 << std::endl;
    }
}