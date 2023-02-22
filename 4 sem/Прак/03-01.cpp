#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdio.h>
#include <iomanip>

namespace numbers
{
    class complex
    {
    private:
        double re_, im_;
    public:
        complex (double re = 0, double im = 0) : re_(re), im_(im) {}
        explicit complex (std::string s) {
            std::stringstream a;
            a.str(s);
            char c;
            double num = 0;
            a >> c;
            a >> num; re_ = num;
            a >> c;
            a >> num; im_ = num;
        }

        double re() const {
            return re_;
        }
        double im() const {
            return im_;
        }
        double abs2() const {
            return re_ * re_ + im_ * im_;
        } 
        double abs() const {
            return sqrt(re_ * re_ + im_ * im_);
        }

        std::string to_string () const {
            std::stringstream res;
            res << "(" << std::setprecision(10) << re_ << "," << std::setprecision(10) << im_ << ")";
            return res.str();
        }

        complex & operator += (complex c)
        {
            re_ += c.re();
            im_ += c.im();
            return *this;
        }
        complex & operator -= (complex c)
        {
            re_ -= c.re();
            im_ -= c.im(); 
            return *this;
        }
        complex & operator *= (complex c)
        {
            double ch_ = re_;
            re_ = c.re() * re_ - c.im() * im_;
            im_ = ch_ * c.im() + im_ * c.re(); 
            return *this;
        }
        complex & operator /= (complex c)
        {
            double ch_ = re_;
            re_ = (re_ * c.re() + im_ * c.im()) / (c.re() * c.re() + c.im() * c.im());
            im_ = (im_ * c.re() - ch_ * c.im()) / (c.re() * c.re() + c.im() * c.im());
            return *this;
        }

        friend complex operator + (complex x, complex y);
        friend complex operator - (complex x, complex y);
        friend complex operator * (complex x, complex y);
        friend complex operator / (complex x, complex y);
        
        complex operator ~ () const
        {
            return complex(re_, -im_);
        }
        complex operator - () const
        {
            return complex(-re_, -im_);
        }
    };
    complex operator + (complex x, complex y)
    {
        x += y;
        return x;
    }
    complex operator - (complex x, complex y)
    {
        x -= y;
        return x;
    }
    complex operator * (complex x, complex y)
    {
        x *= y;
        return x;
    }   
    complex operator / (complex x, complex y)
    {   
        x /= y;
        return x;
    }
}