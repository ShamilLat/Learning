#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::string file_format = ".lsf", file_name = "";
  int nums[3] = {1000000, 5000000, 10000000};
  int omp_nums[4] = {2, 4, 8, 16};
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int i = 0; i < 4; i++) {
      std::stringstream ss;
      ss << size << "_" << omp_nums[i];
      file_name = ss.str() + file_format;
      ss.clear();
      std::string cmd = "scp \"" + file_name +
                        "\" edu-cmc-sqi21-07@polus.cmc.msu.ru:Prac8_task2/";
      std::system(cmd.c_str());
    }
  }
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int i = 0; i < 4; i++) {
      std::stringstream ss;
      ss << size << "_" << omp_nums[i] << "_opt";
      file_name = ss.str() + file_format;
      ss.clear();
      std::string cmd = "scp \"" + file_name +
                        "\" edu-cmc-sqi21-07@polus.cmc.msu.ru:Prac8_task2/";
      std::system(cmd.c_str());
    }
  }
}