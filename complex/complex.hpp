#pragma once

#include <string>

namespace numbers {

class complex {
 public:
  complex(double re = 0, double im = 0) : re_(re), im_(im) {}
  explicit complex(std::string s);

  double re() const;
  double im() const;
  double abs2() const;
  double abs() const;

  std::string to_string() const;

  complex& operator+=(complex c);
  complex& operator-=(complex c);
  complex& operator*=(complex c);
  complex& operator/=(complex c);

  friend complex operator+(complex x, complex y);
  friend complex operator-(complex x, complex y);
  friend complex operator*(complex x, complex y);
  friend complex operator/(complex x, complex y);

  complex operator~() const;
  complex operator-() const;

 private:
  double re_, im_;
};

}  // namespace numbers
