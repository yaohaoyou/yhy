#include "testlib.h"

#include <string>
#include <vector>

struct Rect {
    long long r1, c1, r2, c2;
};

struct Output {
    bool reportsError;
    std::vector<int> match;
};

static bool parseIndex(const std::string& token, int n, int& value) {
    if (token.empty()) return false;
    long long x = 0;
    for (std::size_t i = 0; i < token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9') return false;
        x = x * 10 + token[i] - '0';
        if (x > n) return false;
    }
    if (x < 1 || x > n) return false;
    value = static_cast<int>(x);
    return true;
}

static Output readOutput(InStream& stream, int n, bool jurySide) {
    Output out;
    out.reportsError = false;
    const std::string first = stream.readToken();
    if (first == "syntax") {
        const std::string second = stream.readToken();
        if ((second != "error" && second != "error.") || !stream.seekEof()) {
            stream.quitf(jurySide ? _fail : _wa, "invalid 'syntax error' output");
        }
        out.reportsError = true;
        return out;
    }

    out.match.resize(n);
    if (!parseIndex(first, n, out.match[0])) {
        stream.quitf(jurySide ? _fail : _wa, "the first matching index is invalid");
    }
    for (int i = 1; i < n; ++i) {
        if (!parseIndex(stream.readToken(), n, out.match[i])) {
            stream.quitf(jurySide ? _fail : _wa, "matching index %d is invalid", i + 1);
        }
    }
    if (!stream.seekEof()) stream.quitf(jurySide ? _fail : _wa, "extra output");

    std::vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (++seen[out.match[i]] != 1) {
            stream.quitf(jurySide ? _fail : _wa, "matching is not a permutation");
        }
        --out.match[i];
    }
    return out;
}

static bool pairValid(const Rect& a, const Rect& b) {
    const bool disjoint = a.r2 < b.r1 || b.r2 < a.r1 || a.c2 < b.c1 || b.c2 < a.c1;
    const bool aContainsB = a.r1 < b.r1 && b.r2 < a.r2 && a.c1 < b.c1 && b.c2 < a.c2;
    const bool bContainsA = b.r1 < a.r1 && a.r2 < b.r2 && b.c1 < a.c1 && a.c2 < b.c2;
    return disjoint || aContainsB || bContainsA;
}

static bool valid(const std::vector<long long>& r1, const std::vector<long long>& c1,
                  const std::vector<long long>& r2, const std::vector<long long>& c2,
                  const std::vector<int>& match, std::string& why) {
    const int n = static_cast<int>(match.size());
    std::vector<Rect> rects(n);
    for (int i = 0; i < n; ++i) {
        const int j = match[i];
        rects[i] = Rect{r1[i], c1[i], r2[j], c2[j]};
        if (rects[i].r1 > rects[i].r2 || rects[i].c1 > rects[i].c2) {
            why = "a matched pair does not form a rectangle";
            return false;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (!pairValid(rects[i], rects[j])) {
                why = "two rectangles overlap illegally or their boundaries touch";
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    setName("rectangle matching reference checker (quadratic)");
    registerTestlibCmd(argc, argv);

    const int n = inf.readInt();
    std::vector<long long> r1(n), c1(n), r2(n), c2(n);
    for (int i = 0; i < n; ++i) {
        r1[i] = inf.readLong();
        c1[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        r2[i] = inf.readLong();
        c2[i] = inf.readLong();
    }

    const Output jury = readOutput(ans, n, true);
    const Output participant = readOutput(ouf, n, false);
    std::string why;
    if (!jury.reportsError && !valid(r1, c1, r2, c2, jury.match, why)) {
        quitf(_fail, "jury matching is invalid: %s", why.c_str());
    }
    if (participant.reportsError) {
        if (!jury.reportsError) quitf(_wa, "a valid matching exists");
        quitf(_ok, "both outputs report no solution");
    }
    why.clear();
    if (!valid(r1, c1, r2, c2, participant.match, why)) {
        quitf(_wa, "invalid matching: %s", why.c_str());
    }
    if (jury.reportsError) quitf(_fail, "jury answer incorrectly reports no solution");
    quitf(_ok, "valid matching");
}
