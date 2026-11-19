// 区间带权严格上升子序列：论文的可持久化包络实现。
// 编译：g++ -O2 -pipe -std=c++20 interval_weighted_lis.cpp -o interval_lis
// 代码也只使用了 C++14 已支持的语言特性。
//
// 输入：
// n q
// a[1] ... a[n]
// w[1] ... w[n]
// 接下来 q 行：type l r，使用 1-based 闭区间 [l,r]。
// type=1：输出最大权重和。
// type=2：输出 最大权重和 元素个数 下标1 下标2 ...。
// w[i] 必须为正整数，所有 w[i] 的总和不能超过 long long 上限。
// 若只需要普通 LIS，把所有 w[i] 设为 1。
//
// 类接口使用 0-based 半开区间 [l,r)，并允许空区间。
// 预处理时间/空间 O(n log^2 n)，查询值 O(log n)，输出方案 O(k+log n)。
// 注意：持久化节点常数不小，请依据题目的 n 和内存限制评估。

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

class RangeWeightedLIS {
public:
    using Weight = long long;

    struct Result {
        Weight value = 0;
        std::vector<int> indices;  // 原数组下标，0-based。
    };

private:
    // 0 号句柄表示空序列。
    // left < 0：单个原数组位置 -left-1；否则是两个非空片段的拼接。
    struct Witness {
        Weight weight;
        int left, right;
    };

    // 表示某个左端点区间上的函数。
    // suffix 是统一追加的方案后缀，其权重也是加法懒标记。
    struct Node {
        Weight last;              // 当前区间最右端的函数值，包含本层懒标记。
        int left, right, suffix;
    };

    int n_ = 0;
    int zero_root_ = 0;
    std::vector<Node> nodes_;
    std::vector<Witness> witnesses_;
    std::vector<int> outer_;       // 普通值域线段树，每个节点存内层树根。
    std::vector<int> roots_;       // roots_[r] 表示所有终点位于 [0,r) 的包络。

