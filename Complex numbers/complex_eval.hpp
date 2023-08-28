#pragma once

#include <string>
#include <vector>
#include "complex.hpp"

namespace numbers {

// Solution of Reverse Polish notation
// z - Variable designation
// + - * / supports
// ! - add last element in stack
// ; - delete last element in stack
// ~ - Complex-conjugate Number
// # - change sign of number
complex eval(const std::vector<std::string>& args, const complex& z);

}  // namespace numbers
