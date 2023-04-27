#pragma once

#include <string>
#include <vector>
#include "log_string.hpp"

int days_sum(int number);

void read_file(std::vector<LogString>& log_strings, int argc, char* argv[]);

void output_massive_in_file(int* mas, int mas_size, std::string file_name);
void output_vector_in_file(std::vector<LogString> vector,
                           std::string file_name);

void output_log_strings(std::vector<LogString>& a);