#include <iostream>
#include <algorithm>

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
    if (p1.row > p2.row) std::swap(p1c.row, p2c.row);
    if (p1.col > p2.col) std::swap(p1c.col, p2c.col);

    auto check1 = std::min(p2c.row - p1c.row, p1c.row + f.row - p2c.row);
    auto check2 = std::min(p2c.row - p1c.row, p1c.col + f.col - p2c.col);
    auto check = std::min(check1, check2);

    check1 = std::min(p2c.row - p1c.row - check, p1c.row + f.row - p2c.row - check);
    check2 = std::min(p2c.col - p1c.col - check, p1c.col + f.col - p2c.col - check);
    check += std::max(check1, check2);
    return check;
}