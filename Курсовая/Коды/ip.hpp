#pragma once

#include <sstream>
#include <string>

struct Ip {
  int byte1 = 0;
  int byte2 = 0;
  int byte3 = 0;
  int byte4 = 0;
  int port = 0;

  Ip() {}
  Ip(int b1_, int b2_, int b3_, int b4_, int p_)
      : byte1(b1_), byte2(b2_), byte3(b3_), byte4(b4_), port(p_) {}

  std::string to_string() const;
  std::string to_string_with() const;

  bool operator==(const Ip& other) const;

  friend std::ostream& operator<<(std::ostream& os, const Ip& ip);
  friend void operator>>(std::istream& is, Ip& ip);
};

template <>
struct std::hash<Ip> {
  std::size_t operator()(const Ip& ip) const;
};
