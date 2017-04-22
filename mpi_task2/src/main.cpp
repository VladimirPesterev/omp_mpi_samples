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
    cout << "Кол-во процессов: " << processCount << endl;

    char* characters = new char[6];
    for (auto i = 0; i < 6; i++) {
      characters[i] = (char) ('a' + rand() % 25);
    }
    double* doubles = new double[6];
    for (auto i = 0; i < 6; i++) {
      doubles[i] = (rand() % 100) / 2.2;
    }
    int* integers = new int[6];
    for (auto i = 0; i < 6; i++) {
      integers[i] = (int) rand() % 100;
    }

    int first = rand() % 3;
    if(first == 0) {
      MPI_Send(characters, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
      MPI_Send(doubles, 6, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
      MPI_Send(integers, 6, MPI_INT, 1, 2, MPI_COMM_WORLD);
    }
    else if(first == 1) {
      MPI_Send(doubles, 6, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
      MPI_Send(characters, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
      MPI_Send(integers, 6, MPI_INT, 1, 2, MPI_COMM_WORLD);
    }
    else {
      MPI_Send(integers, 6, MPI_INT, 1, 2, MPI_COMM_WORLD);
      MPI_Send(doubles, 6, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
      MPI_Send(characters, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }

    delete[] characters;
    delete[] doubles;
    delete[] integers;
  }
  else if(rank == 1) {
    for (auto i = 0; i < 3; i++) {
      MPI_Status status;
      int count;
      MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      if(status.MPI_TAG == 0) {
        MPI_Get_count(&status, MPI_CHAR, &count);
        char *recvbuff = new char[count];
        MPI_Recv(recvbuff, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (auto j = 0; j < count; j++) {
          cout << recvbuff[j] << " ";
        }
        delete[] recvbuff;
        cout << endl;
        cout << endl;
      }
      else if(status.MPI_TAG == 1) {
        MPI_Get_count(&status, MPI_DOUBLE, &count);
        double *recvbuff = new double[count];
        MPI_Recv(recvbuff, count, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (auto j = 0; j < count; j++) {
          cout << recvbuff[j] << " ";
        }
        delete[] recvbuff;
        cout << endl;
        cout << endl;
      }
      else {
        MPI_Get_count(&status, MPI_INT, &count);
        int *recvbuff = new int[count];
        MPI_Recv(recvbuff, count, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (auto j = 0; j < count; j++) {
          cout << recvbuff[j] << " ";
        }
        delete[] recvbuff;
        cout << endl;
        cout << endl;
      }
    }
  }

  MPI_Finalize();
  return 0;
}
