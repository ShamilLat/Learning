#include <string>
#include <sstream>
#include <cmath>
#include "07-01.cpp"

class Rectangle : Figure
{
private:
    double a_;
    double b_;

public:
    Rectangle () {};
    Rectangle (double a, double b) : a_{a}, b_{b} {};

    static Rectangle* make(std::string str) {
        std::stringstream ss;
        ss.str(str);
        double a = 0, b = 0;
        ss >> a;
        ss >> b;
        Rectangle *r = new Rectangle;
        r->a_ = a;
        r->b_ = b;
        return r;
    }

    double get_square() const {
        return a_ * b_;
    }
};

class Square : Figure
{
private:
    double a_;

public:
    Square () {};
    Square (double a) : a_{a} {};

    static Square* make(std::string str) {
        std::stringstream ss;
        ss.str(str);
        double a = 0;
        ss >> a;
        Square* s = new Square;
        s->a_ = a;
        return s;
    }

    double get_square() const {
        return a_ * a_;
    }
};

class Circle : Figure
{
private:
    double r_;

public:
    Circle () {};
    Circle (double r) : r_{r} {};

    static Circle* make(std::string str) {
        std::stringstream ss;
        ss.str(str);
        double r = 0;
        ss >> r;
        Circle* c = new Circle;
        c->r_ = r;
        return c;
    }

    double get_square() const {
        return M_PI * r_ * r_;
    }
};