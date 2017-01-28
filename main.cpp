#include <iostream>
#include <cmath>
#include <ctime>
#include <omp.h>

using namespace std;

const double Ta = 0.01;
const double E = 0.00001;

void init(long double** A, long double* B, long double* X, int N) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(i == j) {
        A[i][j] = 2.0;
      }
      else {
        A[i][j] = 1.0;
      }
    }
    B[i] = N + 1;
    X[i] = 0;
  }
}

void compute(long double** A, long double* B, long double* X, int N) {
  long double* Xn = new long double[N];
  // int th_id;
  // cout << "parallel computing on" << endl;
  // #pragma omp parallel private(th_id)
  // {
    // th_id = omp_get_thread_num();
    // #pragma omp critical
    // {
      // std::cout << "thread No:" << th_id << endl;
    // }
    for(int i = 0; i < N; i++) {
      long double summ = 0.0;
      for(int j = 0; j < N; j++) {
        summ += A[i][j] * X[j];
      }
      Xn[i] = X[i] - Ta * (summ - B[i]);
    }
  // }
  for(int i = 0; i < N; i++) {
    X[i] = Xn[i];
    // cout << "X[" << i << "]=" << X[i] << " ";
  }
  // cout << endl;
  delete[] Xn;
}

bool isCompleted(long double** A, long double* B, long double* X, int N) {
  long double ch = 0.0;
  long double zn = 0.0;
  long double* U = new long double[N];
  // #pragma omp parallel
  // {
    for(int i = 0; i < N; i++) {
      long double summ = 0.0;
      for(int j = 0; j < N; j++) {
        summ += (A[i][j] * X[j]);
      }
      summ -= B[i];
      ch += sqrt(summ * summ);
      zn += sqrt(B[i] * B[i]);
    }
  // }

  if(ch / zn < E) {
    return true;
  }
  return false;
}

int main() {

  int N;
  cout << "введите значение N" << endl;
  cin >> N;

  long double** A = new long double* [N];
  for (int i = 0; i < N; i++)
    A[i] = new long double [N];
  long double* B = new long double [N];
  long double *X = new long double [N];

  init(A, B, X, N);


  std::clock_t start;
  long double duration;
  start = clock();

  int count = 0;
  while (true) {
    compute(A, B, X, N);
    if(isCompleted(A, B, X, N)) {
      break;
    }
    count++;
  }

  duration = (clock() - start) / (long double) CLOCKS_PER_SEC;
  cout << "время вычислений: "<< duration << endl;
  cout << "количество итераций: " << count << endl;

  for (int i = 0; i < N; i++)
    delete []A[i];
  delete[] B;
  delete[] X;
  return 0;
}
