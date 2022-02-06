/*****************************************************
 * Дано невзвешенное дерево.
 * Расстоянием между двумя вершинами будем называть количество ребер в пути,
 * соединяющем эти две вершины.
 * Для каждой вершины определите расстояние до самой удаленной от нее вершины.

  Формат ввода
  В первой строке записано количество вершин n ≤ 10000.
  Затем следует n - 1 строка, описывающая ребра дерева.
  Каждое ребро - это два различных целых числа - индексы вершин в диапазоне [0, n-1].
  Индекс корня – 0. В каждом ребре родительской вершиной является та, чей номер меньше.

  Формат вывода
  Выход должен содержать n строк.
  В i-ой строке выводится расстояние от i-ой вершины до самой удаленной от нее.
 */

#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

struct Note {
  vector<int> connected_peaks;
};

class Tree {
public:
  Note *array = nullptr;

  Tree(int size) {
    array = new Note[size];
  }

  ~Tree() {
    delete[] array;
  }

  void Add(int first_peak, int second_peak) {
    array[first_peak].connected_peaks.push_back(second_peak);
    array[second_peak].connected_peaks.push_back(first_peak);
  }

  void FindPoint_A(int N) {
    int index_A = 0; // будущий индекс вершины а, после выполнения процедуры
    int deep = 0;     // расстояние от запускаемой вершины до текущей
    int max_deep = 0; // искомое самое глубокое расстояние
    FindTheMostDeepestPoint(-1, 0, index_A, deep, max_deep);

    int index_B = 0;
    deep = 0;
    max_deep = 0;
    FindTheMostDeepestPoint(-1, index_A, index_B, deep, max_deep);

    CoutAns(N, index_A, index_B);
  }

  void CoutAns(int N, int index_A, int index_B) {
    int *A_array = new int[N];
    int deep = 0;
    Fill(-1, index_A, deep, A_array);

    int *B_array = new int[N];
    deep = 0;
    Fill(-1, index_B, deep, B_array);

    for (int i = 0; i < N; i++) {
      cout << max(A_array[i], B_array[i]) << endl;
    }
    delete[] A_array;
    delete[] B_array;
  }


  void FindTheMostDeepestPoint(int father, int our_peak, int &our_index, int deep, int &max_deep) {
    if (deep >= max_deep) {
      max_deep = deep;
      our_index = our_peak;
    }
    for (int i = 0; i < array[our_peak].connected_peaks.size(); i++) {
      int v = array[our_peak].connected_peaks[i];
      if (array[our_peak].connected_peaks[i] != father) {
        FindTheMostDeepestPoint(our_peak, v, our_index, deep + 1, max_deep);
      }
    }
  }

  void Fill(int father, int our_peak, int deep, int *&our_array) {
    our_array[our_peak] = deep;
    for (int i = 0; i < array[our_peak].connected_peaks.size(); i++) {
      int v = array[our_peak].connected_peaks[i];
      if (array[our_peak].connected_peaks[i] != father) {
        Fill(our_peak, v, deep + 1, our_array);
      }
    }
  }


};

int main() {
  int N;
  cin >> N;
  int first_v, second_v;
  Tree tree(N);

  for (int i = 0; i < N - 1; i++) {
    cin >> first_v >> second_v;
    tree.Add(first_v, second_v);
  }

  tree.FindPoint_A(N);
}
