#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  MPI_Init(&argc, &argv);

  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0) {
    int count = (rand() % 10) + 2;
    int *integers = new int[count];
    for (auto i = 0; i < count; i++) {
      integers[i] = rand() % 100;
    }
    MPI_Send(integers, count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    delete[] integers;

    MPI_Status status;
    MPI_Probe(1, 1, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    int *randomBuff = new int[count];
    MPI_Recv(randomBuff, count, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout << "Полученный массив от первого процесса:" << endl;
    for (auto i = 0; i < count; i++) {
      cout << randomBuff[i] << "_";
    }
    cout << endl;
    delete[] randomBuff;
  }
  else if(rank == 1) {
    int count;
    MPI_Status status;
    MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    int *randomBuff = new int[count];
    MPI_Recv(randomBuff, count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout << "Полученный массив от первого процесса:" << endl;
    for (auto i = 0; i < count; i++) {
      cout << randomBuff[i] << "_";
    }
    cout << endl;
    delete[] randomBuff;

    count = (rand() % 10) + 2;
    int *integers = new int[count];
    for (auto i = 0; i < count; i++) {
      integers[i] = rand() % 85;
    }
    MPI_Send(integers, count, MPI_INT, 0, 1, MPI_COMM_WORLD);
    delete[] integers;
  }

  MPI_Finalize();
  return 0;
}
