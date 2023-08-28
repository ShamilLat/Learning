#include <iostream>

class Sum
{
public:
    Sum(int c1, int c2) noexcept : val1_{c1}, val2_{c2} {};
    
    Sum(Sum c1, int c2) noexcept : val1_{c1.get()}, val2_{c2} {};
    
    int get() const {
        return val1_ + val2_;
    }

private:
    int val1_;
    int val2_;
};