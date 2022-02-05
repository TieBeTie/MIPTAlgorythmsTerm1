/*************************
Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.

Обрабатывать команды push back и pop front.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

Формат вывода
 Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

#include <iostream>
#include <assert.h>

using std::cin;
using std::cout;

void InOutOptimizaton();

bool QueueChecker();

void InitNum(int *num);

void PrintAnswer(bool answer);

class Pair {
public:
  Pair(Pair *first, int second) {
    this->first = first;
    this->second = second;
  }

  ~Pair() {

  }

  int getValue() {
    return (this->second);
  }

  Pair *getNext() {
    return (this->first);
  }

private:
  Pair *first;
  int second;
};

class Stack {
public:
  Stack() {
    this->buffer = new int[2];
    this->size = 0;
    this->buffersize = 2;
  }

  ~Stack() {
    delete[] this->buffer;
  }

  void pushBack(int b) {
    if (this->size == this->buffersize) {
      int *tmp = new int[this->buffersize * 2];
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

  int popBack() {
    if (this->size == 0) {
      return (-1);
    }
    int b = buffer[size - 1];
    this->size--;
    return (b);
  }

  int getSize() {
    return (this->size);
  }

private:
  int *buffer;
  int size;
  int buffersize;
};

class Queue {
public:
  Queue() {
    this->head = new Stack();
    this->tail = new Stack();
  }

  ~Queue() {
    delete[] this->head;
    delete[] this->tail;
  }

  void pushFront(int b) {
    this->head->pushBack(b);
  }

  int popBack() {
    if (this->tail->getSize() != 0) {
      return (this->tail->popBack());
    } else {
      while (this->head->getSize() != 0) {
        this->tail->pushBack(head->popBack());
      }
      if (this->tail->getSize() > 0) {
        return (this->tail->popBack());
      } else {
        return (-1);
      }
    }
  }

private:
  Stack *head;
  Stack *tail;
};

int main() {
  InOutOptimizaton();
  bool queue_answer = true;
  queue_answer = QueueChecker();
  PrintAnswer(queue_answer);
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

/*********************************************
Если в очереди отсутсвуют необходимые элементы,
то функция возвращает false,
**********************************************/
bool QueueChecker() {
  Queue *queue = new Queue();
  int i, n, a, b;
  InitNum(&n);
  i = 0;
  int answer_pop;
  while (i < n) {
    cin >> a >> b;
    if (a == 3) {
      queue->pushFront(b);
    } else if (a == 2) {
      answer_pop = queue->popBack();
      if (answer_pop != b) {
        return (false);
      }
    }
    i++;
  }
  return (true);
}


void InitNum(int *num) {
  cin >> *num;
}

void PrintAnswer(bool answer) {
  if (answer)
    cout << "YES";
  else
    cout << "NO";
}