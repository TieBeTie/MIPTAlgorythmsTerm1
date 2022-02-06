/*************************************
 * Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево,
 * заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root,
 * если root→Key ≤ K, то узел K добавляется в правое поддерево root;
 * иначе в левое поддерево root. Выведите элементы в порядке in-order (слева направо).

Рекурсия запрещена.
 */

#include <iostream>

using std::cin;
using std::cout;

void InOutOptimizaton();

void InitNum(int *num);

template<class T>
struct Node {
  T key;
  Node *left;
  Node *right;

  Node(T k) {
    key = k;
    left = nullptr;
    right = nullptr;
  }
};

template<class T>
class Stack {
public:
  Stack() {
    this->buffer = new T[2];
    this->size = 0;
    this->buffersize = 2;
  }

  Stack(const Stack &) = delete;

  Stack(Stack &&) = delete;

  Stack &operator=(const Stack &) = delete;

  Stack &operator=(Stack &&) = delete;

  ~Stack() {
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

  int GetSize() {
    return (this->size);
  }

private:
  T *buffer;
  int size;
  int buffersize;
};

template<typename T>
void Visit(T key) {
  cout << key << " ";
}

template<class T>
void InOrderTraversal(Node<T> *root) {
  if (root == nullptr)
    return;

  Stack<Node<T> *> bag;
  Node<T> *tmp = root;

  while (bag.GetSize() != 0 || tmp != nullptr) {
    while (tmp != nullptr) {
      bag.PushBack(tmp);
      tmp = tmp->left;
    }

    tmp = bag.PopBack();
    Visit(tmp->key);

    tmp = tmp->right;
  }
}

template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l <= r;
  }
};

template<class T, class TLess = IsLess<T>>
class BinaryTree {
public:
  BinaryTree(TLess comparator = IsLess<T>()) {
    root = nullptr;
    this->comparator = comparator;
  }

  BinaryTree(const BinaryTree &) = delete;

  BinaryTree(BinaryTree &&) = delete;

  BinaryTree &operator=(const BinaryTree &) = delete;

  BinaryTree &operator=(BinaryTree &&) = delete;

  ~BinaryTree() {
    Stack<Node<T> *> bag;
    Node<T> *tmp;

    if (root == nullptr)
      return;

    bag.PushBack(root);

    while (bag.GetSize() != 0) {
      tmp = bag.PopBack();

      if (tmp->left != nullptr)
        bag.PushBack(tmp->left);

      if (tmp->right != nullptr)
        bag.PushBack(tmp->right);

      delete tmp;
    }
  }

  void Insert(T key) {
    if (root == nullptr) {
      root = new Node<T>(key);
      return;
    }

    Node<T> *head = root;
    Node<T> *tale = root;
    bool direction;

    while (head != nullptr) {
      if (comparator(head->key, key)) {
        tale = head;
        head = head->right;
        direction = 0;
      } else {
        tale = head;
        head = head->left;
        direction = 1;
      }
    }

    if (direction == 0)
      tale->right = new Node<T>(key);
    else
      tale->left = new Node<T>(key);
  }

  Node<T> *GetRoot() {
    return (this->root);
  }

private:
  Node<T> *root;
  TLess comparator;
};

int main() {
  InOutOptimizaton();
  int N;
  InitNum(&N);
  BinaryTree<int> *bin_tree = new BinaryTree<int>();
  int key;

  for (int i = 0; i < N; i++) {
    cin >> key;
    bin_tree->Insert(key);
  }
  InOrderTraversal(bin_tree->GetRoot());
  delete bin_tree;
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;
}
