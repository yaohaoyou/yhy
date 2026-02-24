#include <bits/stdc++.h>
using namespace std;
namespace Fastio
{
    const int L = 1 << 20;
    char gc()
    {
        static char buf[L], *l = buf, *r = buf;
        if (l == r)
            r = (l = buf) + fread(buf, 1, L, stdin);
        return (l == r) ? EOF : *l++;
    }
    char obuf[L], *p = obuf;
    void pc(char c)
    {
        if (p == obuf + L)
            fwrite(obuf, 1, L, stdout), p = obuf;
        *p++ = c;
    }
    void flush() { fwrite(obuf, 1, p - obuf, stdout); }
    struct Reader
    {
        template <typename T>
        Reader &operator>>(T &x)
        {
            x = 0;
            short f = 1;
            char c = gc();
            while (!isdigit(c))
            {
                if (c == '-')
                    f = -1;
                c = gc();
            }
            while (isdigit(c))
                x = 10 * x + (c - '0'), c = gc();
            x *= f;
            return *this;
        }
        Reader() {}
    } cin;
    struct Writer
    {
        template <typename T>
        Writer &operator<<(T x)
        {
            if (x < 0)
                pc('-'), x = -x;
            static short tp = 0, s[40];
            do
            {
                s[++tp] = x % 10, x /= 10;
            } while (x);
            while (tp)
                pc(s[tp--] + '0');
            return *this;
        }
        Writer &operator<<(const char *s)
        {
            int i = 0;
            while (s[i])
                pc(s[i++]);
            return *this;
        }
        Writer &operator<<(char c)
        {
            pc(c);
            return *this;
        }
        Writer() {}
        ~Writer() { flush(); }
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
}
signed main()
{
    // 注意：只能输入整数
    // 使用方式：与正常 cin、cout 基本相同
    int x;
    cin >> x;
    cout << x << '\n';
    return 0;
}
