#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
#BSUB -n 4
#BSUB -J "name.job"
#BSUB -W 00:15
#BSUB -o "bad.out"
#BSUB -e "bad.err"
#BSUB -R "span[ptile=2]" //скорее всего эта строчка тебе не нужна
mpiexec ./bad 50000

*/

using namespace std;

int main() {
  std::system("rm *.lsf");

  std::string begin = "source /polusfs/setenv/setup.SMPI\n#BSUB -n ";
  std::string base =
      "#BSUB -W 00:15\n#BSUB -o \"main.%J.out\"\n#BSUB "
      "-e \"main.%J.err\"\n#BSUB -m \"polus-c3-ib polus-c4-ib\"\n";
  std::string server_file = "mpiexec ./main";
  std::string file_format = ".lsf", file_name = "";

  vector<int> nums = {1000000, 5000000, 10000000, 50000000, 100000000};

  vector<int> omp_nums = {1, 2, 4, 8, 16, 32, 48, 60};
  for (auto& size : nums) {
    for (auto& n : omp_nums) {
      std::stringstream ss;
      ss << "mpisubmit.pl -p " << n << " ./main -- " << size;
      string cmd = ss.str();
      std::system(cmd.data());

      // ss << size << "_" << n;
      // file_name = ss.str() + file_format;
      // ss.clear();
      // std::ofstream ccout(file_name);
      // ccout << begin << n << "\n";
      // ccout << base;

      // if (omp_nums[i] > 1) {
      //   ccout << core_flag << omp_nums[i] * omp_nums[i] / 2 + omp_nums[i] % 2
      //         << ")]\"\n";
      // }
      // ccout << server_file << " " << size << "\n";

      printf("%d %d\n", size, n);
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