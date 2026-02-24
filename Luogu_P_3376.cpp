#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int maxn = 5010;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, S, T;
ll maxflow;
namespace Graph
{
int cnt = 1, head[maxn];
struct edge
{
    int nxt, to, flow;
} e[maxn << 1];
void add(int u, int v, int w)
{
    e[++cnt] = {head[u], v, w};
    head[u] = cnt;
}
}  // namespace Graph
using namespace Graph;
namespace Dicnic
{
ll dis[maxn];
int now[maxn];
queue<int> q;
bool bfs()
{
    while (!q.empty()) q.pop();
    memset(dis, 0xff, sizeof(dis));
    dis[S] = 0;
    q.push(S);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        now[u] = head[u];
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int t = e[i].to;
            if (!e[i].flow || ~dis[t])
                continue;
            dis[t] = dis[u] + 1;
            q.push(t);
            if (t == T)
                return 1;
        }
    }
    return 0;
}
ll dfs(int u, ll flow)
{
    if (u == T)
        return flow;
    int res = flow;
    for (int i = now[u]; i && res; i = e[i].nxt)
    {
        now[u] = i;
        int t = e[i].to;
        if (!e[i].flow || dis[t] != dis[u] + 1)
            continue;
        int d = dfs(t, min(res, e[i].flow));
        if (!d)
        {
            dis[t] = -1;
            continue;
        }
        res -= d;
        e[i].flow -= d;
        // printf("%d %d\n",u,e[i].to);
        e[i ^ 1].flow += d;
    }
    if (res == flow)
        dis[u] = -1;
    return flow - res;
}
}  // namespace Dicnic
using namespace Dicnic;
signed main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &S, &T);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        ll w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, 0);
    }
    while (bfs()){maxflow += dfs(S, INF);puts("");}
    printf("%lld", maxflow);
}