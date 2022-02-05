/*
 * Имеется рекуррентная последовательность A1, A2, ..., AN,
 * строящаяся по следующему правилу: A1 = K Ai+1 = (Ai * M) & 0xFFFFFFFFU mod L
 * Требуется найти сумму всех нечётных по порядку элементов
 * в отсортированной по неубыванию последовательности по модулю L.
 * Для входных данных 5 7 13 100 последовательность будет такой:
 * (7, 7*13mod100=91, 91*13mod100=83, 83*13mod100=79, 79*13mod100=27),
 * то есть, (10, 91, 83, 79, 27)
 * Отсортированная последовательность (7, 27, 79, 83, 91)
 * Сумма элементов на нечётных местах = (10 + 79 + 91) mod 100 = 77
 * Для представления элементов последовательности необходимо
 * использовать тип данных unsigned int.
 * Для получения массива используйте цикл
 *
 * Формат ввода
    N K M L
 */

typedef unsigned long long UnsLL;
typedef unsigned int UnsInt;

#include <iostream>

using std::cin;
using std::cout;

template<class T>
void Swap(T &a, T &b) {
  T x = a;
  a = b;
  b = x;
}

int Digit(UnsInt num, int num_digit) {
  num >>= 8 * (num_digit - 1);
  return num & 0b11111111;
}

template<class T>
void LSDByte(T *a, UnsLL size, int max_bit) {
  const short byte = 0b100000000;
  int i, j, count;
  UnsInt *B = new UnsInt[size];
  UnsInt *C = new UnsInt[byte];
  UnsInt tmp;
  int d;

  for (i = 1; i <= max_bit; i++) {
    for (j = 0; j < byte; j++) {
      C[j] = 0;                            //обнуление цифрового массива, в котором записано их количество
    }
    for (j = 0; j < size; j++) {
      d = Digit(a[j], i);
      C[d]++;                // цифры принимаются за индексы и подсчитываются в определённом столбце
    }
    count = 0;
    for (j = 0; j < byte; j++) {
      tmp = C[j];
      C[j] = count;
      count += tmp;
    }
    for (j = 0; j < size; j++) {
      d = Digit(a[j], i);
      B[C[d]] = a[j];
      C[d]++;
    }
    for (j = 0; j < size; j++) {
      a[j] = B[j];
    }
  }
  delete[] C;
  delete[] B;
}

int CreateMagicArray(UnsInt *a, UnsLL N, UnsInt K, UnsLL M, UnsLL L) {
  UnsInt max = K;
  int max_bin = 0;
  a[0] = K;
  for (UnsLL i = 0; i < N - 1; i++) {
    a[i + 1] = ((a[i] * M) & 0xFFFFFFFFU) % L;
    if (a[i] > max)
      max = a[i];
  }
  while (max != 0) {
    max >>= 8;
    max_bin++;
  }
  return max_bin;
}

void InitMagicParam(UnsLL *N, UnsInt *K, UnsLL *M, UnsLL *L) {
  cin >> *N >> *K >> *M >> *L;
}

void PrintVector(UnsInt *vector, UnsLL size_vector) {
  for (UnsLL i = 0; i < size_vector; i++) {
    cout << vector[i] << " ";
  }
}

UnsLL GetMagicNumber(UnsInt *a, UnsLL N, UnsLL L) {
  UnsLL sum = 0;
  for (UnsLL i = 0; i < N; i += 2) {
    sum += a[i];
    sum %= L;
  }
  return sum;
}

void PrintAnswer(UnsLL answer) {
  cout << answer;
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

int main() {
  InOutOptimizaton();
  UnsLL N, M, L;
  UnsInt K;
  InitMagicParam(&N, &K, &M, &L);
  UnsInt *a = new UnsInt[N];
  int max_bit = CreateMagicArray(a, N, K, M, L);

  LSDByte(a, N, max_bit);
  UnsLL answer = GetMagicNumber(a, N, L);

  PrintAnswer(answer);
  delete[] a;
}