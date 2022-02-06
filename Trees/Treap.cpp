/***************************
 * Дано число N < 106 и последовательность
 * пар целых чисел из [-231, 231] длиной N.
 * Построить декартово дерево из N узлов,
 * характеризующихся парами чисел (Xi, Yi).
 * Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi
 * в декартовом дереве. Добавление узла в декартово
 * дерево выполняйте второй версией алгоритма,
 * рассказанного на лекции:
 * При добавлении узла (x, y) выполняйте спуск
 * по ключу до узла P с меньшим приоритетом.
 * Затем разбейте найденное поддерево по ключу x так,
 * чтобы в первом поддереве все ключи меньше x,
 * а во втором больше или равны x.
 * Получившиеся два дерева сделайте дочерними для нового узла (x, y).
 * Новый узел вставьте на место узла P.
 * Построить также наивное дерево поиска по ключам Xi.
 * Равные ключи добавляйте в правое поддерево.
 * Вычислить количество узлов в самом широком слое
 * декартового дерева и количество узлов в самом
 * широком слое наивного дерева поиска.
 * Вывести их разницу.
 * Разница может быть отрицательна.
 *
 * Пример 1
  Ввод
  10
  5 11
  18 8
  25 7
  50 12
  30 30
  15 15
  20 10
  22 5
  40 20
  45 9
  Вывод
  1
 */

#include <iostream>

using std::cin;
using std::cout;

void InOutOptimizaton();

void InitNum(int *num);

void ReadVector(int *vector, int size_vector);

void PrintAnswer(int answer);


template<class T>
class Stack {
public:
  Stack() {
    this->buffer = new T[2];
    this->size = 0;
    this->buffersize = 2;
  }

  ~Stack() {
    delete[] this->buffer;
  }

  void PushBack(T b) {
    if (this->size == this->buffersize) {
      T *tmp = new T[this->buffersize * 2];
      for (int i = 0; i < this->size; i++) {
        tmp[i] = buffer[i];
      }
      delete[] this->buffer;
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

template<class T>
struct Node {
  T key;
  int y;
  Node<T> *left;
  Node<T> *right;

  Node(T key) {
    this->key = key;
    y = -1;
    left = nullptr;
    right = nullptr;
  }

  Node(T key, int y) {
    this->key = key;
    this->y = y;
    left = nullptr;
    right = nullptr;
  }

  Node(T key, int y, Node *left, Node right) {
    this->key = key;
    this->y = y;
    this->left = left;
    this->right = right;
  }
};


template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l < r;
  }
};

template<class T, class TLess = IsLess<T>>
class Treap {
public:
  Treap(TLess comparator = IsLess<T>()) {
    root = nullptr;
    this->comparator = comparator;
  }

  ~Treap() {
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

  Treap(const Treap &) = delete;

  Treap(Treap &&) = delete;

  Treap &operator=(const Treap &) = delete;

  Treap &operator=(Treap &&) = delete;

  Node<T> *Merge(Node<T> *l, Node<T> *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;

    if (r->y < l->y) {
      Node<T> *new_r = Merge(l->right, r);
      return new Node<T> *(l->key, l->y, l->left, new_r);
    } else {
      Node<T> *new_l = Merge(l, r->left);
      return new Node<T>(r->key, r->y, new_l, r->right);
    }
  }

  void Split(T key, Node<T> *node, Node<T> *&l, Node<T> *&r) {
    if (comparator(key, node->key)) {
      if (node->left == nullptr)
        l = nullptr;
      else
        Split(key, node->left, l, node->left);

      r = node;
    } else {
      if (node->right == nullptr)
        r = nullptr;
      else
        Split(key, node->right, node->right, r);

      l = node;
    }
  }

  void Insert(Node<T> *&node, Node<T> *new_node) {
    if (node == nullptr) {
      node = new_node;
      return;
    }
    if (new_node->y < node->y) {
      if (comparator(new_node->key, node->key)) {
        if (node->left != nullptr)
          Insert(node->left, new_node);
        else
          node->left = new_node;
      } else {
        if (node->right != nullptr)
          Insert(node->right, new_node);
        else
          node->right = new_node;
      }
    } else {
      Split(new_node->key, node, new_node->left, new_node->right);
      node = new_node;
    }
  }

  void Add(int key, int y) {
    Node<T> *new_node = new Node<T>(key, y);
    Insert(root, new_node);
  }

  Node<T> *GetRoot() {
    return root;
  }

private:
  Node<T> *root;
  TLess comparator;
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

  void Add(T key) {
    if (root == nullptr) {
      root = new Node<T>(key);
      return;
    }

    Node<T> *head = root;
    Node<T> *tale = root;
    bool direction;

    while (head != nullptr) {
      if (comparator(head->key, key) || head->key == key) {
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
    return root;
  }

private:
  Node<T> *root;
  TLess comparator;
};

template<class T>
int MaxBreadthSize(Node<T> *root) {
  Stack<Node<T> *> EvenBreadth;
  Stack<Node<T> *> OddBreadth;
  Node<T> *tmp = new Node<T>(root->key);
  int max = 0;

  EvenBreadth.PushBack(root);
  while (EvenBreadth.GetSize() != 0 || OddBreadth.GetSize() != 0) {
    if (max < EvenBreadth.GetSize())
      max = EvenBreadth.GetSize();

    while (EvenBreadth.GetSize() != 0) {
      tmp = EvenBreadth.PopBack();

      if (tmp->left != nullptr)
        OddBreadth.PushBack(tmp->left);

      if (tmp->right != nullptr)
        OddBreadth.PushBack(tmp->right);
    }

    if (max < OddBreadth.GetSize())
      max = OddBreadth.GetSize();

    while (OddBreadth.GetSize() != 0) {
      tmp = OddBreadth.PopBack();

      if (tmp->left != nullptr)
        EvenBreadth.PushBack(tmp->left);

      if (tmp->right != nullptr)
        EvenBreadth.PushBack(tmp->right);
    }
  }
  return max;
}

void GrowTreap(Treap<int> *treap, int *vector, int N) {
  for (int i = 0; i < N; i += 2) {
    treap->Add(vector[i], vector[i + 1]);
  }
}

void GrowBinaryTree(BinaryTree<int> *bin_tree, int *vector, int N) {
  for (int i = 0; i < N; i += 2) {
    bin_tree->Add(vector[i]);
  }
}

int main() {
  InOutOptimizaton();
  int N;
  InitNum(&N);
  N = 2 * N;
  int *vector = new int[N];
  ReadVector(vector, N);

  Treap<int> *treap = new Treap<int>();
  GrowTreap(treap, vector, N);
  int max_treap_generation = MaxBreadthSize(treap->GetRoot());
  delete treap;

  BinaryTree<int> *bin_tree = new BinaryTree<int>();
  GrowBinaryTree(bin_tree, vector, N);
  int max_bin_tree_generation = MaxBreadthSize(bin_tree->GetRoot());
  delete bin_tree;

  PrintAnswer(max_treap_generation - max_bin_tree_generation);
  delete[] vector;
}

void InOutOptimizaton() {
  std::ios::sync_with_stdio(0);
  cin.tie(0);
}

void InitNum(int *num) {
  cin >> *num;

}

void ReadVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cin >> vector[i];
  }
}

void PrintAnswer(int answer) {
  cout << answer;
}