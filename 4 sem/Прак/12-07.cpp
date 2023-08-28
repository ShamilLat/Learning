#include <iostream>

char c;
void A();
void B();
void gc()
{
    std::cin >> c;
}

void S()
{
    gc();
    if (c == 'a') {
        A();
        gc();
        if (c != 'b') {
            throw c;
        }
    } else if (c == 'c') {
        B();
    } else {
        throw c;
    }    
}

void A()
{
    gc();
    if (c == 'c') {
        A();
        gc();
        if (c != 'd') {
            throw c;
        }
    } else if (c != 'e') {
        throw c;
    }
}

void B()
{
    if (std::cin >> c) {
        if (c == 'b') {
            B();
        } else if (c != 'd'){ 
            throw c;
        }
    }
}

int main()
{
    try
    {
        S();
        if (std::cin >> c)
            std::cout << 0;
        else std::cout << 1;
    }
    catch(char c)
    {
        std::cout << 0;
    }
    
}