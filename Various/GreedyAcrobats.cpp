/*******************************************************
 * В город N приехал цирк с командой атлетов.
 * Они хотят удивить горожан города N — выстроить
 * из своих тел башню максимальной высоты.
 * Башня — это цепочка атлетов, первый стоит на земле,
 * второй стоит у него на плечах,
 * третий стоит на плечах у второго и т.д.
 * Каждый атлет характеризуется силой si (kg)
 * и массой mi (kg). Сила — это максимальная масса,
 * которую атлет способен держать у себя на плечах.
 * К сожалению ни один из атлетов не умеет программировать,
 * так как всю жизнь они занимались физической подготовкой,
 * и у них не было времени на изучение языков программирования.
 * Помогите им, напишите программу, которая определит
 * максимальную высоту башни, которую они могут составить.
 * Известно, что если атлет тяжелее,
 * то он и сильнее: если mi>mj, то si > sj.
 * Атлеты равной массы могут иметь различную силу.

    Формат ввода
    Вход содержит только пары целых чисел — массу и силу атлетов.
    Число атлетов 1 ≤ n ≤ 100000.
    Масса и сила являются положительными целыми числами меньше, чем 2000000.

    Формат вывода
    Выход должен содержать натуральное число — максимальную высоту башни.
 */

#include <iostream>

using std::cin;
using std::cout;

struct Characteristic {
  int m;
  int p;

  Characteristic(int mass = -1, int power = -1) {
    m = mass;
    p = power;
  }
};

template<class T>
class Array {
public:
  Array() {
    this->buffer = new T[2];
    this->size = 0;
    this->buffersize = 2;
  }

  Array(const Array &) = delete;

  Array(Array &&) = delete;

  Array &operator=(const Array &) = delete;

  Array &operator=(Array &&) = delete;

  ~Array() {
    delete[] this->buffer;
  }

  void PushBack(T b) {
    if (this->size == this->buffersize) {
      T *tmp = new T[this->buffersize * 2];
      for (int i = 0; i < this->size; i++) {
        tmp[i] = buffer[i];
      }
      delete[] this->buffer; //!
      this->buffer = tmp;
      this->buffersize *= 2;
    }
    this->buffer[size] = b;
    this->size++;
  }

  T PopBack() {
    T b = buffer[size - 1];
    this->size--;
    return (b);
  }

  T &operator[](const int i) const {
    return buffer[i];
  }

  int GetSize() {
    return (this->size);
  }

  T *&GetBuffer() {
    return buffer;
  }

private:
  T *buffer;
  int size;
  int buffersize;
};

struct IsEasier {
  bool operator()(const Characteristic &l, const Characteristic &r) const {
    return l.m < r.m;
  }
};

void InOutOptimizaton();

void InitNum(int *num);

void GetCharacteristic(Array<Characteristic> *acrobats);

void PrintAnswer(int answer);

template<class T>
void Swap(T &a, T &b) {
  T x = a;
  a = b;
  b = x;
}

template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l < r;
  }
};

template<class T, class TLess>
void SiftDown(T *a, int i, int n, const TLess &isLess) {
  int first_child = 2 * i + 1;
  int second_child = 2 * i + 2;
  int max = i;
  if (first_child < n && isLess(a[max], a[first_child])) {
    max = first_child;
  }
  if (second_child < n && isLess(a[max], a[second_child])) {
    max = second_child;
  }
  if (max != i) {                //нам не нужно менять элемент так как он уже максимальный.
    Swap(a[i], a[max]);
    SiftDown(a, max, n, isLess);    //востанавливакм свойство кучи
  }
}

template<typename T, class TLess>
void BuildHeap(T *a, int n, const TLess &isLess) {
  for (int i = n / 2; i >= 0; i--) {
    SiftDown(a, i, n, isLess);        //востанавливакм свойство кучи
  }
}

template<typename T, class TLess = IsLess<T>>
void HeapSort(T *a, int n, const TLess &isLess = TLess()) {
  BuildHeap(a, n, isLess);      //строим кучу О(n)
  int size_save = n;
  for (int i = n - 1; i > 0; i--) {
    Swap(a[i], a[0]);    //меняем местами последний элемент с корнем кучи
    size_save--;          // на i-m месте стоит нужный элемент, он не нужен в куче
    SiftDown(a, 0, size_save, isLess);    //востановление свойства кучи
  }
}

int MaxGreedyAcrobats(Characteristic *acrobats, int N) {
  int column = 0;
  int mass_column = 0;

  for (int i = 0; i < N; i++) {
    if (acrobats[i].p >= mass_column) {
      mass_column += acrobats[i].m;
      column++;
    }
  }
  return column;
}

int main() {
  InOutOptimizaton();
  Array<Characteristic> *acrobats_elem = new Array<Characteristic>();
  GetCharacteristic(acrobats_elem);

  Characteristic *acrobats = acrobats_elem->GetBuffer();
  int N = acrobats_elem->GetSize();
  HeapSort(acrobats, N, IsEasier());
  PrintAnswer(MaxGreedyAcrobats(acrobats, N));

  delete acrobats_elem;
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;
}

void GetCharacteristic(Array<Characteristic> *acrobats) {
  Characteristic characteristic;
  for (int i = 0; cin >> characteristic.m >> characteristic.p; i++)
    acrobats->PushBack(characteristic);
}

void PrintAnswer(int answer) {
  cout << answer;
}
