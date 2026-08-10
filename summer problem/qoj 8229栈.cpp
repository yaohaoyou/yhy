#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
    // 固定参数设置（可自行修改）
    unsigned seed = time(nullptr); // 随机种子

    srand(time(0));
    int n = rand()%20+1;      // 栈的数量
    int m = rand()%30+1;      // 操作的数量
    // 初始化随机数生成器
    mt19937 rng(seed);
    uniform_int_distribution<int> op_type_dist(1, 10); // 决定操作类型
    uniform_int_distribution<int> stack_idx_dist(1, n); // 栈编号
    uniform_int_distribution<int> val_dist(1, 20); // 值范围
    uniform_int_distribution<int> count_dist(1, 20);   // 操作1的x和操作2的w范围
    uniform_int_distribution<int> pos_dist(1, 100);  // 查询位置范围

    // 输出第一行：n m
    cout << n << " " << m << "\n";

    // 生成操作序列
    for (int i = 0; i < m; i++) {
        int op_type_roll = op_type_dist(rng);
        int op;

        // 决定操作类型（40% 操作1，40% 操作2，20% 操作3）
        if (op_type_roll <= 4) op = 1;
        else if (op_type_roll <= 8) op = 2;
        else op = 3;

        if (op == 1) { // 操作1: 1 l r x y
            int l = stack_idx_dist(rng);
            int r = uniform_int_distribution<int>(l, n)(rng);
            int x = count_dist(rng); // 压入次数
            int y = val_dist(rng);   // 压入的值
            cout << "1 " << l << " " << r << " " << x << " " << y << "\n";
        }
        else if (op == 2) { // 操作2: 2 l r w
            int l = stack_idx_dist(rng);
            int r = uniform_int_distribution<int>(l, n)(rng);
            int w = count_dist(rng); // 弹栈次数
            cout << "2 " << l << " " << r << " " << w << "\n";
        }
        else { // 操作3: 3 k p q
            int k = stack_idx_dist(rng);
            int p = pos_dist(rng);
            int q = uniform_int_distribution<int>(p, p+50)(rng); // q >= p
            cout << "3 " << k << " " << p << " " << q << "\n";
        }
    }

    return 0;
}