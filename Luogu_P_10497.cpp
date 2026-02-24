#include <bits/stdc++.h>
#define int __int128
#define ri long long
using namespace std;
const int maxn = 1e5 + 10;
int x1, m1, x2, m2, x, y;
ri n;
ri a[maxn], b[maxn];
int exgcd(int a, int b, int &x, int &y)
{
    int m = a;
    if (b == 0)
        x = 1, y = 0;
    else
        m = exgcd(b, a % b, y, x), y -= a / b * x;
    return m;
}
int gcd(int x, int y)
{
    if (x < y)
        swap(x, y);
    if (x % y == 0)
        return y;
    return gcd(y, x % y);
}
int lcm(int x, int y) { return x / gcd(x, y) * y; }
void excrt(int id)
{
    int d = exgcd(m1, m2, x, y);
    int c = x2 - x1;
    if (c % d != 0)
    {
        puts("-1");
        exit(0);
    }
    x = (x * c / d + (m2 / d)) % (m2 / d);
    int mod = lcm(m1, m2);
    x1 = (m1 * x + x1 + mod) % mod;
    m1 = mod;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i], &b[i]);
        m2 = a[i], x2 = b[i];
        if (i > 1)
            excrt(i);
        else
            m1 = a[i], x1 = b[i];
    }
    printf("%lld", (ri)(x1 % m1));
}
