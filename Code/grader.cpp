#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "diameter.h"

namespace {
static void WA(std::string err) {
	std::cout << "WA: " << err << std::endl;
	exit(0);
}

static const int N = 2e5 + 10;
static int subid, n;
static std::vector<int> e[N];

static int fa[N], dep[N], cnt, p[N], pos[N], l[N], r[N];
static void dfs(int u) {
	p[++cnt] = u, pos[u] = cnt;
	dep[u] = dep[fa[u]] + 1;
	l[u] = cnt;
	for (auto v : e[u])
		if (v != fa[u]) {
			fa[v] = u, dfs(v);
			p[++cnt] = u;
		}
	r[u] = cnt;
}

static int lg[N];
static std::pair<int, int> mn[N][20];
static void init() {
	cnt = 0, dfs(1), lg[0] = -1;
	for (int i = 1; i <= cnt; i++) {
		mn[i][0] = std::make_pair(dep[p[i]], p[i]);
		lg[i] = lg[i >> 1] + 1;
	}
	for (int j = 1; j <= lg[cnt]; j++) {
		for (int i = 1; i <= cnt - (1 << j) + 1; i++) {
			mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
		}
	}
}
static int LCA(int x, int y) {
	int l = pos[x], r = pos[y];
	if (l > r) std::swap(l, r);
	int tmp = lg[r - l + 1];
	return std::min(mn[l][tmp], mn[r - (1 << tmp) + 1][tmp]).second;
}

static int cntq2;
static int cntq1;

static int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)]; }

static void solve() {
	cntq1 = cntq2 = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	init();
	std::pair<int, int> ans = find_diameter(subid, n);
	int x = 1, y = 1;
	for (int i = 1; i <= n; i++)
		if (dis(x, i) > dis(x, y)) y = i;
	x = y, y = 1;
	for (int i = 1; i <= n; i++)
		if (dis(x, i) > dis(x, y)) y = i;
	if (ans.first < 1 || ans.first > n) {
		WA("find wrong diameter!");
	}
	if (ans.second < 1 || ans.second > n) {
		WA("find wrong diameter!");
	}
	if (dis(x, y) != dis(ans.first, ans.second)) {
		WA("find wrong diameter!");
	}
}
}  // namespace
bool in(int x, int y, int z) {
	if (x < 1 || x > n) WA("ask2 format error");
	if (y < 1 || y > n) WA("ask2 format error");
	if (z < 1 || z > n) WA("ask2 format error");
	++cntq2;
	if (cntq2 > 2) {
		WA("too many ask2");
	}
	int cnt = 0;
	if (pos[y] >= l[x] && pos[y] <= r[x]) ++cnt;
	if (pos[z] >= l[x] && pos[z] <= r[x]) ++cnt;
	if (cnt == 1) return 1;
	return LCA(y, z) == x;
}

int query(int x, int y, int z) {
	if (x == y || y == z || x == z) WA("ask1 format error");
	if (x < 1 || x > n) WA("ask1 format error");
	if (y < 1 || y > n) WA("ask1 format error");
	if (z < 1 || z > n) WA("ask1 format error");
	++cntq1;
	if (cntq1 > 300000) {
		WA("too many ask1");
	}
	return dis(x, y) + dis(x, z) + dis(y, z);
}
int main() {
	int T;
	scanf("%d%d", &subid, &T);
	while (T--) solve();
	puts("correct");
}
