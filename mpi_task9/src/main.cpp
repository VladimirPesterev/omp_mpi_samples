#include <iostream>
#include <mpi.h>

using namespace std;

void generateSymbols(char *buff, int length) {
  for (auto i = 0; i < length; i++) {
    buff[i] = (char) 'a' + rand() % 25;
    cout << buff[i];
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  MPI_Init(&argc, &argv);

  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  bool isEven = processCount % 2 == 0;
  char *sendbuff;
  if(rank == 0) {
    sendbuff = new char[processCount];
    generateSymbols(sendbuff, processCount);
  }

  char recv;
  MPI_Scatter(sendbuff, 1, MPI_CHAR, &recv, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
  if(rank == 0) {
    delete[] sendbuff;
  }

  char *recvbuff;
  if(rank == 1) {
    recvbuff = new char[processCount];
  }
  MPI_Gather(&recv, 1, MPI_CHAR, recvbuff, 1, MPI_CHAR, 1, MPI_COMM_WORLD);

  if(rank == 1) {
    for (auto i = 0; i < processCount; i++) {
      cout << recvbuff[i];
    }
    cout << endl;
    delete[] recvbuff;
  }

  MPI_Finalize();
  return 0;
}
