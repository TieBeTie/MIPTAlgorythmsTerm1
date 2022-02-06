/***************************************************
   * Реализуйте структуру данных типа “множество строк” на основе
   * динамической хеш-таблицы с открытой адресацией.
   * Хранимые строки непустые и состоят из строчных латинских букв.
   * Хеш-функция строки должна быть реализована с помощью
   * вычисления значения многочлена методом Горнера.
   * Начальный размер таблицы должен быть равным 8-ми.
   * Перехеширование выполняйте при добавлении элементов в случае,
   * когда коэффициент заполнения таблицы достигает 3/4.
   * Структура данных должна поддерживать операции добавления строки в множество,
   * удаления строки из множества и проверки принадлежности данной строки множеству.
   * 1_1. Для разрешения коллизий используйте квадратичное пробирование.
   * i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
   * 1_2. Для разрешения коллизий используйте двойное хеширование.

  Формат ввода
  Каждая строка входных данных задает одну операцию над множеством.
  Запись операции состоит из типа операции и следующей
  за ним через пробел строки, над которой проводится операция.
  Тип операции – один из трех символов: + означает добавление
  данной строки в множество; - означает удаление строки из множества;
  ? означает проверку принадлежности данной строки множеству.
  При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ,
  что он отсутствует в этом множестве.
  При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ,
  что он присутствует в этом множестве.

  Формат вывода
  Программа должна вывести для каждой операции одну из двух строк OK или FAIL.

  Для операции '?': OK, если элемент присутствует во множестве. FAIL иначе.

  Для операции '+': FAIL,
  если добавляемый элемент уже присутствует
  во множестве и потому не может быть добавлен. OK иначе.

  Для операции '-': OK, если элемент
  присутствовал во множестве и успешно удален. FAIL иначе.
 */

#include <iostream>

using std::cin;
using std::cout;
using std::string;

template<class T>
struct Item {
  T key;
  bool exist;
  bool deleted;

  Item() { //exist
    exist = false;
    deleted = false;
    key = "";
  }
};

template<typename T>
struct StringPreHash {
  int operator()(T &key, int mod) {
    int answer = 0;
    int x = 3;
    int length = key.length();

    for (int i = 0; i < length; i++)
      answer = (answer * x + (int) key[i] + 1) % mod;

    return answer;
  }
};

template<typename T>
struct StringPostHash {
  int operator()(T &key, int mod) {
    int answer = 0;
    int x = 5;
    int length = key.length();

    for (int i = 0; i < length; i++)
      answer = (answer * x + (int) key[i] + 1) % mod;

    answer += answer % 2 == 0 ? 1 : 0;
    return answer % mod;
  }
};


template<class T, class TPreHash = StringPreHash<T>, class TPostHash = StringPostHash<T>>
class HashTable {
public:
  HashTable(TPostHash PostHash = StringPostHash<T>(), TPreHash PreHash = StringPreHash<T>()) {
    table = new Item<T>[8];
    table_size = 8;
    size = 0;
    fullness = 0;
    this->PostHash = PostHash;
    this->PreHash = PreHash;
  }

  ~HashTable() {
    delete[] table;
  }

  HashTable(const HashTable &) = delete;

  HashTable(HashTable &&) = delete;

  HashTable &operator=(const HashTable &) = delete;

  HashTable &operator=(HashTable &&) = delete;

  bool Add(T key) {
    CheckRehash();
    int pre = PreHash(key, table_size);
    int post = PostHash(key, table_size);

    for (int i = 0; i < table_size; i++) {
      if (!table[pre].deleted && table[pre].key == key)
        return false;

      if (!table[pre].exist) {
        table[pre].key = key;
        table[pre].exist = true;
        size++;
        return true;
      }

      pre = (pre + post) % table_size;
    }
    return false;
  }

  bool Remove(T key) {
    int pre = PreHash(key, table_size);
    int post = PostHash(key, table_size);

    for (int i = 0; i < table_size; i++) {
      if (!table[pre].exist)
        return false;

      if (!table[pre].deleted && table[pre].key == key) {
        table[pre].deleted = true;
        return true;
      }
      pre = (pre + post) % table_size;

    }
    return false;
  }

  bool Exists(T key) {
    int pre = PreHash(key, table_size);
    int post = PostHash(key, table_size);

    for (int i = 0; i < table_size; i++) {
      if (!table[pre].exist)
        return false;

      if (!table[pre].deleted && table[pre].key == key)
        return true;

      pre = (pre + post) % table_size;
    }
    return false;
  }

  void Rehash() {
    Item<T> *tmp = new Item<T>[table_size * 2];
    int pre, post;
    int count = 0;
    int exists = 0;

    for (int i = 0; i < table_size && count < size; i++) {
      if (table[i].exist) //add to tmp
      {
        count++;
        if (!table[i].deleted) {
          pre = PreHash(table[i].key, table_size * 2);
          post = PostHash(table[i].key, table_size * 2);

          for (int j = 0; j < table_size * 2; j++) {
            if (!tmp[pre].exist) {
              tmp[pre].key = table[i].key;
              tmp[pre].exist = true;
              exists++;
              break;
            }
            pre = (pre + post) % (table_size * 2);
          }
        }
      }
    }

    size = exists;
    delete[] table;
    table = tmp;
    table_size *= 2;
  }

private:
  TPostHash PostHash;
  TPreHash PreHash;
  Item<T> *table;
  double fullness;
  int table_size;
  int size;

  void CheckRehash() {
    fullness = ((double) size) / ((double) table_size);
    if (fullness >= 0.75)
      Rehash();
  }
};

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;
}

void AnswerToComands(HashTable<string> *table) {
  char command;
  string word;
  bool answer;

  while (cin >> command) {
    cin >> word;

    switch (command) {
      case '+':
        answer = table->Add(word);
        break;
      case '?':
        answer = table->Exists(word);
        break;
      case '-':
        answer = table->Remove(word);
        break;
    }

    if (answer)
      cout << "OK " << "\n";
    else
      cout << "FAIL" << "\n";
  }
}

int main() {
  InOutOptimizaton();
  HashTable<string> *table = new HashTable<string>();
  AnswerToComands(table);
  delete table;
}
