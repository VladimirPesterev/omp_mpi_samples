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
    cout << "Кол-во процессов: " << processCount << endl;

    int randomProcess = (rand() % (processCount - 1)) + 1;
    cout << "Сгенеренный номер процесса: " <<  randomProcess << endl;
    int *randomBuff = new int[1];
    randomBuff[0] = randomProcess;
    for (size_t i = 1; i < processCount; i++) {
      MPI_Send(randomBuff, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    delete[] randomBuff;

    MPI_Status status;
    int count;
    MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    int *recvbuff = new int[count];
    MPI_Recv(recvbuff, count, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD, &status);
    delete[] recvbuff;
    cout << "Получено от: " << status.MPI_SOURCE << endl;
    cout << "Полученный массив:" << endl;
    for (size_t j = 0; j < count; j++) {
      cout << recvbuff[j] << " ";
    }
    cout << endl;
  }
  else {
    int randomProcess;
    int *randomBuff = new int[1];
    MPI_Recv(randomBuff, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    randomProcess = randomBuff[0];
    delete[] randomBuff;
    if(randomProcess == rank) {
      int count = (rand() % 10) + 2;
      int *integers = new int[count];
      for (size_t i = 0; i < count; i++) {
        integers[i] = rand() % 100;
      }
      MPI_Send(integers, count, MPI_INT, 0, 1, MPI_COMM_WORLD);
      delete[] integers;
    }
  }

  MPI_Finalize();
  return 0;
}
