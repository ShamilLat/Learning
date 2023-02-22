#include <iostream>

int main()
{
    int count;
    std::cin >> count;

    Holder *mas = new Holder[count];
    int j = count - 1;
    for (int i = 0; i < count / 2; i++) {
        mas[i].swap(mas[j]);
        j--;
    }
    delete[] mas;
}