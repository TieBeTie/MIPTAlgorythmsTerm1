/****************************************
 * Дано число N и N строк.
 * Каждая строка содержащит команду
 * добавления или удаления натуральных чисел,
 * а также запрос на получение k-ой порядковой статистики.
 * Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”.
 * Запрос на получение k-ой порядковой статистики задается числом k.
 * Требуемая скорость выполнения запроса - O(log n).
 *
 * Пример 1
    Ввод
      3
      1 0
      2 0
      -1 0
    Вывод
      1 1 2
 */

#include <iostream>

using std::cin;
using std::cout;

template<class T>
struct Node {
  T key;
  int height;
  Node<T> *left;
  Node<T> *right;
  int famaly;

  Node(T k) {
    key = k;
    left = nullptr;
    right = nullptr;
    height = 1;
    famaly = 1;
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

template<typename T>
struct IsLess {
  bool operator()(const T &l, const T &r) const {
    return l < r;
  }
};

template<class T, class TLess = IsLess<T>>
class AVL {
public:
  AVL() {
  }

  ~AVL() {
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

  AVL(const AVL &) = delete;

  AVL(AVL &&) = delete;

  AVL &operator=(const AVL &) = delete;

  AVL &operator=(AVL &&) = delete;

  int Height(Node<T> *node) {
    if (node != nullptr)
      return node->height;
    else
      return 0;
  }

  int Family(Node<T> *node) {
    if (node != nullptr)
      return node->famaly;

    return 0;
  }

  int Balance(Node<T> *node) {
    return Height(node->right) - Height(node->left);
  }

  void FixHeight(Node<T> *node) {
    int left_height = Height(node->left);
    int right_height = Height(node->right);

    if (left_height < right_height)
      node->height = right_height + 1;
    else
      node->height = left_height + 1;
  }

  void FixFamily(Node<T> *node) {
    node->famaly = Family(node->left) + Family(node->right) + 1;
  }

  Node<T> *LeftRotate(Node<T> *left_libra) {
    Node<T> *right_libra = left_libra->right;
    left_libra->right = right_libra->left;
    right_libra->left = left_libra;

    FixHeight(left_libra);
    FixFamily(left_libra);

    FixHeight(right_libra);
    FixFamily(right_libra);

    return right_libra;
  }

  Node<T> *RightRotate(Node<T> *right_libra) {
    Node<T> *left_libra = right_libra->left;
    right_libra->left = left_libra->right;
    left_libra->right = right_libra;

    FixHeight(right_libra);
    FixFamily(right_libra);

    FixHeight(left_libra);
    FixFamily(left_libra);

    return left_libra;
  }

  Node<T> *GreatRotate(Node<T> *node) {
    FixHeight(node);
    FixFamily(node);

    if (Balance(node) == 2) {
      if (Balance(node->right) < 0)
        node->right = RightRotate(node->right);

      return LeftRotate(node);
    }
    if (Balance(node) == -2) {
      if (Balance(node->left) > 0)
        node->left = LeftRotate(node->left);

      return RightRotate(node);
    }
    return (node);
  }

  Node<T> *Insert(Node<T> *node, int k) {
    if (node == nullptr)
      return new Node<T>(k);

    if (comparator(k, node->key))
      node->left = Insert(node->left, k);
    else
      node->right = Insert(node->right, k);

    return GreatRotate(node);
  }

  void Insert(int k) {
    root = Insert(root, k);
  }

  Node<T> *Remove(Node<T> *node, int key) {
    if (node == nullptr)
      return nullptr;

    if (comparator(key, node->key))
      node->left = Remove(node->left, key);
    else if (!comparator(key, node->key) && key != node->key)
      node->right = Remove(node->right, key);

    else {
      Node<T> *left_tree = node->left;
      Node<T> *right_tree = node->right;
      short balance = Balance(node);
      delete node;

      if (left_tree == nullptr)
        return right_tree;

      if (right_tree == nullptr)
        return left_tree;

      if (balance < 0) {
        Node<T> *max = left_tree;
        left_tree = RemoveMaxLeft(left_tree, max);
        max->left = left_tree;
        max->right = right_tree;

        FixHeight(max);
        FixFamily(max);

        return max;
      } else {
        Node<T> *min = right_tree;
        right_tree = RemoveMinRight(right_tree, min);
        min->right = right_tree;
        min->left = left_tree;

        FixHeight(min);
        FixFamily(min);

        return min;
      }
    }

    FixHeight(node);
    FixFamily(node);
    return node;
  }

  void Remove(int key) {
    root = Remove(root, key);
  }

  Node<T> *SearchKey(Node<T> *node, int stat) {
    if (Family(node->left) == stat)
      return node;

    if (Family(node->left) < stat)
      return SearchKey(node->right, stat - Family(node->left) - 1);

    if (Family(node->left) > stat)
      return SearchKey(node->left, stat);
  }

  int StatToKey(int order_statistic) {
    Node<T> *node = SearchKey(root, order_statistic);
    return node->key;
  }

private:
  Node<T> *RemoveMaxLeft(Node<T> *node, Node<T> *&max) {
    if (node->right == nullptr) {
      max = node;
      return node->left;
    }

    node->right = RemoveMaxLeft(node->right, max);

    FixHeight(node);
    FixFamily(node);
    return node;
  }

  Node<T> *RemoveMinRight(Node<T> *node, Node<T> *&min) {
    if (node->left == nullptr) {
      min = node;
      return node->right;
    }

    node->left = RemoveMinRight(node->left, min);

    FixHeight(node);
    FixFamily(node);
    return node;
  }

  TLess comparator;
  Node<T> *root;
};

void PrintVector(int *vector, int size_vector) {
  for (int i = 0; i < size_vector; i++) {
    cout << vector[i] << " ";
  }
}

void PrintAVLOrderStatistic(AVL<int> *tree) {
  int n;
  cin >> n;
  int key, order_statistic;
  int *keys = new int[n];

  for (int i = 0; i < n; i++) {
    cin >> key >> order_statistic;

    if (key < 0)
      tree->Remove(-key);
    else
      tree->Insert(key);

    key = tree->StatToKey(order_statistic);
    keys[i] = key;
  }
  PrintVector(keys, n);
  delete[] keys;
}

int main() {
  //i
  AVL<int> *avl_tree = new AVL<int>();
  PrintAVLOrderStatistic(avl_tree);
  delete avl_tree;
}