#pragma once

#include <string>

struct Id {
  int a = 0;
  int b = 0;
  int c = 0;

  Id() {}
  Id(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {}

  std::string to_string() const;

  bool operator==(const Id& other);

  friend std::ostream& operator<<(std::ostream& os, const Id& id);
};
