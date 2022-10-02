#pragma once

#include <string>

namespace numbers {

class complex {
 public:
  complex(double re = 0, double im = 0) : re_(re), im_(im) {}
  explicit complex(std::string s);

  double re() const;    // return re
  double im() const;    // return im
  double abs() const;   // normal abs of complex number
  double abs2() const;  // return not sqrt value

  std::string to_string() const;  // return string in (re, im) view

  complex& operator+=(complex c);
  complex& operator-=(complex c);
  complex& operator*=(complex c);
  complex& operator/=(complex c);

  friend complex operator+(complex x, complex y);
  friend complex operator-(complex x, complex y);
  friend complex operator*(complex x, complex y);
  friend complex operator/(complex x, complex y);

  complex operator~() const;  // (re, -im)
  complex operator-() const;  // (-re, -im)

 private:
  double re_, im_;
};

}  // namespace numbers
