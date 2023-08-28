#include "ip.hpp"
#include <sstream>
#include <string>

std::string Ip::to_string() const {
  std::stringstream ss;
  ss << byte1 << '.' << byte2 << '.' << byte3 << '.' << byte4 << ':' << port;
  // ss << byte1 << '.' << byte2 << '.' << byte3 << '.' << byte4;
  return ss.str();
}

bool Ip::operator==(const Ip& other) const {
  return (other.byte1 == byte1 && other.byte2 == byte2 &&
          other.byte3 == byte3 && other.byte4 == byte4);
}

std::ostream& operator<<(std::ostream& os, const Ip& ip) {
  os << ip.byte1 << '.' << ip.byte2 << '.' << ip.byte3 << '.' << ip.byte4;
  return os;
}
void operator>>(std::istream& is, Ip& ip) {
  std::stringstream ss;
  std::string str;
  char t;
  is >> str;
  ss.str(str);
  ss >> ip.byte1 >> t >> ip.byte2 >> t >> ip.byte3 >> t >> ip.byte4 >> t >>
      ip.port;
}

std::size_t std::hash<Ip>::operator()(const Ip& ip) const {
  using std::hash;
  using std::size_t;

  return hash<int>{}(ip.byte1) * hash<int>{}(ip.byte2) +
         hash<int>{}(ip.byte3) * hash<int>{}(ip.byte4);
}
