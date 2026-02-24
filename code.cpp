#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

struct Group {
    vector<tuple<int, int, int>> triples;
    int max_b = 0;
    int max_c = 0;

    void add(int a, int b, int c) {
        triples.emplace_back(a, b, c);
        if (b > max_b) {
            max_b = b;
            max_c = c;
        } else if (b == max_b) {
            max_c = max(max_c, c);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    vector<Group> groups(256);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            int high = (a >> 8) & 0xFF;
            groups[high].add(a, b, c);
        } else {
            int x;
            cin >> x;
            int h_x_high = (x >> 8) & 0xFF;
            int x_low = x & 0xFF;
            int current_max = 0;

            for (int k = 255; k >= 0; --k) {
                int h_a = h_x_high ^ k;
                auto& group = groups[h_a];
                if (group.triples.empty()) continue;

                // 计算该分组的可能上界
                int upper_bound = k * 256 * group.max_b + 255 * group.max_b + group.max_c;
                if (upper_bound <= current_max) continue;

                // 遍历该分组中的元素，计算实际贡献
                for (const auto& [a_val, b_val, c_val] : group.triples) {
                    int a_low = a_val & 0xFF;
                    int xor_low = a_low ^ x_low;
                    int value = (k * 256 + xor_low) * b_val + c_val;
                    if (value > current_max) {
                        current_max = value;
                    }
                }
            }

            cout << current_max << '\n';
        }
    }

    return 0;
}