    int new_node(Node x) {
        if (nodes_.size() >= static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("too many persistent function nodes");
        nodes_.push_back(x);
        return static_cast<int>(nodes_.size()) - 1;
    }

    int new_witness(Witness x) {
        if (witnesses_.size() >= static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("too many witness nodes");
        witnesses_.push_back(x);
        return static_cast<int>(witnesses_.size()) - 1;
    }

    int singleton(int i, Weight w) {
        return new_witness(Witness{w, -i - 1, 0});
    }

    int concatenate(int u, int v) {
        if (u == 0) return v;
        if (v == 0) return u;
        return new_witness(Witness{
            witnesses_[u].weight + witnesses_[v].weight, u, v
        });
    }

    int join(int left, int right) {
        return new_node(Node{nodes_[right].last, left, right, 0});
    }

    int build_zero(int b, int e) {
        if (e - b == 1) return new_node(Node{0, 0, 0, 0});
        const int m = b + (e - b) / 2;
        const int left = build_zero(b, m);
        const int right = build_zero(m, e);
        return join(left, right);
    }

    // 在 t 表示的所有坐标处，给方案追加片段 v。只复制根，不修改旧节点。
    int append(int t, int v) {
        if (v == 0) return t;
        Node x = nodes_[t];  // 必须按值复制，不能跨 vector 扩容保留引用。
        x.suffix = concatenate(x.suffix, v);
        x.last += witnesses_[v].weight;
        return new_node(x);
    }

    // 取得已包含父节点后缀的左右限制函数；不原地 pushdown。
    std::pair<int, int> children(int t) {
        const Node x = nodes_[t];
        const int left = append(x.left, x.suffix);
        const int right = append(x.right, x.suffix);
        return std::make_pair(left, right);
    }

    // 在坐标 [0,c) 处追加片段 v。当前节点对应 [b,e)。
    int prefix_append(int t, int b, int e, int c, int v) {
        if (c <= b) return t;
        if (e <= c) return append(t, v);
        const int m = b + (e - b) / 2;
        const auto ch = children(t);
        if (c <= m) {
            const int left = prefix_append(ch.first, b, m, c, v);
            return join(left, ch.second);
        }
        const int left = append(ch.first, v);
        const int right = prefix_append(ch.second, m, e, c, v);
        return join(left, right);
    }

    // 前提：g(l)>f(l) 的位置构成 [b,e) 的一个前缀。
    // 平局取 f。每层只递归一个儿子，所以是 O(log n)，不是一般线段树合并。
    int merge(int f, int g, int b, int e) {
        if (f == g) return f;
        // 最右端仍严格占优，则 g 在整个区间占优。
        if (nodes_[g].last > nodes_[f].last) return g;
        if (e - b == 1) return f;

        const int m = b + (e - b) / 2;
        const auto fc = children(f);
        const auto gc = children(g);
        if (nodes_[gc.first].last > nodes_[fc.first].last) {
            const int right = merge(fc.second, gc.second, m, e);
            return join(gc.first, right);
        }
        const int left = merge(fc.first, gc.first, b, m);
        return join(left, fc.second);
    }

    // f 的候选终点值全部小于 g 的候选终点值。不能交换调用顺序！
    int merge_roots(int f, int g) {
        if (f == zero_root_) return g;
        if (g == zero_root_) return f;
        return merge(f, g, 0, n_);
    }

    // 外层查询值域 [0,c) 的包络，按值从小到大合并。
    int outer_prefix(int v, int b, int e, int c) {
        if (c <= b) return zero_root_;
        if (e <= c) return outer_[v];
        const int m = b + (e - b) / 2;
        if (c <= m) return outer_prefix(v * 2, b, m, c);
        const int right = outer_prefix(v * 2 + 1, m, e, c);
        return merge_roots(outer_[v * 2], right);
    }

    void outer_set(int v, int b, int e, int pos, int root) {
        if (e - b == 1) {
            outer_[v] = root;
            return;
        }
        const int m = b + (e - b) / 2;
        if (pos < m) outer_set(v * 2, b, m, pos, root);
        else outer_set(v * 2 + 1, m, e, pos, root);
        outer_[v] = merge_roots(outer_[v * 2], outer_[v * 2 + 1]);
    }

public:
    RangeWeightedLIS(const std::vector<Weight>& a, const std::vector<Weight>& w) {
        if (a.size() != w.size())
            throw std::invalid_argument("a and w must have the same size");
        if (a.size() > static_cast<std::size_t>((std::numeric_limits<int>::max() - 8) / 4))
            throw std::length_error("input is too large for int node indices");

        Weight sum = 0;
        for (Weight x : w) {
            if (x <= 0) throw std::invalid_argument("weights must be positive");
            if (x > std::numeric_limits<Weight>::max() - sum)
                throw std::overflow_error("sum of weights exceeds long long");
            sum += x;
        }

        n_ = static_cast<int>(a.size());
        nodes_.reserve(static_cast<std::size_t>(n_) * 2 + 1);
        witnesses_.reserve(static_cast<std::size_t>(n_) + 1);
        nodes_.push_back(Node{0, 0, 0, 0});
        witnesses_.push_back(Witness{0, 0, 0});
        roots_.assign(static_cast<std::size_t>(n_) + 1, 0);
        if (n_ == 0) return;

        // 按 (a[i], -i) 排序成互异排名，保持原数组中的严格上升关系。
        std::vector<int> order(n_), rank(n_);
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [&](int i, int j) {
            if (a[i] != a[j]) return a[i] < a[j];
            return i > j;
        });
        for (int r = 0; r < n_; ++r) rank[order[r]] = r;

        zero_root_ = build_zero(0, n_);
        outer_.assign(static_cast<std::size_t>(n_) * 4 + 8, zero_root_);
        roots_[0] = zero_root_;
        for (int i = 0; i < n_; ++i) {
            const int predecessor = outer_prefix(1, 0, n_, rank[i]);
            const int leaf = singleton(i, w[i]);
            const int endpoint = prefix_append(predecessor, 0, n_, i + 1, leaf);
            outer_set(1, 0, n_, rank[i], endpoint);
            roots_[i + 1] = outer_[1];
        }
    }

    // 0-based 半开区间。need_sequence=false 时不展开方案。
    Result query(int l, int r, bool need_sequence = false) const {
        if (l < 0 || l > r || r > n_)
            throw std::out_of_range("query interval must satisfy 0 <= l <= r <= n");
        Result answer;
        if (l == r) return answer;

        std::vector<int> stack;
        int t = roots_[r], b = 0, e = n_;
        while (true) {
            const Node& x = nodes_[t];
            answer.value += witnesses_[x.suffix].weight;
            if (need_sequence && x.suffix != 0) stack.push_back(x.suffix);
            if (e - b == 1) break;
            const int m = b + (e - b) / 2;
            if (l < m) {
                t = x.left;
                e = m;
            } else {
                t = x.right;
                b = m;
            }
        }

        // 根到叶收集的是 S0,S1,...,Sh；正确输出顺序是 Sh,...,S1,S0。
        // 直接利用栈逆序展开，拼接节点先访问左儿子。
        // 用迭代遍历，避免很长的拼接链导致递归爆栈。
        while (!stack.empty()) {
            const int id = stack.back();
            stack.pop_back();
            const Witness& x = witnesses_[id];
            if (x.left < 0) {
                answer.indices.push_back(-x.left - 1);
            } else {
                stack.push_back(x.right);
                stack.push_back(x.left);
            }
        }
        return answer;
    }

    // 用于估算当前节点量；不包含 vector 的预留容量。
    std::pair<std::size_t, std::size_t> node_counts() const {
        return std::make_pair(nodes_.size() - 1, witnesses_.size() - 1);
    }
};

#ifndef RANGE_WEIGHTED_LIS_NO_MAIN
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    try {
        int n, q;
        if (!(std::cin >> n >> q)) return 0;
        if (n <= 0 || q < 0) throw std::invalid_argument("require n >= 1 and q >= 0");
        std::vector<long long> a(n), w(n);
        for (auto& x : a)
            if (!(std::cin >> x)) throw std::invalid_argument("invalid value input");
        for (auto& x : w) x=1;

        const RangeWeightedLIS solver(a, w);
        while (q--) {
            int type=1, l, r;
            if (!(std::cin >> l >> r))
                throw std::invalid_argument("invalid query input");
            if ((type != 1 && type != 2) || l < 1 || l > r || r > n)
                throw std::invalid_argument("require type in {1,2} and 1 <= l <= r <= n");
            const auto answer = solver.query(l - 1, r, type == 2);
            std::cout << answer.value;
            if (type == 2) {
                std::cout << ' ' << answer.indices.size();
                for (int i : answer.indices) std::cout << ' ' << i + 1;
            }
            std::cout << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
#endif