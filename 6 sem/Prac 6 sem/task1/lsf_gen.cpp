#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string base =
      "#BSUB -n 1\n#BSUB -W 00:15\n#BSUB -o \"job.%J.out\"\n#BSUB -e "
      "\"job.%J.err\"\n";
  std::string core_flag = "#BSUB -R \"affinity[core(";
  std::string num_threads = "OMP_NUM_THREADS=";
  std::string server_file = "./a.out";

  int iter = 50;

  std::string file_format = ".lsf", file_name = "";
  int st = 1;
  for (int j = 0; j < 3; j++) {
    st = 1;
    int size = 0;
    switch (j) {
      case 0:
        size = 50;
        break;
      case 1:
        size = 100;
        break;
      case 2:
        size = 200;
        break;
    }
    for (int i = 0; i < 6; i++) {
      std::stringstream ss;
      ss << size << "_" << i;
      file_name = ss.str() + file_format;
      ss.clear();
      std::ofstream ccout(file_name);
      ccout << base;
      if (i > 1) {
        ccout << core_flag << st / 2 << ")]\"\n";
      }
      ccout << num_threads << st << " " << server_file << " " << size << " " << iter << "\n";
      st *= 2;
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