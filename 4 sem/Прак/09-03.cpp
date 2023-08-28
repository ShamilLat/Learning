#include <iostream>

class S
{
private:
    int a;
    bool check, output_check;

public:

    S()
    {
        if (std::cin >> a) {
            check = 1;
        } else {
            a = 0;
            check = 0;
        }
        output_check = check;
    }
    S(S &&b)
    {
        if (std::cin >> a) {
            check = 1;
        } else {
            a = 0;
            check = 0;
        }
        b.output_check = 0;
        output_check = 1;
        a += b.a;
    }
    ~S()
    {
        if (output_check) std::cout << a << std::endl;
    }
    operator bool() { return check; }
};