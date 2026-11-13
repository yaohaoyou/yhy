#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <utility>
#include <vector>
using namespace std;

int inspect(InStream& out, const map<pair<int,int>,int>& inventory, int n) {
    int k = out.readInt(0, n-1, "k");
    vector<pair<int,int>> p(n);
    auto remaining = inventory;
    for (int j = 0; j < n; ++j) {
        int a = out.readInt(-1000000000, 1000000000, "a");
        int b = out.readInt(a, 1000000000, "b");
        auto it = remaining.find({a,b});
        if (it == remaining.end()) out.quitf(_wa, "unknown or repeated interval");
        remaining.erase(it); p[j] = {a,b};
    }
    int width = max(1, int(sqrt(n))), blocks = (n + width - 1) / width;
    vector<int> minA(blocks, 1000000001), maxA(blocks, -1000000001), maxB(blocks, -1000000001);
    bool tight = (k == 0);
    for (int j = 0; j < n; ++j) {
        int here = j / width;
        for (int block = 0; block < here; ++block)
            if (maxA[block] > p[j].second) out.quitf(_wa, "wrong order of disjoint intervals");
        for (int i = here * width; i < j; ++i)
            if (p[i].first > p[j].second) out.quitf(_wa, "wrong order of disjoint intervals");
        // Pairs farther than the submitted bound must be disjoint.
        int end = j - k;
        if (end > 0) {
            int complete = end / width;
            for (int block = 0; block < complete; ++block) {
                if (maxB[block] < p[j].first || minA[block] > p[j].second) continue;
                for (int i = block * width; i < (block + 1) * width; ++i)
                    if (max(p[i].first, p[j].first) <= min(p[i].second, p[j].second))
                        out.quitf(_wa, "intersecting pair exceeds k");
            }
            for (int i = complete * width; i < end; ++i)
                if (max(p[i].first, p[j].first) <= min(p[i].second, p[j].second))
                    out.quitf(_wa, "intersecting pair exceeds k");
        }
        if (k > 0 && j >= k &&
            max(p[j-k].first, p[j].first) <= min(p[j-k].second, p[j].second)) tight = true;
        minA[here] = min(minA[here], p[j].first);
        maxA[here] = max(maxA[here], p[j].first);
        maxB[here] = max(maxB[here], p[j].second);
    }
    if (!tight) out.quitf(_wa, "no intersecting pair attains k");
    return k;
}
int main(int argc, char** argv) {
    setName("interval public pair-constraint checker");
    registerTestlibCmd(argc, argv);
    int T = inf.readInt(1, 200000, "T");
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        int n = inf.readInt(1, 200000, "n");
        map<pair<int,int>,int> inventory;
        for (int i = 0; i < n; ++i) {
            int a = inf.readInt(), b = inf.readInt(); inventory[{a,b}] = i;
        }
        if (int(inventory.size()) != n) quitf(_fail, "duplicate input intervals");
        int reference = inspect(ans, inventory, n), candidate = inspect(ouf, inventory, n);
        if (candidate < reference) quitf(_fail, "candidate improves the jury optimum");
        if (candidate > reference) quitf(_wa, "candidate is not optimal");
    }
    if (!ans.seekEof()) quitf(_fail, "extra jury tokens");
    if (!ouf.seekEof()) quitf(_wa, "extra contestant tokens");
    quitf(_ok, "all cases accepted");
}
