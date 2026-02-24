//  P1439 【模板】最长公共子序列
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10, inf = 1e9 + 7;
int n, a[maxn], b[maxn], pac[maxn], ans = 0, f[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), pac[a[i]] = i;
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]), f[i] = inf;
    for (int i = 1; i <= n; i++)
    {
        if (pac[b[i]] > f[ans])
        {
            f[++ans] = pac[b[i]];
        }
        else
        {
            int k = upper_bound(f + 1, f + ans + 1, pac[b[i]]) - f;
            f[k] = min(pac[b[i]], f[k]);
        }
    }
    printf("%d", ans);
}