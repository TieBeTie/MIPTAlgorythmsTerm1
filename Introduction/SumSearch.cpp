/**************************************************
 2_3. Нужная сумма

		Даны два строго возрастающих массива
	целых чисел A[0..n) и B[0..m) и число k.
	Найти количество таких пар индексов (i, j),
	что A[i] + B[j] = k.
	Время работы O(n + m). n, m ≤ 100000.

	Указание. Обходите массив B от конца к началу.

 	Формат ввода
  В первой и второй строке вводятся количество элементов и сами элементы массива A.

  В третьей и четвертой строке вводятся количество элементов и сами элементы массива B.

  В пятой строке — число k.

  Формат вывода
  Выведите требуемое количество пар.

***************************************************/

#include <iostream>

using std::cin;
using std::cout;

void InOutOptimizaton();

void InitNum(int *num);

void ReadVector(int *vector, int size_vector);

int SearchKeys(int *A, int n, int *B, int m, int k);

void PrintNum(int num);


int main() {
  InOutOptimizaton();
  int n;
  InitNum(&n);
  int *A = new int[n];
  ReadVector(A, n);
  int m;
  InitNum(&m);
  int *B = new int[m];
  ReadVector(B, m);
  int k;
  InitNum(&k);
  int answer = SearchKeys(A, n, B, m, k);
  PrintNum(answer);
  delete[] A;
  delete[] B;
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

int SearchKeys(int *A, int n, int *B, int m, int k) {
  int i = 0;
  int j = m - 1;
  int answer = 0;
  while (i < n && j >= 0) {
    if (A[i] + B[j] < k) {
      i++;
    } else if (A[i] + B[j] == k) {
      i++;
      j--;
      answer++;
    } else if (A[i] + B[j] > k) {
      j--;
    }
  }
  return (answer);
}

void PrintNum(int num) {
  cout << num;
}