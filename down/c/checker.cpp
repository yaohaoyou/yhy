#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

string to_lower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

int lis_length(const vector<int>& seq) {
	int n = (int)seq.size(), maxx = 0;
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
    	f[i]=1;
    	for (int j = 0; j < i; j++) if(seq[j] < seq[i]) f[i] = max(f[i], f[j]+1);
    	maxx = max(maxx, f[i]);
	}
	return maxx;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // 读取输入数据
    int n = inf.readInt();
    int m = inf.readInt();
    int k = inf.readInt();
    vector<int> a(n);
    vector<int> pos(n + 1);          // 记录每个值在排列中的位置（1-based 值）
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(1, n);
        pos[a[i]] = i;                // 0-based 位置
    }

    // 读取答案文件第一行
    string ans_first = ans.readWord();
    if (ans_first != "Yes" && ans_first != "No") {
        quitf(_fail, "Answer file first line must be Yes or No");
    }

    // 读取选手输出第一行
    string out_first = ouf.readWord();
    if (out_first != "Yes" && out_first != "No") {
        quitf(_wa, "First line must be Yes or No");
    }

    // 答案说无解
    if (ans_first == "No") {
        if (out_first != "No") {
            quitf(_wa, "Expected No, but found Yes");
        }
        // 检查选手输出是否有多余内容
        if (!ouf.seekEof()) {
            quitf(_wa, "Extra tokens after No");
        }
        quitf(_ok, "No solution");
    }

    // 答案说有解，选手必须输出 Yes
    if (out_first != "Yes") {
        quitf(_wa, "Expected Yes, but found No");
    }

    // 读取选手输出的 m 个数
    vector<int> b;
    for (int i = 0; i < m; ++i) {
        int x = ouf.readInt(1, n, format("b[%d]", i + 1).c_str());
        b.push_back(x);
    }

    // 检查是否有多余内容
    if (!ouf.seekEof()) {
        quitf(_wa, "Extra tokens after subsequence");
    }

    // 验证是否构成原排列的子序列（位置严格递增）
    int prev_pos = -1;
    for (int i = 0; i < m; ++i) {
        int val = b[i];
        int cur_pos = pos[val];
        if (cur_pos <= prev_pos) {
            quitf(_wa, "Not a subsequence: value %d at position %d appears before previous value %d at position %d",
                  val, cur_pos, b[i-1], prev_pos);
        }
        prev_pos = cur_pos;
    }

    // 计算子序列的 LIS 长度
    int lis = lis_length(b);
    if (lis != k) {
        quitf(_wa, "LIS length of subsequence is %d, but expected %d", lis, k);
    }

    quitf(_ok, "Valid subsequence with LIS = %d", k);
}
