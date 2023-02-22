#include <iostream>
#include <cmath>
#include <algorithm>

namespace Game
{
    template <typename C>
    class Coord
    {
    public: 
        typedef C value_type;
        C row{}, col{};
        Coord () {};
        Coord (Coord & a) : row{a.row}, col{a.col} {};
        Coord (C a = C(), C b = C()) : row{a}, col{b} {};
    };

    template <typename C>
    typename C::value_type dist (C & f, C & p1, C & p2)
    {
        C p1c = p1;
        C p2c = p2;
        typename C::value_type change = 1;
        
        auto res = p1c.col;
        if (p1.col > p2.col) {
            change = -1;
        }
        while (p1c.col != p2c.col) {
            if (p1c.row < p2c.row) {
                if (p1c.col % 2 == 0) p1c.row++;
            } else if (p1c.row > p2c.row) {
                if (p1c.col % 2 != 0) p1c.row--; 
            }
            p1c.col += change;
        }
        return std::abs(p1c.row - p2c.row) + std::abs(p1c.col - res);
    }
}