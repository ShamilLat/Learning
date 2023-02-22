#include "id.hpp"
#include <iostream>
#include <sstream>
#include <string>

std::string Id::to_string() const {
  std::stringstream ss;
  ss << '[' << a << ':' << b << ':' << c << ']';
  return ss.str();
}

bool Id::operator==(const Id& other) {
  return (other.a == a && other.b == b && other.c == c);
}

std::ostream& operator<<(std::ostream& os, const Id& id) {
  os << '[' << id.a << ':' << id.b << ':' << id.c << ']';
  return os;
}