#include "testlib.h"
#include <algorithm>
using namespace std;

using i128 = __int128;

i128 abs128(i128 x) { return x < 0 ? -x : x; }
i128 gcd128(i128 a, i128 b) {
    while (b) { i128 t = b; b = a % b; a = t; }
    return a;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int Q = inf.readInt();
    for (int i = 1; i <= Q; ++i) {
        i128 x1 = inf.readInt(), y1 = inf.readInt();
        i128 x2 = inf.readInt(), y2 = inf.readInt();
        i128 x3 = inf.readInt(), y3 = inf.readInt();

        int x = ouf.readInt(), y = ouf.readInt();

        if (x == -1 && y == -1) {
            // 选手声称内部无整点，用 Pick 定理验证
            i128 cross = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
            i128 g1 = gcd128(abs128(x1 - x2), abs128(y1 - y2));
            i128 g2 = gcd128(abs128(x2 - x3), abs128(y2 - y3));
            i128 g3 = gcd128(abs128(x3 - x1), abs128(y3 - y1));
            if (cross - (g1 + g2 + g3) != -2)
                quitf(_wa, "triangle %d actually has interior lattice points", i);
        } else {
            // 选手输出了一个点，验证是否严格在三角形内部
            auto cross_product = [&](i128 xa, i128 ya, i128 xb, i128 yb,
                                     i128 xp, i128 yp) {
                return (xb - xa) * (yp - ya) - (yb - ya) * (xp - xa);
            };
            i128 c1 = cross_product(x1, y1, x2, y2, x, y);
            i128 c2 = cross_product(x2, y2, x3, y3, x, y);
            i128 c3 = cross_product(x3, y3, x1, y1, x, y);

            if (!(c1 > 0 && c2 > 0 && c3 > 0))
                quitf(_wa, "point (%d,%d) is not strictly inside triangle %d", x, y, i);
        }
    }
    // ouf.readEof();
    quitf(_ok, "all triangles passed");
}