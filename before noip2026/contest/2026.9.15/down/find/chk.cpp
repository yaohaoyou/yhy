#include<bits/stdc++.h>
#include "testlib.h"


struct Graph {
    int n = 0;
    std::vector<std::pair<int, int>> edges;
    std::unordered_set<std::uint64_t> edgeSet;
};

struct Witness {
    std::vector<int> path;
    std::vector<int> a;
    std::vector<int> b;
};

static std::uint64_t edgeKey(int u, int v) {
    if (u > v) std::swap(u, v);
    return (static_cast<std::uint64_t>(u) << 32) |
           static_cast<std::uint32_t>(v);
}

static Graph readGraph() {
    Graph graph;
    graph.n = inf.readInt();
    const int m = inf.readInt();
    graph.edges.reserve(m);
    graph.edgeSet.reserve(static_cast<std::size_t>(m) * 2 + 1);
    for (int i = 0; i < m; ++i) {
        const int u = inf.readInt();
        const int v = inf.readInt();
        graph.edges.push_back({u, v});
        graph.edgeSet.insert(edgeKey(u, v));
    }
    return graph;
}

static Witness readWitness(InStream& stream, int n, TResult invalidVerdict) {
    const int p = stream.readInt(1, n, "p");
    const int s = stream.readInt(0, n / 2, "s");
    if (p + 2 * s != n) {
        stream.quitf(invalidVerdict,
                     "p + 2*s must equal c, found p=%d, s=%d, c=%d", p, s, n);
    }

    Witness witness;
    witness.path.reserve(p);
    witness.a.reserve(s);
    witness.b.reserve(s);
    for (int i = 0; i < p; ++i) {
        witness.path.push_back(stream.readInt(1, n, "path_vertex"));
    }
    for (int i = 0; i < s; ++i) {
        witness.a.push_back(stream.readInt(1, n, "a_vertex"));
    }
    for (int i = 0; i < s; ++i) {
        witness.b.push_back(stream.readInt(1, n, "b_vertex"));
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra non-whitespace tokens after the witness");
    }
    return witness;
}

static void validateWitness(const Graph& graph, const Witness& witness,
                            InStream& stream, TResult invalidVerdict) {
    std::vector<unsigned char> owner(graph.n + 1, 0);

    auto assign = [&](const std::vector<int>& vertices, unsigned char id,
                      const char* part) {
        for (int v : vertices) {
            if (owner[v] != 0) {
                stream.quitf(invalidVerdict,
                             "vertex %d appears more than once (while reading %s)", v,
                             part);
            }
            owner[v] = id;
        }
    };

    assign(witness.path, 1, "path");
    assign(witness.a, 2, "A");
    assign(witness.b, 3, "B");
    for (int v = 1; v <= graph.n; ++v) {
        if (owner[v] == 0) {
            stream.quitf(invalidVerdict, "vertex %d is missing from the partition", v);
        }
    }

    for (std::size_t i = 1; i < witness.path.size(); ++i) {
        const int u = witness.path[i - 1];
        const int v = witness.path[i];
        if (graph.edgeSet.find(edgeKey(u, v)) == graph.edgeSet.end()) {
            stream.quitf(invalidVerdict,
                         "path step %d-%d is not an edge of the input graph", u, v);
        }
    }

    for (const auto& edge : graph.edges) {
        const unsigned char left = owner[edge.first];
        const unsigned char right = owner[edge.second];
        if ((left == 2 && right == 3) || (left == 3 && right == 2)) {
            stream.quitf(invalidVerdict,
                         "edge %d-%d has one endpoint in A and one endpoint in B",
                         edge.first, edge.second);
        }
    }
}

int main(int argc, char* argv[]) {
    setName("validate a path and an equal anticomplete partition");
    registerTestlibCmd(argc, argv);

    const Graph graph = readGraph();

    const Witness jury = readWitness(ans, graph.n, _fail);
    validateWitness(graph, jury, ans, _fail);

    const Witness participant = readWitness(ouf, graph.n, _wa);
    validateWitness(graph, participant, ouf, _wa);

    quitf(_ok, "valid witness: p=%d, s=%d",
          static_cast<int>(participant.path.size()),
          static_cast<int>(participant.a.size()));
}
