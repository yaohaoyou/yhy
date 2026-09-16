#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

struct InputData {
    int n;
    std::vector<int> fixed_parent;
};

struct OutputData {
    int claimed;
    std::vector<int> parent;
};

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
private:
    std::vector<int> parent;
    std::vector<int> size;
};

static InputData readInput() {
    InputData input;
    input.n = inf.readInt();
    input.fixed_parent.assign(input.n + 1, 0);
    for (int i = 2; i <= input.n; ++i) input.fixed_parent[i] = inf.readInt();
    return input;
}

static OutputData readOutput(InStream& stream, int n, bool jury_side) {
    OutputData output;
    output.claimed = stream.readInt(0, n / 2, "matching size");
    output.parent.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) output.parent[i] = stream.readInt(1, n, format("parent[%d]", i));
    if (!stream.seekEof()) stream.quitf(jury_side ? _fail : _pe, "extra tokens after parent list");
    return output;
}

// The distributable checker deliberately uses a generic bipartite matcher.
static int genericBipartiteMatching(const std::vector<int>& parent) {
    const int n = static_cast<int>(parent.size()) - 1;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 2; i <= n; ++i) {
        graph[i].push_back(parent[i]);
        graph[parent[i]].push_back(i);
    }

    std::vector<int> color(n + 1, -1);
    std::queue<int> q;
    color[1] = 0;
    q.push(1);
    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        for (int v : graph[u]) if (color[v] == -1) {
            color[v] = color[u] ^ 1;
            q.push(v);
        }
    }

    std::vector<int> left;
    for (int i = 1; i <= n; ++i) if (color[i] == 0) left.push_back(i);
    std::vector<int> mate_left(n + 1, 0), mate_right(n + 1, 0), dist(n + 1, 0);
    const int inf_dist = n + 5;

    int shortest_augmenting_path = inf_dist;
    auto bfs = [&]() {
        std::queue<int> bfs_queue;
        shortest_augmenting_path = inf_dist;
        for (int u : left) {
            if (mate_left[u] == 0) {
                dist[u] = 0;
                bfs_queue.push(u);
            } else {
                dist[u] = inf_dist;
            }
        }
        while (!bfs_queue.empty()) {
            const int u = bfs_queue.front();
            bfs_queue.pop();
            if (dist[u] + 1 > shortest_augmenting_path) continue;
            for (int v : graph[u]) {
                const int next_left = mate_right[v];
                if (next_left == 0) {
                    shortest_augmenting_path = dist[u] + 1;
                } else if (dist[next_left] == inf_dist) {
                    dist[next_left] = dist[u] + 1;
                    bfs_queue.push(next_left);
                }
            }
        }
        return shortest_augmenting_path != inf_dist;
    };

    std::vector<int> next_edge(n + 1, 0);
    auto augment = [&](int start) {
        std::vector<int> stack;
        stack.push_back(start);
        while (!stack.empty()) {
            const int u = stack.back();
            bool advanced = false;
            while (next_edge[u] < static_cast<int>(graph[u].size())) {
                const int v = graph[u][next_edge[u]++];
                const int next_left = mate_right[v];
                if (next_left == 0 && dist[u] + 1 == shortest_augmenting_path) {
                    int new_right = v;
                    for (int at = static_cast<int>(stack.size()) - 1; at >= 0; --at) {
                        const int path_left = stack[at];
                        const int old_right = mate_left[path_left];
                        mate_left[path_left] = new_right;
                        mate_right[new_right] = path_left;
                        new_right = old_right;
                    }
                    return true;
                }
                if (next_left != 0 && dist[next_left] == dist[u] + 1) {
                    stack.push_back(next_left);
                    advanced = true;
                    break;
                }
            }
            if (advanced) continue;
            dist[u] = inf_dist;
            stack.pop_back();
        }
        return false;
    };

    int matching = 0;
    while (bfs()) {
        std::fill(next_edge.begin(), next_edge.end(), 0);
        for (int u : left) if (mate_left[u] == 0 && augment(u)) ++matching;
    }
    return matching;
}

static int validateAndScore(const InputData& input, const OutputData& output,
                            InStream& stream, bool jury_side) {
    auto reject = [&](const char* message, int vertex) {
        stream.quitf(jury_side ? _fail : _wa, message, vertex);
    };

    Dsu dsu(input.n);
    for (int i = 2; i <= input.n; ++i) {
        if (input.fixed_parent[i] != 0 && output.parent[i] != input.fixed_parent[i]) {
            reject("fixed parent of vertex %d was changed", i);
        }
        if (output.parent[i] == i) reject("vertex %d is its own parent", i);
        if (!dsu.unite(i, output.parent[i])) reject("parent relation contains a cycle at vertex %d", i);
    }
    for (int i = 1; i <= input.n; ++i) {
        if (dsu.find(i) != dsu.find(1)) reject("vertex %d is not connected to root 1", i);
    }

    const int actual = genericBipartiteMatching(output.parent);
    if (actual != output.claimed) {
        stream.quitf(jury_side ? _fail : _wa,
                     "claimed matching size %d, but completed tree has maximum matching %d",
                     output.claimed, actual);
    }
    return actual;
}

int main(int argc, char* argv[]) {
    setName("forest completion checker using generic matching");
    registerTestlibCmd(argc, argv);

    const InputData input = readInput();
    const OutputData jury = readOutput(ans, input.n, true);
    const int optimum = validateAndScore(input, jury, ans, true);
    const OutputData participant = readOutput(ouf, input.n, false);
    const int found = validateAndScore(input, participant, ouf, false);
    if (found != optimum) expectedButFound(_wa, optimum, found, "maximum matching size");
    quitf(_ok, "optimal matching size is %d", optimum);
}
