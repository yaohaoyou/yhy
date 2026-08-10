#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;

ll modpow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

vector<ll> fact, invfact, pow2, inv_pow2;

void precompute(int N) {
    fact.resize(N + 1); invfact.resize(N + 1);
    pow2.resize(N + 1); inv_pow2.resize(N + 1);

    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % MOD;
    invfact[N] = modpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % MOD;

    pow2[0] = 1;
    for (int i = 1; i <= N; ++i) pow2[i] = pow2[i - 1] * 2 % MOD;

    ll inv2 = modpow(2, MOD - 2);
    inv_pow2[0] = 1;
    for (int i = 1; i <= N; ++i) inv_pow2[i] = inv_pow2[i - 1] * inv2 % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

// 长度为 m，最长连续 1 <= k 的方案数
ll f(int m, int k) {
    if (k >= m) return pow2[m];
    ll res = 0;
    int k1 = k + 1, k2 = k + 2;
    for (int i = 0; ; ++i) {
        int p = m - i * k2;
        if (p < 0) break;
        ll term1 = nCr(p + i, i) * pow2[p] % MOD;
        int q = p - k1;
        ll term2 = (q >= 0) ? nCr(q + i, i) * pow2[q] % MOD : 0;
        ll term = (term1 - term2 + MOD) % MOD;
        if (i & 1) res = (res - term + MOD) % MOD;
        else       res = (res + term) % MOD;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;
    cin >> N >> S;
    precompute(N);

    // 统计每段 '.' 的长度
    vector<int> cnt(N + 1, 0);
    int Q = 0, cur = 0;
    for (char ch : S) {
        if (ch == '.') {
            ++cur;
        } else {
            if (cur > 0) {
                ++cnt[cur];
                Q += cur;
                cur = 0;
            }
        }
    }
    if (cur > 0) {
        ++cnt[cur];
        Q += cur;
    }

    vector<ll> G(N + 1, pow2[Q]);   // G[k] 最终为最长 <= k 的总方案数

    for (int m = 1; m <= N; ++m) {
        if (cnt[m] == 0) continue;
        int c = cnt[m];
        ll inv2m = inv_pow2[m];
        // 只更新 k < m 的部分
        for (int k = 0; k < m; ++k) {
            ll fk = f(m, k);
            ll ratio = fk * inv2m % MOD;
            ll val = modpow(ratio, c);
            G[k] = G[k] * val % MOD;
        }
        // k >= m 时比值为 1，无需更新
    }

    // 差分得到恰好为 k 的答案
    for (int k = 1; k <= N; ++k) {
        ll ans = (G[k] - G[k - 1] + MOD) % MOD;
        cout << ans << '\n';
    }

    return 0;
}