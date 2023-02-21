#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>

bool sr(unsigned int a, unsigned int b) {
    return a > b;
}

void print (std::map<std::pair<int, int>, unsigned int> &matr) {    
    int i = 0, flag = 0;
    for (auto & it : matr) {
        flag = 1;
        if (it.first.first == i + 1) {
            std::cout << std::endl;
            i++;
        } else if (it.first.second != 0) {
            std::cout << " ";
        }
        std::cout << it.second;
    }
    if (flag) std::cout << std::endl;
}

int main()
{
    std::map<std::pair<int, int>, unsigned int, std::less<std::pair<int, int> > > matr;
    unsigned int num;
    int i = 0, j = 0;
    std::string s;
    std::istringstream ss;
    
    while (std::getline(std::cin, s)) {
        if (s.size() == 0) break;
        ss.clear();
        ss.str(s);
        
        while (ss >> num) {
            matr[{i, j}] = num;
            j++;
        }
        i++;
        j = 0;
    }

    i = 0;
    j = 0;
    unsigned int max_num = 0;
    
    std::vector <unsigned int> pop;

    while (std::cin >> num) {
        pop.push_back(num);
    }
    std::sort(pop.begin(), pop.end(), sr);

    for (auto pop_i = pop.begin(); pop_i < pop.end(); pop_i++) {
        num = *pop_i;
        unsigned int num1 = num / 2;
        unsigned int num2 = num1 / 2;
        for (auto & it : matr) {
            if (it.second > max_num) {
                max_num = it.second;
                i = it.first.first;
                j = it.first.second;
            }
        }
        for (int i1 = i - 1; i1 <= i + 1; i1++) {
            for (int j1 = j - 1; j1 <= j + 1; j1++) {
                auto search = matr.find({i1, j1});
                if (search != matr.end()) {
                    if (i1 == i && j1 == j) {
                        if (num > matr[{i1, j1}]){
                            matr[{i1, j1}] = 0;
                        } else {
                            matr[{i1, j1}] -= num;
                        }
                    } else if ((i + j) % 2 == (i1 + j1) % 2) {
                        if (num2 > matr[{i1, j1}]){
                            matr[{i1, j1}] = 0;
                        } else {
                            matr[{i1, j1}] -= num2;
                        }
                    } else if ((i + j) % 2 != (i1 + j1) % 2) {
                        if (num1 > matr[{i1, j1}]){
                            matr[{i1, j1}] = 0;
                        } else {
                            matr[{i1, j1}] -= num1;
                        }
                    }
                }
            }
        }
        max_num = 0;
    }
    
    print(matr);
}