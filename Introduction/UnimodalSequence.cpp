/***************************************
3_2. Унимодальная последовательность
Дан массив целых чисел А[0..n-1]. 
Известно, что на интервале [0, m] 
значения массива строго возрастают, 
а на интервале [m, n-1] строго убывают. 
Найти m за O( log m ).
2 ≤ n ≤ 10000.
****************************************/

#include <iostream>

using std::cin;
using std::cout;

void InOutOptimizaton();

void InitNum(int *num);

void ReadVector(int *vector, int size_vector);

int SearchUnimodal(int *A, int n);

int BinarySearch(int *A, int low, int high);

void PrintNum(int num);

int main() {
  InOutOptimizaton();
  int n;
  InitNum(&n);
  int *A = new int[n];
  ReadVector(A, n);
  int tail = SearchUnimodal(A, n);
  int unimodal_max;
  unimodal_max = BinarySearch(A, (tail / 2) - 1, tail - 1);
  delete[] A;
  PrintNum(unimodal_max);
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;
}

void ReadVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cin >> vector[i];
  }
}

int SearchUnimodal(int *A, int n) {
  int i = 1;
  while (A[i - 1] < A[i] && i != n) {
    i *= 2;
    if (i > n) {
      i = n;
    }
  }
  return (i);
}

int BinarySearch(int *A, int low, int high) {
  int mid;
  while (low < high - 1) {
    mid = (low + high) / 2;
    if (A[mid] < A[mid + 1]) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return (high);
}

void PrintNum(int num) {
  cout << num;
}