#include <iostream>

int main()
{
    std::string str;
    while (std::cin >> str) {
        //auto s = str.size();
        unsigned int i = 0;
        while ((str[i] == '3' || str[i] == '4') && i < str.length()) {
            i++;
        }
        while ((str[i] == '1' || str[i] == '2') && i < str.length()) {
            i++;
        }
        std::cout << (i == str.length()) << std::endl;
    }
}