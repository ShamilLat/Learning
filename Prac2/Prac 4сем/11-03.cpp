#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map <std::pair<std::string, char>, std::string> m;
    std::map <std::string, bool> end;
    std::string cur, start_state, nnew;
    char cchar;

    while (std::cin >> cur) {
        if (cur == "END") {
            break;
        }
        std::cin >> cchar >> nnew;
        m.insert({{cur, cchar}, nnew});
    }
    while (std::cin >> cur) {
        if (cur == "END") {
            break;
        }
        end.insert({cur, true});
    }
    
    std::cin >> start_state >> cur;
    unsigned int let_cnt = 0, flag = 1;
    for (unsigned int i = 0; i < cur.size(); i++) {
        if (m.find({start_state, cur[i]}) != m.end()) {
            start_state = m[{start_state, cur[i]}];
            let_cnt++;
        } else {
            flag = 0;
            break;
        }
    }
    if (flag && end.find(start_state) == end.end()) {
        flag = 0;
    }
    std::cout << flag << "\n" << let_cnt << "\n" << start_state << "\n";
}