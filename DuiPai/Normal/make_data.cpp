#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

string randomBracket(int n) {
    string s;
    for (int i = 0; i < n; i++) {
        s += (random(0, 1) ? '(' : ')');
    }
    return s;
}

int main(int argc, char* argv[]) {
    int seed = atoi(argv[1]);
    rng.seed(time(0));
    
    int N = random(1, 2000);      // 小数据便于暴力验证
    int Q = random(1, 2000);
    
    cout << N << " " << Q << "\n";
    cout << randomBracket(N) << "\n";
    
    for (int i = 0; i < Q; i++) {
        int L = random(1, N);
        int R = random(L, N);
        cout << L << " " << R << "\n";
    }
    return 0;
}