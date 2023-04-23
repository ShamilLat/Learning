#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/*
#BSUB -n 4
#BSUB -J "name.job"
#BSUB -W 00:15
#BSUB -o "bad.out"
#BSUB -e "bad.err"
#BSUB -R "span[ptile=2]" //скорее всего эта строчка тебе не нужна
mpiexec ./bad 50000

*/

int main() {
  std::system("rm *.lsf");

  std::string begin = "#BSUB -n ";
  std::string base =
      "#BSUB -W 00:15\n#BSUB -o \"mpi.%J.out\"\n#BSUB "
      "-e \"mpi.%J.err\"\n";
  std::string base_barrier =
      "#BSUB -W 00:15\n#BSUB -o \"mpi_opt.%J.out\"\n#BSUB "
      "-e \"mpi_opt.%J.err\"\n";
  std::string server_file = "mpiexec ./mpi";
  std::string server_file_barrier = "mpiexec ./mpi_opt";
  std::string file_format = ".lsf", file_name = "";

  int nums[3] = {1000000, 5000000, 10000000};
  int omp_nums[5] = {2, 4, 8, 16};
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int i = 0; i < 4; i++) {
      std::stringstream ss;
      ss << size << "_" << omp_nums[i];
      file_name = ss.str() + file_format;
      ss.clear();
      std::ofstream ccout(file_name);
      ccout << begin << omp_nums[i] << "\n";
      ccout << base;

      // if (omp_nums[i] > 1) {
      //   ccout << core_flag << omp_nums[i] * omp_nums[i] / 2 + omp_nums[i] % 2
      //         << ")]\"\n";
      // }
      ccout << server_file << " " << size << "\n";

      printf("%d %d\n", size, omp_nums[i]);
    }
  }
  for (int j = 0; j < 3; j++) {
    int size = nums[j];
    for (int i = 0; i < 4; i++) {
      std::stringstream ss;
      ss << size << "_" << omp_nums[i] << "_opt";
      file_name = ss.str() + file_format;
      ss.clear();
      std::ofstream ccout(file_name);

      ccout << begin << omp_nums[i] << "\n";
      ccout << base_barrier;
      // if (omp_nums[i] > 1) {
      //   ccout << core_flag << omp_nums[i] * omp_nums[i] / 2 + omp_nums[i] % 2
      //         << ")]\"\n";
      // }
      ccout << server_file_barrier << " " << size << "\n";

      printf("%d %d\n", size, omp_nums[i]);
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