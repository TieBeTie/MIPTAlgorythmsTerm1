/*
   * Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
  Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
  Напишите нерекурсивный алгоритм.
  Требования к дополнительной памяти: O(n).
  Требуемое среднее время работы: O(n).
  Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
  Описание для случая прохода от начала массива к концу:
  Выбирается опорный элемент.
  Опорный элемент меняется с последним элементом массива.
  Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
  Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
  Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
  Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
  В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 */

#include <iostream>
#include <random>

using std::cin;
using std::cout;

void InOutOptimizaton();

void InitNum(int *num);

void ReadVector(int *vector, int size_vector);

void PrintAnswer(int answer);

int RandomFromInterval(int l, int r);

int SearchOrderStatistic(int *a, int n, int k);

template<class T>
void Swap(T &a, T &b);

template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l < r;
  }
};

template<class T, class TLess = IsLess<T>>
int RandomPartition(T *a, int l, int r, const TLess &isLess = TLess()) {
  int pivot = RandomFromInterval(l, r - 1);
  Swap(a[pivot], a[r - 1]);
  pivot = r - 1;
  int i = l;
  int j = l;
  while (j != pivot) {
    if (isLess(a[pivot], a[j])) {
      j++;
    } else {
      Swap(a[i], a[j]);
      i++;
      j++;
    }
  }
  Swap(a[i], a[pivot]);
  pivot = i;
  return pivot;
}

int main() {
  InOutOptimizaton();
  int n;
  InitNum(&n);
  int k;
  InitNum(&k);
  int *a = new int[n];
  ReadVector(a, n);
  k = SearchOrderStatistic(a, n, k);
  PrintAnswer(a[k]);
  delete[] a;
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void PrintAnswer(int answer) {
  cout << answer;
}

int RandomFromInterval(int l, int r) {
  return std::rand() % (r - l + 1) + l;
}

template<class T>
void Swap(T &a, T &b) {
  T x = a;
  a = b;
  b = x;
}

int SearchOrderStatistic(int *a, int n, int k) {
  int l = 0;
  int r = n;
  int pivot = RandomPartition(a, l, r);
  while (k != pivot) {
    if (k < pivot) {
      r = pivot;
      pivot = RandomPartition(a, l, r);
    } else {
      l = pivot + 1;
      pivot = RandomPartition(a, l, r);
    }
  }
  return pivot;
}

void ReadVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cin >> vector[i];
  }
}

void InitNum(int *num) {
  cin >> *num;
}