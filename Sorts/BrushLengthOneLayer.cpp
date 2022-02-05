/*******
   * На числовой прямой окрасили N отрезков.
  Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
  N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].

  Формат ввода
  В первой строке записано количество отрезков.
  В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.

  Формат вывода
  Выведите целое число — длину окрашенной в один слой части.
 */

#include <algorithm>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <vector>
#include <map>

// точка
class Point {
public:
  int64_t x_;
  bool start_;

  explicit Point(int64_t x, bool start) : x_(x), start_(start) {}
};

// сравнение точек
bool isPointLess(const Point &p1, const Point &p2) {
  return p1.x_ < p2.x_;
}

int getSingleLayerNumber(std::vector <Point> &points, size_t n) {
  int64_t result = 0;

  std::sort(points.begin(), points.end(), &isPointLess);
  int64_t layers = 0;

  for (size_t i = 0; i < n; i++) {
    if (layers == 1) {
      result += abs(points[i].x_ - points[i - 1].x_);
    }
    if (points[i].start_) {
      layers++;
    } else {
      layers--;
    }
  }

  return result;
}

int main() {
  size_t n = 0;
  std::cin >> n;

  std::vector <Point> points;
  int64_t x, y;
  for (int64_t i = 0; i < n; i++) {
    std::cin >> x >> y;
    points.emplace_back(x, 1);
    points.emplace_back(y, 0);
  }
  n *= 2;
  std::cout << getSingleLayerNumber(points, n);

  return 0;
}
