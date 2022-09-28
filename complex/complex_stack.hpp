#pragma once

#include "complex.hpp"

namespace numbers {

class complex_stack {
 public:
  complex_stack();
  complex_stack(const complex num);
  complex_stack(const complex_stack& other_stack);

  size_t size() const;  // return size of stack (amount of complex numbers)

  // delete last number
  friend complex_stack operator~(complex_stack other);

  // add number in stack
  friend complex_stack operator<<(complex_stack other_stack, const complex num);

  // return last number
  friend complex operator+(const complex_stack& other_stack);

  complex_stack& operator=(const complex_stack& other_stack);
  const complex operator[](int i) const;

  ~complex_stack();

 private:
  complex* stack_;
  int size_ = 0;
  int poz_ = 0;
};

}  // namespace numbers
