#include <bits/stdc++.h>

using namespace std;

#include "islands.h"

static int n, limit, used, case_id;
static vector <vector <int> > tree;
static set <pair <int, int> > hidden;
static bool finished, active;

[[noreturn]] void fail(const string &reason) {
  cout << "WA in case " << case_id << ": " << reason << '\n';
  exit(0);
}

pair <int, int> farthest(int s, const vector <char> &in) {
  vector <int> d(n + 1, -1);
  queue <int> q;
  q.push(s), d[s] = 0;
  int p = s;
  while (!q.empty()) {
    int x = q.front(); q.pop();
    if (d[x] > d[p]) p = x;
    for (int y : tree[x]) if (in[y] && d[y] == -1) {
      d[y] = d[x] + 1;
      q.push(y);
    }
  }
  return {p, d[p]};
}

int query(const vector <int> &s) {
  if (!active) fail("query was called outside solve");
  if (finished) fail("query was called after answer");
  if (s.empty()) fail("query received an empty set");
  if (++used > limit) fail("query limit exceeded: used " + to_string(used) + ", limit " + to_string(limit));
  vector <char> in(n + 1), vis(n + 1);
  for (int x : s) {
    if (x < 1 || x > n) fail("query contains an out-of-range vertex " + to_string(x));
    if (in[x]) fail("query contains vertex " + to_string(x) + " more than once");
    in[x] = 1;
  }
  if (s.size() == 1) return 1;
  if (s.size() == 2) {
    int x = s[0], y = s[1];
    if (x > y) swap(x, y);
    return hidden.count({x, y}) ? 2 : 1;
  }
  int ans = 1;
  for (int i = 1; i <= n; ++i) if (in[i] && !vis[i]) {
    queue <int> q;
    q.push(i), vis[i] = 1;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (int y : tree[x]) if (in[y] && !vis[y]) vis[y] = 1, q.push(y);
    }
    int p = farthest(i, in).first;
    ans = max(ans, farthest(p, in).second + 1);
  }
  return ans;
}

void answer(const vector <int> &u, const vector <int> &v) {
  if (!active) fail("answer was called outside solve");
  if (finished) fail("answer was called more than once");
  if (u.size() != v.size()) fail("answer vectors have different lengths");
  if (u.size() != (size_t)n - 1) fail("answer must contain exactly " + to_string(n - 1) + " edges");
  set <pair <int, int> > got;
  for (int i = 0; i < n - 1; ++i) {
    int x = u[i], y = v[i];
    if (x < 1 || x > n || y < 1 || y > n) fail("answer edge " + to_string(i) + " has an out-of-range endpoint");
    if (x == y) fail("answer edge " + to_string(i) + " is a self-loop");
    if (x > y) swap(x, y);
    if (!got.insert({x, y}).second) fail("answer repeats edge " + to_string(x) + " " + to_string(y));
  }
  if (got != hidden) fail("submitted edge set is not the hidden tree");
  finished = true;
}

int main() {
  freopen("islands4.in","r",stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests;
  if (!(cin >> tests)) fail("cannot read the number of cases");
  if (tests < 1 || tests > 20) fail("the number of cases is outside [1, 20]");
  for (case_id = 1; case_id <= tests; ++case_id) {
    if (!(cin >> n >> limit)) fail("cannot read n and L");
    if (n < 2 || n > 256 || limit < 1) fail("invalid n or L in local input");
    used = 0, finished = false, active = false;
    hidden.clear(), tree.assign(n + 1, {});
    for (int i = 1; i < n; ++i) {
      int x, y;
      if (!(cin >> x >> y)) fail("cannot read hidden edge " + to_string(i));
      if (x < 1 || x > n || y < 1 || y > n || x == y) fail("hidden edge " + to_string(i) + " is invalid");
      if (x > y) swap(x, y);
      if (!hidden.insert({x, y}).second) fail("hidden input contains a duplicate edge");
      tree[x].push_back(y), tree[y].push_back(x);
    }
    vector <char> vis(n + 1);
    queue <int> q;
    q.push(1), vis[1] = 1;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (int y : tree[x]) if (!vis[y]) vis[y] = 1, q.push(y);
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) fail("hidden input is not a tree");
    active = true;
    solve(n, limit);
    active = false;
    if (!finished) fail("solve returned without calling answer");
    printf("used = %d\n",used);
  }
  cout << "OK\n";
  return 0;
}
