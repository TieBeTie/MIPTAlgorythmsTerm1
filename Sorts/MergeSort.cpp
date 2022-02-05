/*
 * Дана последовательность целых чисел a1...an и натуральное число k,
 * такое что для любых i, j: если j >= i + k,
 * то a[i] <= a[j]. Требуется отсортировать последовательность.
 * Последовательность может быть очень длинной. Время работы O(n * log(k)).
 * Доп. память O(k). Использовать слияние.
 */

#include <iostream>

using std::cin;
using std::cout;

void InOutOptimizaton();

template<class T>
void InitNum(T *num);

int min(int a, int b);

void ReadVector(int *vector, int size_vector);

void PrintVector(int *vector, int size_vector);

void SortOrderedByk(long long n, int k);

void MergeSortIterative(int *a, int l, int r);

template<class T>
void Swap(T &a, T &b);

int main() {
  //InOutOptimizaton();
  long long n;
  InitNum(&n);
  int k;
  InitNum(&k);
  SortOrderedByk(n, k);
}

template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l < r;
  }
};

template<class T, class TLess = IsLess<T>>
void Merge(T *a, int l, int m, int r, const TLess &isLess = TLess()) {
  int i = 0;
  int j = 0;
  T *buffer = new T[r - l];

  while ((l + i) < m && (m + j) < r) {
    if (isLess(a[l + i], a[m + j])) {
      buffer[i + j] = a[l + i];
      i++;
    } else {
      buffer[i + j] = a[m + j];
      j++;
    }
  }
  while (l + i < m) {
    buffer[i + j] = a[l + i];
    i++;
  }
  while (m + j < r) {
    buffer[i + j] = a[m + j];
    j++;
  }
  for (i = 0; i < r - l; i++) //т.к. происходит экономия динамической памяти, буффер начинает заполнятся с 0 элемента
  {
    a[l + i] = buffer[i];
  }
  delete[] buffer;
}


void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

template<class T>
void InitNum(T *num) {
  cin >> *num;
}

void ReadVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cin >> vector[i];
  }
}

void PrintVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cout << vector[i] << " ";
  }
}

template<class T>
void Swap(T &a, T &b) {
  T x = a;
  a = b;
  b = x;
}

void Sew(int *rainicorn, int *head, int *tale, int k, int n) {
  for (int i = 0; i < k; i++) {
    rainicorn[i] = head[i];
  }
  for (int i = k; i < n; i++) {
    rainicorn[i] = tale[i - k];
  }
}

void HeadIsTale(int *rainicorn, int *head, int k, int n) {
  for (int i = 0; i < n; i++) {
    head[i] = rainicorn[i + k];
  }
}

int EndOfTale(int i, int k, int n) //функция, вычисляющая mod k
{
  i = min(i, n);
  if (i % k == 0) {
    return (k);
  }
  return (i % k);
}

void SortOrderedByk(long long n, int k) {
  int *head = new int[k];
  int *tale = new int[k];
  int *rainicorn = new int[2 * k];

  ReadVector(head, k);
  MergeSortIterative(head, 0, k);
  for (long long i = 2 * k; i < n + k; i += k) {
    ReadVector(tale, EndOfTale(i, k, n));
    MergeSortIterative(tale, 0, EndOfTale(i, k, n));  //массив сортируется по k элементов
    Sew(rainicorn, head, tale, k, EndOfTale(i, k, n) + k);
    Merge(rainicorn, 0, k, EndOfTale(i, k, n) + k);
    HeadIsTale(rainicorn, head, k, EndOfTale(i, k, n));
    PrintVector(rainicorn, k);
  }
  if (n % k == 0) {
    PrintVector(head, k);
  } else {
    PrintVector(head, n % k);
  }

  delete[] head;
  delete[] tale;
  delete[] rainicorn; // ;c
}

void MergeSortIterative(int *a, int l, int r) {
  for (int i = 1; i < r; i *= 2) {
    for (int j = l; j < r - i; j += 2 * i) {
      Merge(a, j, j + i, min(j + 2 * i,
                             r)); // i - количество элементов в разбинении, j - указатель на первой элемент последовательности
    }
  }
}

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}