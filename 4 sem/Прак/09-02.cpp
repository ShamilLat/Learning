#include <iostream>

class Result
{
public:
    long long num;
    Result(){}
};

void func(long long a, long long b, unsigned int k) {
    Result res;
    try {
        switch (k)
        {
            case 0:
                res.num = a + b;
                throw res;
                break;
            default:
                if (b == 1) {
                    res.num = a;
                    throw res;
                } else if (b > 1) {
                    try {
                        func(a, b - 1, k);
                    } catch (Result b) {
                        try {
                            func(a, b.num, k - 1);
                        } catch(Result c) {
                            throw c;
                        }
                    }
                }
                break;
        }
    } catch (Result ans) {
        throw ans;
    }
}

int main()
{
    long long a, b;
    unsigned int k;
    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        } catch(Result res) {
            std::cout << res.num << std::endl;
        }
    }
}