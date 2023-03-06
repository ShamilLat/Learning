#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::string file_format = ".lsf", file_name = "";
  int nums[3] = {5760, 17280, 34560};
  int omp_nums[5] = {1, 2, 4, 6, 8};
  for (int j = 0; j < 3; j++) {
    int size = nums[j];

    for (int i = 0; i < 5; i++) {
      std::stringstream ss;
      ss << size << "_" << size / omp_nums[i];
      file_name = ss.str() + file_format;
      ss.clear();
      std::string cmd =
          "scp \"" + file_name + "\" edu-cmc-sqi21-07@polus.cmc.msu.ru:lsf/";
      std::system(cmd.c_str());
    }
  }
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int i = 0; i < 5; i++) {
      std::stringstream ss;
      ss << size << "_" << size / omp_nums[i] << "_barrier";
      file_name = ss.str() + file_format;
      ss.clear();
      std::string cmd =
          "scp \"" + file_name + "\" edu-cmc-sqi21-07@polus.cmc.msu.ru:lsf/";
      std::system(cmd.c_str());
    }
  }
}