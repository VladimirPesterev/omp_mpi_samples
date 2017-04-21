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
    int initialValue = 0;

    int *sendbuff = new int[1];
    sendbuff[0] = initialValue;
    MPI_Send(sendbuff, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

    int *recvbuff = new int[1];
    MPI_Recv(recvbuff, 1, MPI_INT, processCount - 1, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    cout << rank + 1 << ". передал " << initialValue << " получил " << recvbuff[0] << endl;

    delete[] sendbuff;
    delete[] recvbuff;
  }
  else {
    int *recvbuff = new int[1];
    MPI_Recv(recvbuff, 1, MPI_INT, rank - 1, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int *sendbuff = new int[1];
    sendbuff[0] = recvbuff[0] + 1;
    if(rank != processCount - 1) {
      MPI_Send(sendbuff, 1, MPI_INT, rank + 1, rank + 1, MPI_COMM_WORLD);
    }
    else {
      MPI_Send(sendbuff, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    cout << rank + 1 << ". передал " << sendbuff[0] << " получил " << recvbuff[0] << endl;
    delete[] recvbuff;
    delete[] sendbuff;
  }

  MPI_Finalize();
  return 0;
}
