#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using i64 = long long;

i64 normalize(i64 x, i64 mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

struct Fenwick {
    int n;
    i64 mod;
    std::vector<i64> t;

    Fenwick(int n_, i64 mod_)
        : n(n_), mod(mod_), t(n_ + 1, 0) {}

    void add(int p, i64 x) {
        x = normalize(x, mod);

        for (; p <= n; p += p & -p) {
            t[p] += x;
            if (t[p] >= mod) t[p] -= mod;
        }
    }

    i64 sum(int p) const {
        i64 s = 0;

        for (; p > 0; p -= p & -p) {
            s += t[p];
            if (s >= mod) s -= mod;
        }

        return s;
    }

    i64 range(int l, int r) const {
        i64 result = sum(r) - sum(l - 1);
        if (result < 0) result += mod;
        return result;
    }
};

// 原树以输入的 R 为根，根的深度为 1。
// 原树遍历使用显式栈，递归只用于点分治。
class TreeFourOps {
    int n, lg, root;
    i64 answerMod, mod; // 输出模 P，内部模 2P。

    std::vector<std::vector<int>> g, up;
    std::vector<int> parent, depth, tin, tout, size;

    std::vector<bool> removed;
    std::vector<int> tempParent, tempSize;

    // centPath[x]：
    // 从点分树根到 x 的分治祖先，以及 x 到它们的原树距离。
    std::vector<std::vector<std::pair<int, int>>> centPath;

    // 分治块内的 b 之和、以重心为起点的带权距离和。
    std::vector<i64> mass, distanceSum;

    // 分支信息。
    // subDistanceSum[z] 的距离起点是 z 的分治父亲，不是 z。
    std::vector<i64> subMass, subDistanceSum;

    // 路径加部分：在 DFS 序上维护 b、depth*b。
    Fenwick diffSum, diffDepth;

    // 子树加部分：
    // 前两棵维护 C 的区间加、区间和；
    // 后一棵维护 E 的区间加、单点查询。
    Fenwick rangeDiff, rangeIndex, rangeDepth;

    i64 totalDiff = 0;
    i64 totalDepth = 0;

    void buildOriginalTree() {
        depth[root] = 1;

        std::vector<int> stack{root}, order;
        order.reserve(n);

        int timer = 0;

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();

            tin[v] = ++timer;
            order.push_back(v);

            for (int u : g[v]) {
                if (u == parent[v]) continue;

                parent[u] = v;
                depth[u] = depth[v] + 1;
                stack.push_back(u);
            }
        }

        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            int v = *it;

            size[v] += 1;

            if (parent[v])
                size[parent[v]] += size[v];

            tout[v] = tin[v] + size[v] - 1;
        }

        up[0] = parent;

        for (int j = 1; j < lg; ++j) {
            for (int v = 1; v <= n; ++v) {
                up[j][v] = up[j - 1][up[j - 1][v]];
            }
        }
    }

    void buildCentroid(int entry) {
        // 收集当前未被删除的连通块。
        std::vector<int> order{entry};
        tempParent[entry] = 0;

        for (std::size_t i = 0; i < order.size(); ++i) {
            int v = order[i];

            for (int u : g[v]) {
                if (removed[u] || u == tempParent[v]) continue;

                tempParent[u] = v;
                order.push_back(u);
            }
        }

        // 计算临时子树大小。
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            int v = *it;
            tempSize[v] = 1;

            for (int u : g[v]) {
                if (!removed[u] && tempParent[u] == v)
                    tempSize[v] += tempSize[u];
            }
        }

        // 寻找当前连通块的重心。
        int centroid = entry;
        int componentSize = static_cast<int>(order.size());

        for (int v : order) {
            int largest = componentSize - tempSize[v];

            for (int u : g[v]) {
                if (!removed[u] && tempParent[u] == v)
                    largest = std::max(largest, tempSize[u]);
            }

            if (largest <= componentSize / 2) {
                centroid = v;
                break;
            }
        }

        // 预存本分治层的距离。
        // 后续查询时不在每一层调用 LCA 求距离。
        struct Visit {
            int v, p, d;
        };

        std::vector<Visit> stack{{centroid, 0, 0}};

        while (!stack.empty()) {
            Visit item = stack.back();
            stack.pop_back();

            centPath[item.v].emplace_back(centroid, item.d);

            for (int u : g[item.v]) {
                if (removed[u] || u == item.p) continue;

                stack.push_back({u, item.v, item.d + 1});
            }
        }

        removed[centroid] = true;

        for (int u : g[centroid]) {
            if (!removed[u])
                buildCentroid(u);
        }
    }

    // 单点修改差分权值 b[x]。
    void addDifference(int x, i64 delta) {
        if (x == 0) return;

        delta = normalize(delta, mod);

        diffSum.add(tin[x], delta);
        diffDepth.add(tin[x], delta * depth[x]);

        totalDiff += delta;
        if (totalDiff >= mod) totalDiff -= mod;

        totalDepth = (totalDepth + delta * depth[x]) % mod;

        int last = 0;

        for (auto it = centPath[x].rbegin();
             it != centPath[x].rend(); ++it) {
            auto [c, d] = *it;

            mass[c] += delta;
            if (mass[c] >= mod) mass[c] -= mod;

            distanceSum[c] = (distanceSum[c] + delta * d) % mod;

            // last 标识 c 下方包含 x 的分支。
            // 此处距离必须到 c，而不是到 last。
            if (last) {
                subMass[last] += delta;
                if (subMass[last] >= mod) subMass[last] -= mod;

                subDistanceSum[last] =
                    (subDistanceSum[last] + delta * d) % mod;
            }

            last = c;
        }
    }

    // 查询所有点 t 的 b[t] * dist(x,t) 之和，模 2P。
    i64 queryDistance(int x) const {
        i64 result = 0;
        int last = 0;

        for (auto it = centPath[x].rbegin();
             it != centPath[x].rend(); ++it) {
            auto [c, d] = *it;

            result += distanceSum[c] + mass[c] * d;

            if (last) {
                result -= subDistanceSum[last] + subMass[last] * d;
            }

            result = normalize(result, mod);
            last = c;
        }

        return result;
    }

    // 根到 x 的路径点权和，模 P。
    i64 rootPrefix(int x) const {
        if (x == 0) return 0;

        // 路径加部分：
        // 分子在整数意义下是偶数。
        // 必须先模 2P，再整除 2，才能得到正确的模 P 结果。
        i64 numerator = normalize(
            depth[x] * totalDiff + totalDepth - queryDistance(x),
            mod
        );

        i64 fromPaths = numerator / 2;

        // 子树加部分：depth[x] * C[x] + E[x]。
        i64 fromSubtrees = (
            depth[x] * rangeDiff.sum(tin[x])
            + rangeDepth.sum(tin[x])
        ) % mod;

        return (fromPaths + fromSubtrees) % answerMod;
    }

    // C 在 DFS 序上前 k 项的和，模 2P。
    i64 subtreePartPrefix(int k) const {
        return normalize(
            k * rangeDiff.sum(k) - rangeIndex.sum(k),
            mod
        );
    }

