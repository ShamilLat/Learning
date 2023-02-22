#include <iostream>
#include <string>
#include <sstream>
#include <stack>

int main()
{
    char a;
    std::string s;
    std::stack<std::string> m;
    while (std::cin >> a) {
        if (a >= 'a' && a <= 'z') {
            s = a;
            m.push(s);
        } else {
            std::string s1, s2;
            s1 = m.top();
            m.pop();
            s2 = m.top();
            m.pop();
            m.push("(" + s2 + a + s1 + ")");
        }
    }
    std::cout << m.top();
    m.pop();
}