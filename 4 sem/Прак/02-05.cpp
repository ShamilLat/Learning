#include <string>

class BinaryNumber
{
private:
    std::string s_;

public:
    BinaryNumber (const std::string &s) : s_(s) {};
    operator std::string () const {
        return s_;
    }
    const BinaryNumber &operator++() {
        int a = s_.length() -  1;
        while (s_[a] == '1' && a >= 0) {
            s_[a] = '0';
            a--;
        }
        if (a == -1) {
            s_ = "1" + s_;
        } else {
            s_[a] = '1';
        }
        return *this;
    }
};