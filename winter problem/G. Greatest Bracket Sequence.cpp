#include <bits/stdc++.h>
using namespace std;

bool isBalanced(const string& s) {
    int bal = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else bal--;
        if (bal < 0) return false;
    }
    return bal == 0;
}

int longestValid(const string& s) {
    stack<int> st;
    st.push(-1);
    int maxLen = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (!st.empty()) {
                maxLen = max(maxLen, i - st.top());
            } else {
                st.push(i);
            }
        }
    }
    return maxLen;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    
    while (Q--) {
        int L, R;
        cin >> L >> R;
        L--; R--;
        
        string X = S.substr(L, R - L + 1);
        int n = X.size();
        
        // 判断是否无限
        int total = count(X.begin(), X.end(), '(') - count(X.begin(), X.end(), ')');
        bool infinite = false;
        
        if (total == 0) {
            // 检查所有循环移位
            string temp = X + X;  // 方便取循环移位
            for (int start = 0; start < n; start++) {
                string candidate = temp.substr(start, n);
                if (isBalanced(candidate)) {
                    infinite = true;
                    break;
                }
            }
        }
        
        if (infinite) {
            cout << "-1\n";
            continue;
        }
        
        // 有限情况：重复足够多次
        int repeat = n * 10;  // 可以调整
        string longStr;
        longStr.reserve(n * repeat);
        for (int i = 0; i < repeat; i++) {
            longStr += X;
        }
        
        int ans = longestValid(longStr);
        cout << ans << "\n";
    }
    
    return 0;
}