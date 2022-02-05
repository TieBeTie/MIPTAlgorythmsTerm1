/******************
     Группа людей называется современниками если был такой момент,
     когда они могли собраться вместе.
     Для этого в этот момент каждому из них должно было уже исполниться 18 лет,
     но ещё не исполниться 80 лет.

     Дан список Жизни Великих Людей.
     Необходимо получить максимальное количество современников.
     В день 18летия человек уже может принимать участие в собраниях,
     а в день 80летия и в день смерти уже не может.

     Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия.
     В этих случаях принимать участие в собраниях он не мог.

    Пример

    Ввод
    2 5 1980 13 11 2055
    1 1 1982 1 1 2030
    2 1 1920 2 1 2000

    Вывод
    3
*/

#include <iostream>
#include <cassert>

using std::cin;
using std::cout;

template<class T>
void Swap(T &a, T &b) {
  T x = a;
  a = b;
  b = x;
}

struct Date {
  int dd, mm, yyyy;
  int alive;
};

struct IsEarly {
  bool operator()(const Date &l, const Date &r) const {
    if (l.yyyy != r.yyyy) {
      return l.yyyy < r.yyyy;
    }
    if (l.mm != r.mm) {
      return l.mm < r.mm;
    }
    return l.dd < r.dd;
  }
};


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

template<typename T>
struct ReadDate {
  void operator()(T &a) const {
    std::cin >> a.dd >> a.mm >> a.yyyy;
  }
};

template<class T, class TRead = ReadDate<T>>
void InitLifes(T *life_line, int count, const TRead &read = TRead()) {
  for (int i = 0; i < count; i += 2) {
    read(life_line[i]);
    read(life_line[i + 1]);
    life_line[i].alive = 1;
    life_line[i + 1].alive = -1;
  }
}


void InOutOptimizaton();

void InitNum(int *num);

bool IsLater(Date l, Date r) {
  if (l.yyyy != r.yyyy) {
    return l.yyyy > r.yyyy;
  }
  if (l.mm != r.mm) {
    return l.mm > r.mm;
  }
  return l.dd > r.dd;
}


bool Adulthood(Date *life_line, int i) {
  Date adult;
  adult.yyyy = life_line[i].yyyy + 18;
  adult.mm = life_line[i].mm;
  adult.dd = life_line[i].dd;
  return IsLater(life_line[i + 1], adult);
}

void CutChildhood(Date *life_line, int i) {
  life_line[i].yyyy += 18;
}

void CutSenility(Date *life_line, int i) {
  Date old_man;
  old_man.yyyy = life_line[i].yyyy + 80;
  old_man.mm = life_line[i].mm;
  old_man.dd = life_line[i].dd;
  if (IsLater(life_line[i + 1], old_man)) {
    life_line[i + 1].yyyy = old_man.yyyy;
    life_line[i + 1].mm = old_man.mm;
    life_line[i + 1].dd = old_man.dd;
  }
}


int CutLife(Date *life_line, int count) {
  int i = 0;
  while (i < count) {
    if (Adulthood(life_line, i)) {
      CutSenility(life_line, i);
      CutChildhood(life_line,
                   i); //порядок обрезки важен, т.к. было проверено, что у человека было детство, а проверка старости не осуществлена
      i += 2;
    } else {
      Swap(life_line[i], life_line[count - 2]); //выбрасываем дату рождения
      Swap(life_line[i + 1], life_line[count - 1]); //выбрасываем дату смерти
      count -= 2;
    }
  }
  return count;
}

void ReadVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cin >> vector[i];
  }
}

void PrintVector(int *vector, int size_vector) {
  for (long long i = 0; i < size_vector; i++) {
    cout << vector[i] << " ";
  }
}

void PrintDates(Date *life_line, int count) {
  for (int i = 0; i < count; i += 2) {
    cout << life_line[i].dd << " " << life_line[i].mm << " " << life_line[i].yyyy << " " << life_line[i].alive << "  ";
    cout << life_line[i + 1].dd << " " << life_line[i + 1].mm << " " << life_line[i + 1].yyyy << " "
         << life_line[i + 1].alive << "\n";
  }
}

bool Today(Date previous_day, Date today) {
  if (previous_day.yyyy == today.yyyy)
    if (previous_day.mm == today.mm)
      return previous_day.dd == today.dd;
  return false;
}

int MaxPeopleMeeting(Date *life_line, int count) {
  int max_meeting = 0;
  int meeting = 0;
  int i = 0;
  Date today;
  while (i < count) {
    today = life_line[i];
    while (Today(today, life_line[i]) == 1 && i < count) {
      meeting += life_line[i].alive;
      i++;

    }
    if (meeting > max_meeting) {
      max_meeting = meeting;
    }
  }
  assert(meeting == 0);
  return max_meeting;
}

void PrintAnswer(int answer) {
  cout << answer;
}

int main() {
  InOutOptimizaton();
  int count;
  InitNum(&count);
  count *= 2;
  Date *life_line = new Date[count];

  InitLifes(life_line, count);
  count = CutLife(life_line, count);
  //cout << "CutLife" << "\n";
  //PrintDates(life_line, count);

  HeapSort(life_line, count, IsEarly());
  //cout << "HeapSort" << "\n";
  //PrintDates(life_line, count);

  //cout << "\n";
  int answer = MaxPeopleMeeting(life_line, count);
  PrintAnswer(answer);
  delete[] life_line;
}


void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;
}