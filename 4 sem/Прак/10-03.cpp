#include <iostream>
#include <map>
#include <string>

void m_null(int m[4]) {
    for (int i = 0; i < 4; i++) {
        m[i] = 0;
    }
}

int main()
{
    std::string in;
    //std::map <char, int> m = {{'a', 0}, {'0', 1}, {'b', 2}, {'1', 3}};
    std::map <int, char> m { {0, 'a'}, {1, '0'}, {2, 'b'}, {3, '1'} };
    int cnt[4] = {};
    while (std::cin >> in) {
        m_null(cnt);
        int flag = 1;
        int set_mode = 0;
        long unsigned int i = 0;
        while (i < in.size()) {
            if (set_mode == 4 || in.size() < 4) {
                flag = 0;
                break;
            }
            if (m[set_mode] == in[i]) {
                cnt[set_mode]++;
                i++;
                continue;
            }
            if (i == 0) flag = 0;
            set_mode++;
        }
        if (set_mode != 3 || cnt[0] != cnt[2] || cnt[1] != cnt[3]) flag = 0;
        std::cout << flag << std::endl;
    }
}