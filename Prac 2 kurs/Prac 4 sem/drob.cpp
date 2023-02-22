#include <stdio.h>
#include <iostream>

using namespace std;

class drob{
private:
    int ch, zn;

public:
    drob() {
        ch = 0;
        zn = 0;
    }
    
    drob (int a, int b) : ch{a}, zn{b} {}
   
    int getch()
    {
        return ch;
    }
    
    int getzn()
    {
        return zn;
    }

    void write() {
        printf("%d/%d\n", ch, zn);
    }
    
    void prod(drob a) {
        this->ch *= a.getch();
        this->zn *= a.getzn();
    }
    
    drob operator*= (drob a) {
        this->ch *= a.getch();
        this->zn *= a.getzn();
    }
    
    drob operator+= (drob a) {
        this->ch = ch * a.getzn() + a.getch() * zn;
        this->zn *= a.getzn();
    }

    friend drob operator + (drob a, drob b);
};

drob operator + (drob a, drob b) {
    a += b;
    return a;
}

int main()
{
    drob a(4,8), b(2,5), c;
    a = a + b;
    a.write();

    return 0;
}