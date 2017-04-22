#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  srand(time(NULL) * (rank + 1));

  if(rank == 0) {
    int *integers = new int[5];
    for (size_t i = 0; i < 5; i++) {
      integers[i] = rand() % 100;
    }
    int *randomBuff = new int[5];
    MPI_Sendrecv(integers, 5, MPI_INT, 1, 0, randomBuff, 5, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    delete[] integers;

    cout << "Полученный массив от первого процесса:" << endl;
    for (size_t i = 0; i < 5; i++) {
      cout << randomBuff[i] << "_";
    }
    cout << endl;
    delete[] randomBuff;
  }
  else if(rank == 1) {
    int *integers = new int[5];
    for (size_t i = 0; i < 5; i++) {
      integers[i] = rand() % 10;
    }
    int *randomBuff = new int[5];
    MPI_Sendrecv(integers, 5, MPI_INT, 0, 1, randomBuff, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    delete[] integers;

    cout << "Полученный массив от второго процесса:" << endl;
    for (size_t i = 0; i < 5; i++) {
      cout << randomBuff[i] << "_";
    }
    cout << endl;
    delete[] randomBuff;
  }

  MPI_Finalize();
  return 0;
}
