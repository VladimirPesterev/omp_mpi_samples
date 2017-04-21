#include <iostream>
#include <mpi.h>

using namespace std;

void generate(float *buff, int length) {
  for (auto i = 0; i < length; i++) {
    buff[i] = rand() % (i + 10) / 2.f;
    cout << buff[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  MPI_Init(&argc, &argv);

  int processCount, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int length = 5;

  float *buff = new float[length];
  generate(buff, length);

  float *recvbuff;
  if(rank == 0) {
    cout << "Количество процессов: " << processCount << endl;
    recvbuff = new float[length];
  }

  MPI_Reduce(buff, recvbuff, length, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(rank == 0) {
    cout << "Результат:" << endl;
    for (auto i = 0; i < length; i++) {
      cout << recvbuff[i] << " ";
    }
    cout << endl;
    delete[] recvbuff;
  }

  delete[] buff;

  MPI_Finalize();
  return 0;
}
