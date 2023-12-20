#include <mpi.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  string l1 = "send", l2 = "";

  string sub = l1.substr(l1.length() - 2, 2);

  if (rank == 0) {
    MPI_Send(&sub, sub.size() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
  } else {
    MPI_Recv(&l2, 2048, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  cout << "rank = " << rank << ", l = \'" << l2 << "\'" << endl;

  MPI_Finalize();
}