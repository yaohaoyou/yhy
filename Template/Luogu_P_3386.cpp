//  P3386 【模板】二分图最大匹配
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, c;
namespace Graph
{
    int head[maxn];
    int cnt;
    struct edge
    {
        int nxt, to;
    } e[maxn << 1];
    void add(int u, int v)
    {
        e[++cnt] = {head[u], v};
        head[u] = cnt;
    }
}
using namespace Graph;
int fr[maxn];
bool vis[maxn];
bool dfs(int u)
{
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int t = e[i].to;
        if (!vis[t])
        {
            vis[t]=1;
            if (!fr[t] || dfs(fr[t]))
            {
                fr[t] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= c; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        y += n;
        add(x, y);
        add(y, x);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(vis,0,sizeof(vis));
        vis[i]=1;
        ans += dfs(i);
    }
    // for (int i = 1; i <= m; i++)
    // {
    //     printf("%d ", fr[i]);
    // }
    printf("%d\n", ans);
}