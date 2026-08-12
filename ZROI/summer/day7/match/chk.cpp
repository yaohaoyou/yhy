#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static int parseFirstIndex(const string& token, int upper, TResult verdict, int tc) {
    if (token.empty()) quitf(verdict, "test case %d: empty point index", tc);
    long long value = 0;
    for (char c : token) {
        if (c < '0' || c > '9')
            quitf(verdict, "test case %d: invalid point index token '%s'", tc, token.c_str());
        value = value * 10 + c - '0';
        if (value > upper)
            quitf(verdict, "test case %d: point index is greater than %d", tc, upper);
    }
    if (value < 1)
        quitf(verdict, "test case %d: point index must be positive", tc);
    return (int)value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int subtask = inf.readInt(1, 5, "subtask");
    int T = inf.readInt(1, 200000, "T");
    long long sumN = 0;

    for (int tc = 1; tc <= T; ++tc) {
        int n = inf.readInt(1, 200000, format("n[%d]", tc).c_str());
        int k = inf.readInt(0, n, format("k[%d]", tc).c_str());
        sumN += n;
        if (sumN > 200000)
            quitf(_fail, "input violates sum(n) <= 200000");

        vector<long long> x(2 * n), y(2 * n);
        for (int i = 0; i < 2 * n; ++i) {
            x[i] = inf.readLong(-1000000000LL, 1000000000LL,
                                format("x[%d][%d]", tc, i + 1).c_str());
            y[i] = inf.readLong(-1000000000LL, 1000000000LL,
                                format("y[%d][%d]", tc, i + 1).c_str());
        }

        // The jury output is used only to determine whether this case is feasible.
        string juryFirst = ans.readToken();
        bool juryHasSolution = juryFirst != "-1";
        if (juryHasSolution) {
            (void)parseFirstIndex(juryFirst, 2 * n, _fail, tc);
            for (int token = 1; token < 2 * n; ++token)
                (void)ans.readInt(1, 2 * n, format("jury token in case %d", tc).c_str());
        }

        string first = ouf.readToken();
        if (first == "-1") {
            if (juryHasSolution)
                quitf(_wa, "test case %d: a valid construction exists", tc);
            continue;
        }
        if (!juryHasSolution)
            quitf(_wa, "test case %d: jury says the instance is impossible", tc);

        vector<char> used(2 * n, false);
        int friendlyCount = 0;
        for (int row = 0; row < n; ++row) {
            int a = (row == 0
                         ? parseFirstIndex(first, 2 * n, _wa, tc)
                         : ouf.readInt(1, 2 * n, format("a[%d][%d]", tc, row + 1).c_str()));
            int b = ouf.readInt(1, 2 * n, format("b[%d][%d]", tc, row + 1).c_str());
            --a, --b;
            if (a == b)
                quitf(_wa, "test case %d, pair %d uses one point twice", tc, row + 1);
            if (used[a] || used[b])
                quitf(_wa, "test case %d, pair %d reuses a point", tc, row + 1);
            used[a] = used[b] = true;
            friendlyCount += (x[a] == x[b] || y[a] == y[b]);
        }

        if (subtask != 2 && friendlyCount != k)
            quitf(_wa, "test case %d has %d friendly pairs, expected %d",
                  tc, friendlyCount, k);
    }

    ouf.skipBlanks();
    if (!ouf.eof()) quitf(_pe, "extra output after all test cases");
    ans.skipBlanks();
    if (!ans.eof()) quitf(_fail, "extra tokens in jury output");

    quitf(_ok, "all %d test cases are correct", T);
}
