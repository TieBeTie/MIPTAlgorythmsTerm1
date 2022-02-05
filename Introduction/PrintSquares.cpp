/***************************************************
1_5.
	Вывести квадраты натуральных чисел от 1 до n,
 используя только O(n) операций сложения и вычитания
 (умножением пользоваться нельзя).
***************************************************/

#include <iostream>

using std::cin;
using std::cout;

void InOutOptimizaton();

void InitSizeVector(int *n);

void CreateVectorSquaredNums(int *squared_vector, int n);

void PrintVector(int *squared_vector, int n);

int main() {
  InOutOptimizaton();
  int n;
  InitSizeVector(&n);
  int *squared_vector = new int[n];
  CreateVectorSquaredNums(squared_vector, n);
  PrintVector(squared_vector, n);
  delete[] squared_vector;
}

//Оптимизация ввода-вывода
void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitSizeVector(int *n) {
  cin >> *n;
}

/*!******************************************
	Вывод чисел возведённых в квадрат
 Формула вычисления последующего числа,
 возведённого в квадрат, задаётся рекурретно,
 а именно X(n+1) = X(n) + n + n + 1.
*********************************************/
void CreateVectorSquaredNums(int *squared_vector, int n) {
  int X = 0;
  for (int i = 0; i < n; i += 1) {
    X += i + i + 1;
    squared_vector[i] = X;
  }
}

void PrintVector(int *squared_vector, int n) {
  for (int i = 0; i < n; i++) {
    cout << squared_vector[i] << " ";
  }
}