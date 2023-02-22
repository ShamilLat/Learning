#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include "07-02.cpp"

class Fab
{
private:
public:
    Fab (){}
    Fab (const Fab &a) = delete;
    Fab (Fab &&a) = delete;
    Fab &operator= (const Fab &a) = delete;
    Fab &operator= (Fab &&a) = delete;

    std::map<char, std::function<Figure * (std::string)>> fab
    {
        {'R', &Rectangle::make},
        {'S', &Square::make},
        {'C', &Circle::make}
    };

    Figure *create_fig (std::string str) {
        std::string s;
        char type;
        std::stringstream ss(str);
        ss >> type;
        getline(ss, s);
        return fab[type](s);
    }

    static Fab &factory_instance()
    {
        static Fab inst;
        return inst;
    }
};

bool sr (Figure *a, Figure *b)
{
    return a->get_square() < b->get_square();
}

int main()
{
    std::string str;
    std::vector<Figure *> ans;
    Fab f;

    while (getline(std::cin, str)) {
        ans.push_back(f.create_fig(str));
    }

    std::stable_sort(ans.begin(), ans.end(), sr);

    for (auto i = ans.begin(); i != ans.end(); i++) {
        std::cout << (*i)->to_string() << std::endl;
        delete *i;
    }
}