public:
    TreeFourOps(
        std::vector<std::vector<int>> graph,
        const std::vector<i64>& a,
        int root_,
        i64 p
    )
        : n(static_cast<int>(graph.size()) - 1),
          lg(1),
          root(root_),
          answerMod(p),
          mod(2LL * p),
          g(std::move(graph)),
          parent(n + 1),
          depth(n + 1),
          tin(n + 1),
          tout(n + 1),
          size(n + 1),
          removed(n + 1, false),
          tempParent(n + 1),
          tempSize(n + 1),
          centPath(n + 1),
          mass(n + 1),
          distanceSum(n + 1),
          subMass(n + 1),
          subDistanceSum(n + 1),
          diffSum(n, mod),
          diffDepth(n, mod),
          rangeDiff(n, mod),
          rangeIndex(n, mod),
          rangeDepth(n, mod) {

        while ((1LL << lg) <= n) ++lg;
        up.assign(lg, std::vector<int>(n + 1));

        buildOriginalTree();
        buildCentroid(root);

        // 初始点权归入路径加部分。
        // b[v] = a[v] - 所有孩子的 a 之和。
        std::vector<i64> b = a;

        for (int v = 1; v <= n; ++v) {
            if (parent[v])
                b[parent[v]] -= a[v];
        }

        for (int v = 1; v <= n; ++v)
            addDifference(v, b[v]);
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v])
            std::swap(u, v);

        int d = depth[u] - depth[v];

        for (int j = 0; j < lg; ++j) {
            if ((d >> j) & 1)
                u = up[j][u];
        }

        if (u == v) return u;

        for (int j = lg - 1; j >= 0; --j) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return parent[u];
    }

    void addPath(int u, int v, i64 delta) {
        int w = lca(u, v);

        addDifference(u, delta);
        addDifference(v, delta);
        addDifference(w, -delta);
        addDifference(parent[w], -delta);
    }

    void addSubtree(int v, i64 delta) {
        delta = normalize(delta, mod);

        int l = tin[v], r = tout[v];

        // C 在区间 [l,r] 上加 delta。
        rangeDiff.add(l, delta);
        rangeDiff.add(r + 1, -delta);

        rangeIndex.add(l, delta * (l - 1));
        rangeIndex.add(r + 1, -delta * r);

        // E 在同一区间上加 delta * (1-depth[v])。
        rangeDepth.add(l, delta * (1 - depth[v]));
        rangeDepth.add(r + 1, -delta * (1 - depth[v]));
    }

    i64 queryPath(int u, int v) const {
        int w = lca(u, v);

        return normalize(
            rootPrefix(u) + rootPrefix(v)
            - rootPrefix(w) - rootPrefix(parent[w]),
            answerMod
        );
    }

    i64 querySubtree(int v) const {
        int l = tin[v], r = tout[v];

        i64 fromPaths =
            diffDepth.range(l, r)
            - (depth[v] - 1) * diffSum.range(l, r);

        i64 fromSubtrees =
            subtreePartPrefix(r) - subtreePartPrefix(l - 1);

        return normalize(fromPaths + fromSubtrees, answerMod);
    }
};

// P3384 输入格式：
// N M R P
// N 个初始点权
// N-1 条无向边
// M 个操作：
//
// 1 x y z：路径 x-y 点权加 z
// 2 x y  ：查询路径 x-y 点权和
// 3 x z  ：x 的子树点权加 z
// 4 x    ：查询 x 的子树点权和
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, root;
    i64 p;

    if (!(std::cin >> n >> q >> root >> p))
        return 0;

    std::vector<i64> a(n + 1);

    for (int v = 1; v <= n; ++v)
        std::cin >> a[v];

    std::vector<std::vector<int>> g(n + 1);

    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    TreeFourOps tree(std::move(g), a, root, p);

    while (q--) {
        int op, u, v;
        i64 delta;

        std::cin >> op >> u;

        if (op == 1) {
            std::cin >> v >> delta;
            tree.addPath(u, v, delta);
        } else if (op == 2) {
            std::cin >> v;
            std::cout << tree.queryPath(u, v) << '\n';
        } else if (op == 3) {
            std::cin >> delta;
            tree.addSubtree(u, delta);
        } else if (op == 4) {
            std::cout << tree.querySubtree(u) << '\n';
        }
    }

    return 0;
}