#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string base =
      "#BSUB -m polus-c3-ib\n#BSUB -W 00:15\n#BSUB -o \"main.%J.out\"\n#BSUB "
      "-e \"main.%J.err\"\n";
  std::string base_barrier =
      "#BSUB -m polus-c3-ib\n#BSUB -W 00:15\n#BSUB -o "
      "\"main_barrier.%J.out\"\n#BSUB -e \"main_barrier.%J.err\"\n";
  std::string core_flag = "#BSUB -R \"affinity[core(";
  std::string num_threads = "OMP_NUM_THREADS=";
  std::string server_file = "./main";
  std::string server_file_barrier = "./main_barrier";
  std::string file_format = ".lsf", file_name = "";

  int nums[3] = {10240, 30720, 51200};
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    int st = 1;
    for (int omp_num = 1; omp_num <= 64; omp_num *= 2) {
      std::stringstream ss;
      ss << size << "_" << size / omp_num;
      file_name = ss.str() + file_format;
      ss.clear();
      std::ofstream ccout(file_name);
      ccout << base;
      if (st > 1) {
        ccout << core_flag << st / 2 << ")]\"\n";
      }
      ccout << num_threads << st << " " << server_file << " " << size << " "
            << size / omp_num << "\n";
      st *= 2;
      printf("%d %d\n", size, size / omp_num);
    }
  }
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    int st = 1;
    for (int omp_num = 1; omp_num <= 64; omp_num *= 2) {
      std::stringstream ss;
      ss << size << "_" << size / omp_num << "_barrier";
      file_name = ss.str() + file_format;
      ss.clear();
      std::ofstream ccout(file_name);
      ccout << base_barrier;
      if (st > 1) {
        ccout << core_flag << st / 2 << ")]\"\n";
      }
      ccout << num_threads << st << " " << server_file_barrier << " " << size
            << " " << size / omp_num << "\n";
      st *= 2;
      printf("%d %d\n", size, size / omp_num);
    }
  }
}

/*
#BSUB -n 1
#BSUB -W 00:15
#BSUB -o "my_job.%J.out"
#BSUB -e "my_job.%J.err"

OMP_NUM_THREADS=1 ./a.out
OMP_NUM_THREADS=2 ./a.out

#BSUB -R "affinity[core(2)]"
OMP_NUM_THREADS=4 ./a.out

#BSUB -R "affinity[core(4)]"
OMP_NUM_THREADS=8 ./a.out

#BSUB -R "affinity[core(8)]"
OMP_NUM_THREADS=16 ./a.out

#BSUB -R "affinity[core(16)]"
OMP_NUM_THREADS=32 ./a.out

*/