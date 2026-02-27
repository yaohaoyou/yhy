#include <bits/stdc++.h>
#include "testlib.h"
#define For(i, j, k) for (int i = (j); i <= (k); ++i)
#define ForDown(i, j, k) for (int i = (j); i >= (k); --i)
#define Debug(fmt, args...) fprintf(stderr, "(func %s, line #%d): " fmt, __func__, __LINE__, ##args), fflush(stderr)
#define debug(fmt, args...) fprintf(stderr, fmt, ##args), fflush(stderr)
#define within :
#define WTF main
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
inline int read() {
  char ch = getchar(); int x = 0, f = 1;
  while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
  while (ch >= '0' && ch <= '9')
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * f;
}
int n, m; __int128 a[N], b[N];
set<int> G[N];
void wtf(int TT) {
  n = inf.readInt(), m = inf.readInt();
  For(i, 1, n) G[i].clear();
  For(i, 1, n) a[i] = inf.readInt(); For(i, 1, n) b[i] = inf.readInt();
  For(i, 1, m) {
    int u = inf.readInt(), v = inf.readInt();
    G[u].emplace(v), G[v].emplace(u);
  }
  string op = ouf.readString(), res = ans.readString();
  if(op != "Yes" && op != "No") quitf(_wa, "Yes or No?");
  if(op == "No" && res == "Yes") quitf(_wa, "There's a solution but you don't find it.");
  else if(op == "Yes" && res == "No") quitf(_fail, "Are you kidding me or std is wrong.");
  if(op == "No") return;
  int stp = ouf.readInt(); if(stp > n) quitf(_wa, "Your construction has too mush steps."); ouf.readEoln();
  For(i, 1, stp) {
    int x = ouf.readInt(1, n), y = ouf.readInt(1, n), z = ouf.readInt(1, n);
    if(x == z) quitf(_wa, "Your construction is invalid."); 
    ll nc = ouf.readLong((ll)-1e18, (ll)1e18); ouf.readEoln();
    if(!(G[x].count(y) && G[y].count(z))){
      debug("%d %d %d\n",x,y,z);
      quitf(_wa, "There isn't that edge.");
    }
    a[x] += nc, a[z] += nc, a[y] -= 2 * nc;
  } ForDown(i, n, 1) if(a[i] != b[i]) debug("%d %d\n",TT,i),quitf(_wa, "Your construction is wrong.");
  debug("OK\n");
}
signed WTF(int argc, char **argv) {
  registerTestlibCmd(argc, argv);
  int T = inf.readInt();for(int i=1;i<=T;i++)wtf(i);
  quitf(_ok, "OK");
  return 0;
}
