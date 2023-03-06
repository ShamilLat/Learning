#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::string file_format = ".lsf", file_name = "";
  int nums[3] = {10240, 30720, 51200};
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int omp_num = 1; omp_num <= 64; omp_num *= 2) {
      std::stringstream ss;
      ss << size << "_" << size / omp_num;
      file_name = ss.str() + file_format;
      ss.clear();
      std::string cmd =
          "scp \"" + file_name + "\" edu-cmc-sqi21-07@polus.cmc.msu.ru:lsf/";
      std::system(cmd.c_str());
    }
  }
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int omp_num = 1; omp_num <= 64; omp_num *= 2) {
      std::stringstream ss;
      ss << size << "_" << size / omp_num << "_barrier";
      file_name = ss.str() + file_format;
      ss.clear();
      std::string cmd =
          "scp \"" + file_name + "\" edu-cmc-sqi21-07@polus.cmc.msu.ru:lsf/";
      std::system(cmd.c_str());
    }
  }
}