#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::map <char, std::vector<std::string> > m;
    std::map <char, bool> check;
    char left;
    std::string right;
    int cnt = 0;
    while (std::cin >> left >> right) {
        m[left].push_back(right);
        if (check[left]);
        cnt++;
        if (left == 'S') {
            check[left] = true;
        }
    }
    for (int i = 0; i < cnt; i++) {
        for (auto j = m.begin(); j != m.end(); j++) {
            for (auto k = (j->second).begin(); k != (j->second).end(); k++) {
                for (unsigned str_poz = 0; str_poz < (*k).size(); str_poz++) {
                    if ((*k)[str_poz] >= 'A' && (*k)[str_poz] <= 'Z' && check[j->first]) {
                        check[(*k)[str_poz]] = true;
                    }
                }
            }
        }
    }

    for (auto i = check.begin(); i != check.end(); i++) {
        if (check[i->first] == false) {
            m.erase(i->first);
        }
    }

    for (auto i = m.begin(); i != m.end(); i++) {
        for (auto j = (i->second).begin(); j != (i->second).end(); j++) {
            std::cout << i->first << " " << *j << "\n";
        }
    }
}