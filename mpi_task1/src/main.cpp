#include <iostream>
#include <mpi.h>

using namespace std;

void init(double* vec, int vecLength) {
  for (auto i = 0; i < vecLength; i++) {
    vec[i] = rand() % 10;
    cout << vec[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (processCount != 3) {
    cerr << "Все очень плохо!" << endl;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Abort(MPI_COMM_WORLD, 10);
  }
  else {
    if(rank == 0) cout << "Все збс!" << endl;
    MPI_Finalize();
  }
  return 0;
}
