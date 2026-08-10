/**
 * 本 grader 为下发给选手使用的 grader，仅作参考，与正式评测时的交互器
 * 不一定相同。 本 grader 支持的 n <= 3000。如果选手需要测试更大的
 * n，请自行修改。 grader 的输入格式如下： 第一行一个整数 n，表示矩阵的大小。
 * 接下来 n 行，每行 n 个整数，表示矩阵的内容。
 * 接下来一个整数 T，表示测试用例的数量。
 * 接下来一行 T 一个整数 z，表示要查询的值。
 *
 * 注：本 grader 在多次调用 solve 之间没有改变 a 的值，但最终的交互器会改变。
 */
#include "disk.h"
#include <iostream>
using namespace std;

static const int N = 3e3 + 2, V = 1e6 + 5;
static int n, a[N][N];
static bool b[V];
static int tot_query = 0;

int query(int x, int y) {
  ++tot_query;
  if (x < 1 || x > n || y < 1 || y > n)
    return -1;
  return a[x][y];
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      b[a[i][j]] = true;
    }
  }

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    int z;
    cin >> z;
    int pos = solve(n, z);
    if (!pos && !b[z] || pos && query((pos - 1) / n, (pos - 1) % n + 1) == z) {
      cout << "OK, z = " << z << ", " << (b[z] ? "exists" : "not exists")
           << endl;
    } else {
      cout << "WA, z = " << z << ", " << (b[z] ? "exists" : "not exists")
           << endl;
    }
  }

  // 你用到的总查询数
  cout << "Total queries: " << tot_query << endl;
  return 0;
}