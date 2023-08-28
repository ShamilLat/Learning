#include "complex.hpp"
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace numbers {

explicit complex::complex(std::string s) {
  std::stringstream a(s);
  char c;
  double num = 0;
  a >> c;
  a >> num;
  re_ = num;
  a >> c;
  a >> num;
  im_ = num;
}

double complex::re() const {
  return re_;
}

double complex::im() const {
  return im_;
}

double complex::abs() const {
  return sqrt(re_ * re_ + im_ * im_);
}

double complex::abs2() const {
  return re_ * re_ + im_ * im_;
}

std::string complex::to_string() const {
  std::stringstream res;
  res << "(" << std::setprecision(10) << re_ << "," << std::setprecision(10)
      << im_ << ")";
  return res.str();
}

complex& complex::operator+=(complex c) {
  re_ += c.re();
  im_ += c.im();
  return *this;
}

complex& complex::operator-=(complex c) {
  re_ -= c.re();
  im_ -= c.im();
  return *this;
}

complex& complex::operator*=(complex c) {
  double ch_ = re_;
  re_ = c.re() * re_ - c.im() * im_;
  im_ = ch_ * c.im() + im_ * c.re();
  return *this;
}

complex& complex::operator/=(complex c) {
  double ch_ = re_;
  re_ = (re_ * c.re() + im_ * c.im()) / (c.re() * c.re() + c.im() * c.im());
  im_ = (im_ * c.re() - ch_ * c.im()) / (c.re() * c.re() + c.im() * c.im());
  return *this;
}

complex complex::operator~() const {
  return complex(re_, -im_);
}
complex complex::operator-() const {
  return complex(-re_, -im_);
}

complex operator+(complex x, complex y) {
  x += y;
  return x;
}

complex operator-(complex x, complex y) {
  x -= y;
  return x;
}

complex operator*(complex x, complex y) {
  x *= y;
  return x;
}

complex operator/(complex x, complex y) {
  x /= y;
  return x;
}

}  // namespace numbers
