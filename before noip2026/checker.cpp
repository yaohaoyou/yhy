#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
using u64 = uint64_t;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    const int n = inf.readInt(1, INT_MAX, "n");
    const long long Q = inf.readLong(1LL, LLONG_MAX, "Q");

    // 题面要求操作次数 m 为正整数。
    const long long m = ouf.readLong(1LL, Q, "m");
    const size_t words = (static_cast<size_t>(n) + 63) / 64;

    // 直接检查选手构造，不需要读取标准答案文件。
    vector<vector<u64>> a;
    vector<u64> colMask;
    vector<unsigned char> rowUsed;
    try {
        a.assign(n, vector<u64>(words, 0));
        colMask.assign(words, 0);
        rowUsed.assign(n, 0);
    } catch (const bad_alloc&) {
        quitf(_fail, "Checker memory exhausted; review input limits.");
    }

    for (long long op = 0; op < m; ++op) {
        const int p = ouf.readInt(1, n, "p");
        const int q = ouf.readInt(1, n, "q");
        vector<int> rows;
        rows.reserve(p);

        for (int k = 0; k < p; ++k) {
            const int r = ouf.readInt(1, n, "r") - 1;
            if (rowUsed[r]) {
                quitf(_wa, "Operation %lld: duplicate row %d.", op + 1, r + 1);
            }
            rowUsed[r] = 1;
            rows.push_back(r);
        }

        fill(colMask.begin(), colMask.end(), u64{0});
        for (int k = 0; k < q; ++k) {
            const int c = ouf.readInt(1, n, "c") - 1;
            const size_t w = static_cast<size_t>(c) / 64;
            const u64 bit = u64{1} << (c % 64);
            if (colMask[w] & bit) {
                quitf(_wa, "Operation %lld: duplicate column %d.", op + 1, c + 1);
            }
            colMask[w] |= bit;

            // 下标从 0 开始：第 c 列的第 c、c+1 行必须保持为 0。
            // 操作只能置 1，不能恢复为 0，因此可以立即判错。
            if (rowUsed[c]) {
                quitf(_wa, "Operation %lld: forbidden cell (%d, %d) is set to 1.",
                      op + 1, c + 1, c + 1);
            }
            if (c + 1 < n && rowUsed[c + 1]) {
                quitf(_wa, "Operation %lld: forbidden cell (%d, %d) is set to 1.",
                      op + 1, c + 2, c + 1);
            }
        }

        for (int r : rows) {
            for (size_t w = 0; w < words; ++w) {
                a[r][w] |= colMask[w];
            }
            rowUsed[r] = 0;
        }
    }

    if (!ouf.seekEof()) {
        quitf(_wa, "Extra non-whitespace data after the operations.");
    }

    const unsigned tail = static_cast<unsigned>(n % 64);
    const u64 lastMask = tail == 0 ? ~u64{0} : (u64{1} << tail) - 1;
    for (int r = 0; r < n; ++r) {
        for (size_t w = 0; w < words; ++w) {
            u64 expected = (w + 1 == words) ? lastMask : ~u64{0};
            // 第 r 行必须为 0 的列是 r 和 r-1（若存在）。
            if (static_cast<size_t>(r) / 64 == w) {
                expected &= ~(u64{1} << (r % 64));
            }
            if (r > 0 && static_cast<size_t>(r - 1) / 64 == w) {
                expected &= ~(u64{1} << ((r - 1) % 64));
            }
            const u64 diff = a[r][w] ^ expected;
            if (diff != 0) {
                // diff 非零，逐位寻找最低的 1，不依赖 <bit>。
                unsigned offset = 0;
                u64 remaining = diff;
                while ((remaining & u64{1}) == 0) {
                    remaining >>= 1;
                    ++offset;
                }
                const size_t c = w * 64 + offset;
                quitf(_wa, "Final matrix is incorrect at (%d, %d).",
                      r + 1, static_cast<int>(c) + 1);
            }
        }
    }

    quitf(_ok, "Valid construction with %lld operations.", m);
}
  