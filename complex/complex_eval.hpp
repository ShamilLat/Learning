#pragma once

#include <string>
#include <vector>
#include "complex.hpp"

namespace numbers {

complex eval(const std::vector<std::string>& args, const complex& z);

}  // namespace numbers
