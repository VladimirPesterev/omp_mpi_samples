#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  MPI_Init(&argc, &argv);

  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int *sendbuff = new int[1];
  sendbuff[0] = rank;
  if(rank == processCount - 1) {
    MPI_Send(sendbuff, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  else {
    MPI_Send(sendbuff, 1, MPI_INT, rank + 1, rank + 1, MPI_COMM_WORLD);
  }
  delete[] sendbuff;

  int *recvbuff = new int[1];
  if(rank == 0) {
    MPI_Recv(recvbuff, 1, MPI_INT, processCount - 1, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  else {
    MPI_Recv(recvbuff, 1, MPI_INT, rank - 1, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  cout << rank << recvbuff[0] << endl;
  delete[] recvbuff;

  MPI_Finalize();
  return 0;
}
