#pragma once

#include "complex.hpp"

namespace numbers {

class complex_stack {
 public:
  complex_stack();
  complex_stack(const complex num);
  complex_stack(const complex_stack& other_stack);

  size_t size() const;

  friend complex_stack operator~(complex_stack other);
  friend complex_stack operator<<(complex_stack other_stack, const complex num);
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
