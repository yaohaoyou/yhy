#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define sz(x) (int)(x).size()
using ll = long long;

const int kn = 2010;
int n, m, tot;
string src, dst;
bool g[kn][kn], vis[kn];

vector<int> read_set(InStream& ouf) {
    memset(vis, 0, sizeof(vis));
    vector<int> a(tot);
    for (int& i : a) {
        i = ouf.readInt(1, n);
        if (vis[i]) ouf.quitf(_wa, "stone positions are not distinct");
        vis[i] = true;
    }
    return a;
}

// lev = 1: 30
// lev = 2: 70
// lev = 3: 100

bool check(InStream& ouf, int& lev, ll& area) {
    string ans = upperCase(ouf.readToken());
    if (ans == "NO") return false;
    if (ans != "YES") ouf.quitf(_wa, "expected YES or NO, found %s", ans.c_str());
    int k = ouf.readInt(0, 2 * n * n);
    area += (ll)(k + 1) * n;
    vector<int> last = read_set(ouf);
    for (int i : last)
        if (src[i] == '0')
            ouf.quitf(_wa, "initially there is no stone on node %d", i);
    rep (i, 1, k) {
        vector<int> cur = read_set(ouf);
        rep (j, 0, tot - 1)
            if (!g[last[j]][cur[j]])
                ouf.quitf(_wa, "in operation %d, stone moves from %d to %d, but there is no edge",
                          i, last[j], cur[j]);
        last = cur;
    }
    for (int i : last)
        if (dst[i] == '0') lev = min(lev, 1);
    if (k > 2 * n) lev = min(lev, 2);
    return true;
}

int main(int argc, char* argv[]) {
    cin.tie(0)->sync_with_stdio(0);
    registerTestlibCmd(argc, argv);
    setName("abcyz");
    int t = inf.readInt(1, 1000);
    int lev = 3;
    ll area = 0;
    while (t--) {
        n = inf.readInt(1, 2000);
        m = inf.readInt(0, 1e4);
        string pattern = "[01]{" + to_string(n) + "}";
        src = inf.readToken(pattern);
        dst = inf.readToken(pattern);
        tot = count(begin(src), end(src), '1');
        src = " " + src, dst = " " + dst;
        memset(g + 1, 0, n * sizeof(g[0]));
        while (m--) {
            int u = inf.readInt(1, n);
            int v = inf.readInt(1, n);
            g[u][v] = g[v][u] = true;
        }
        bool pans = check(ouf, lev, area);
        bool jans = upperCase(ans.readToken()) == "YES";
        if (jans > pans) quitf(_wa, "jury finds a solution but participant doesn't");
        else if (pans > jans) quitf(_fail, "participant finds a solution but jury doesn't");
    }
    if (area > (int)1e7) quitf(_wa, "participant's solution is too long");
    if (lev == 3) quitf(_ok, "ok");
    else quitp(lev == 1 ? 0.3 : 0.7);
}
