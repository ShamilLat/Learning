#include <iostream>
#include <string>

class Object
{
public:
    std::string a;
    Object() {}
    Object(std::string b) : a{b} {}
    ~Object() {
        std::cout << a << "\n";
    }
};

void rec()
{
    std::string a;
    if (std::cin >> a) {
        Object b(a);
        rec();
    }
    throw 0;
}

int main()
{
    try {
        rec();
    } catch (int) {}
}