/*
 * Дано N кубиков.
 * Требуется определить каким количеством
 * способов можно выстроить из этих кубиков пирамиду.
 * Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.

    Формат ввода
    На вход подается количество кубиков N.

    Формат вывода
    Вывести число различных пирамид из N кубиков.
 */

#include <iostream>

using std::cin;
using std::cout;

void BobBuilder(long long **plan, int n) {
  plan[0][0] = 1;
  for (int i = 1; i < n; i++) {
    plan[i][0] = 0;
    plan[0][i] = 1;
  }
  for (int i = 1; i < n; i++)
    for (int j = 1; j < n; j++)
      if (i >= j)
        plan[i][j] = plan[i][j - 1] + plan[i - j][j - 1];
      else
        plan[i][j] = plan[i][j - 1];
}

int main() {
  int n;
  cin >> n;
  n++;

  long long **plan = new long long *[n];
  for (int i = 0; i < n; i++)
    plan[i] = new long long[n];

  BobBuilder(plan, n);
  cout << plan[n - 1][n - 1];

  for (int i = 0; i < n; i++)
    delete[] plan[i];
  delete[] plan;
}