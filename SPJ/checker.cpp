#include "testlib.h"

constexpr int lim = 1e9;

template <class T> void make_unique(std::vector<T> &vec) {
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	int n = inf.readInt();
	int pa = ouf.readInt(-1, 3 * n), ja = ans.readInt();
	if (pa != ja) quitf(_wa, "Your answer is wrong :(");
	if (pa != -1) {
		std::vector<std::tuple<int, int, int>> l(n);
		std::vector<int> s(n * 3);
		for (int i = 0; i < n; i++) {
			int a = ouf.readInt(-lim, lim), b = ouf.readInt(-lim, lim), c = ouf.readInt(-lim, lim);
			if (a == 0 && b == 0) quitf(_wa, "Not a line :(");
			if (a != 0 && b != 0) quitf(_wa, "One line is not parallel to one of the coordinate axis :(");
			int g = std::__gcd(std::__gcd(std::abs(a), std::abs(b)), std::abs(c));
			if (a < 0 || b < 0) g = -g;
			l[i] = {a / g, b / g, c / g};
			s[i * 3] = a, s[i * 3 + 1] = b, s[i * 3 + 2] = c;
		}
		int m = inf.readInt();
		while (m--) {
			int op = inf.readInt(), u = inf.readInt() - 1, v = inf.readInt() - 1;
			int type_u = std::get<0>(l[u]) == 0, type_v = std::get<0>(l[v]) == 0;
			if (op != (type_u ^ type_v)) quitf(_wa, "Not meeting the restrictions :(");
		}
		make_unique(l);
		if (l.size() != n) quitf(_wa, "Two lines are same :(");
		make_unique(s);
		if (s.size() != pa) quitf(_wa, "Your answer is not equal to the size of set S :(");
	}
	quitf(_ok, "Your answer is right :)");
}