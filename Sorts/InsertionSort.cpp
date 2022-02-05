/**************************************************
 1_5. База данных

			В базе данных хранится N записей,
		вида (Name, a1, a2, … , ak) — во всех
		записях одинаковое число параметров.
		На вход задачи подаётся приоритет
		полей — перестановка на
		числах 1,...,k — записи нужно
		вывести в соответствии с этим приоритетом.

			В случае, если приоритет полей таков:
		3 4 2 1, то это следует воспринимать так:
		надо читать как: приоритет значений из 3
		колонки самый высокий, приоритет значений из
		колонки 4 ниже, приоритет значений из колонки
		2 ещё ниже, а приоритет значений из колонки
		1 самый низкий.

		Формат ввода
		N (1⩽N⩽1000) k (1⩽k;⩽10) p1 p2 ... pk (перестановка на k числах, разделитель пробел) N строк вида Name a1 a2 ... ak (разделитель — пробел)

		Формат вывода
		N строк с именами согласно приоритету

***************************************************/

#include <iostream>
#include <assert.h>

using std::cin;
using std::cout;
using std::string;


class Data {
public:
  Data() {
    this->k = -1; //данные необходимо инициализировать
  }

  ~Data() {
    delete[] a;
  }

  Data(const Data &other) {
    this->k = other.k;
    this->a = new int[k];
    this->Name = other.Name;
    for (int i = 0; i < k; i++) {
      this->a[i] = other.a[i];
    }
  }

  Data(Data &&other) noexcept {
    this->a = other.a;
    this->k = other.k;
    this->Name = other.Name;
    other.a = nullptr;
  }

  Data &operator=(const Data &other) {
    assert(other.k != -1);
    if (this == &other)
      return *this;

    if (this->k == -1) {
      this->a = new int[other.k];
    }
    this->k = other.k;
    this->Name = other.Name;
    for (int i = 0; i < k; i++) {
      this->a[i] = other.a[i];
    }
    return *this;
  }

  Data &operator=(Data &&other) noexcept {
    if (this == &other)
      return *this;
    if (k != -1)
      delete this->a;
    this->a = other.a;
    this->k = other.k;
    this->Name = other.Name;
    other.a = nullptr;
    return *this;
  }

  void CreateData(int k) {
    this->a = new int[k];
    this->k = k;
  }

  string getName() {
    return this->Name;
  }

  void initNum(int pose, int ball) {
    this->a[pose] = ball;
  }

  void initName(string Name) {
    this->Name = Name;
  }

  int getNum(int pose) {
    return a[pose];
  }

private:
  string Name;
  int k;
  int *a;
};

class DataComparator {
public:
  DataComparator() {}

  DataComparator(int *p, int k) {
    this->size = k;
    this->priority = new int[size];
    for (int i = 0; i < size; i++) {
      this->priority[i] = p[i];
    }
  }

  ~DataComparator() {
    delete[] this->priority;
  }

  DataComparator(const DataComparator &) = delete;

  DataComparator(DataComparator &&) = delete;

  DataComparator &operator=(DataComparator &&) = delete;

  DataComparator &operator=(DataComparator &r) {
    if (this == &r)
      return *this;
    for (int i = 0; i < r.size; i++) {
      this->priority[i] = r.priority[i];
    }
    return *this;
  }

  bool operator()(Data &l, Data &r) const {
    int i = 0;
    for (int i = 0; i < this->size; i++) {
      if (l.getNum(this->priority[i]) < r.getNum(this->priority[i])) {
        return true;
      }
      if (l.getNum(this->priority[i]) > r.getNum(this->priority[i])) {
        return false;
      }
    }
    return false;
  }

private:
  int *priority;
  int size;
};

void InOutOptimizaton();

void InitNum(int *num);

void ReadPriority(int *vector, int size_vector);

void ReadData(Data *base, int k, int N);

void PrintKeysData(Data *base, int N);

template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l < r;
  }
};

template<class T, class TLess = IsLess<T>>
void InsertionSort(T *base, int n, const TLess &isLess = TLess()) {
  int j;
  T tmp;
  for (int i = 1; i < n; i++) {
    j = i - 1;
    tmp = base[j + 1];
    while (j >= 0 && isLess(base[j], tmp)) {
      base[j + 1] = base[j];
      j--;
    }
    base[j + 1] = tmp;
  }
}


int main() {
  int N;
  InitNum(&N);
  int k;
  InitNum(&k);

  int *p = new int[k];
  ReadPriority(p, k);
  DataComparator data_comparator(p, k);
  delete[] p;

  Data *base = new Data[N];
  for (int i = 0; i < N; i++) {
    base[i].CreateData(k);
  }

  ReadData(base, k, N);
  InsertionSort(base, N, data_comparator);
  PrintKeysData(base, N);

  delete[] base;
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;
}

void ReadPriority(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cin >> vector[i];
    vector[i]--;
  }
}

void ReadData(Data *base, int k, int N) {
  int c;
  string Name;
  for (int i = 0; i < N; i++) {
    cin >> Name;
    base[i].initName(Name);
    for (int j = 0; j < k; j++) {
      cin >> c;
      base[i].initNum(j, c);
    }
  }
}

void PrintKeysData(Data *base, int N) {
  for (int i = 0; i < N; i++) {
    cout << base[i].getName() << "\n";
  }
}