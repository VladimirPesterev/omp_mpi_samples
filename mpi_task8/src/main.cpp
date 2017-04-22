#include <iostream>
#include <mpi.h>

using namespace std;

void generateSymbols(char *buff, int length) {
  for (auto i = 0; i < length; i++) {
    buff[i] = (char) 'a' + rand() % 25;
    cout << i << buff[i];
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  srand(time(NULL) * (rank + 1));

  bool isEven = processCount % 2 == 0;
  for (auto i = 0; i < processCount; i++) {
    if(i == rank) {
      char symbol;
      if(rank == 0) {
        char *sendbuff = new char[processCount];
        generateSymbols(sendbuff, processCount);
        for (auto i = 1; i < processCount; i++) {
          MPI_Send(&sendbuff[i], 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        symbol = sendbuff[0];
        delete[] sendbuff;
      }
      else {
        MPI_Recv(&symbol, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      if(isEven || rank != processCount / 2) {
        MPI_Sendrecv(&symbol, 1, MPI_CHAR, processCount - rank - 1, 1, &symbol, 1, MPI_CHAR, processCount - rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      cout << rank << symbol;
    }
  }

  MPI_Finalize();
  return 0;
}
