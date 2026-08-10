#include <bits/stdc++.h>

#include "pen.h"
using namespace std;

/*
 * 笔测试(pen)本地样例交互库(grader)
 *
 * 选手本地编译:g++ grader.cpp <你的源文件> -O2 -std=c++17 -o pen
 * 运行:./pen < 数据.in
 *   - .in 第一行为 T N C;
 *   - 随后 T 行,每行 N 个整数,为各组真实的墨水排列(0..N-1),供确定性测试。
 * 输出:一行 "succeeded"(成功组数达到 C)或 "failed"(未达到);
 *      违反协议则输出 "invalid <原因>"。
 */
static int T, N, C;
static vector<vector<short>> perm;
static vector<vector<unsigned char>> used;
static int cur_case;
static int write_count;

int try_write(int pen) {
    if (pen < 1 || pen > N) {
        cout << "invalid bad_query\n";
        exit(0);
    }
    if (++write_count > N * (N + 1) / 2) {
        cout << "invalid too_many_writes\n";
        exit(0);
    }
    int j = pen - 1;
    if (used[cur_case][j] < (unsigned char)perm[cur_case][j]) {
        ++used[cur_case][j];
        return 1;
    }
    return 0;
}

int main() {
    freopen("pen3.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> T >> N >> C)) return 0;

    perm.assign(T, vector<short>(N));
    used.assign(T, vector<unsigned char>(N, 0));
    bool ok = true;
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            if (!(cin >> x)) { ok = false; break; }
            perm[i][j] = (short)x;
        }
        if (!ok) break;
    }
    if (!ok) {
        cout << "invalid bad_data\n";
        return 0;
    }

    int s = 0;
    for (int i = 0; i < T; ++i) {
        cur_case = i;
        write_count = 0;
        auto res = solve_one(N);
        int u = res.first, v = res.second;
        if (u < 1 || u > N || v < 1 || v > N || u == v) {
            cout << "invalid bad_answer\n";
            return 0;
        }
        int remu = perm[i][u - 1] - used[i][u - 1];
        int remv = perm[i][v - 1] - used[i][v - 1];
        if (remu + remv >= N) ++s;
    }
    printf("ac %d\n",s);
    cout << (s >= C ? "succeeded" : "failed") << "\n";
    return 0;
}
