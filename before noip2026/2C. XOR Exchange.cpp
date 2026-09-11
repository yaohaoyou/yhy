#include <bits/stdc++.h>
using namespace std;

int N, Q, K;
vector<long long> A, sumTree, bitData;
vector<int> layerOffset;

int getBitOffset(int idx, int len, int h) {
    int base = N / len;
    int pos = idx - base;
    return layerOffset[h] + pos * h;
}

void build(int idx, int l, int r) {
    if (r - l == 1) {
        sumTree[idx] = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2, l, mid);
    build(idx * 2 + 1, mid, r);

    sumTree[idx] = sumTree[idx * 2] + sumTree[idx * 2 + 1];

    int len = r - l;
    int h = __builtin_ctz(len);
    int offset = getBitOffset(idx, len, h);

    int leftLen = len / 2;
    int leftH = h - 1;
    int leftOffset = getBitOffset(idx * 2, leftLen, leftH);
    int rightOffset = getBitOffset(idx * 2 + 1, leftLen, leftH);

    for (int b = 0; b < h - 1; ++b) {
        bitData[offset + b] = bitData[leftOffset + b] + bitData[rightOffset + b];
    }
    bitData[offset + h - 1] = sumTree[idx * 2 + 1];
}

void query(int idx, int l, int r, int ql, int qr, long long S, int L, int type, long long &ans) {
    if (ql <= l && r <= qr) {
        int len = r - l;
        int h = __builtin_ctz(len);
        long long m = S & (len - 1);
        long long j_start = ((l ^ S) >> h) << h;
        int j_idx = (N >> h) + (j_start >> h);
        long long sum_j = sumTree[j_idx];

        if (type == 2) {
            ans += sum_j;
        } else {
            int jOffset = getBitOffset(j_idx, len, h);
            long long xorWeighted = 0;
            for (int b = 0; b < h; ++b) {
                long long bitSum = bitData[jOffset + b];
                if (m & (1LL << b)) {
                    xorWeighted += (1LL << b) * (sum_j - bitSum);
                } else {
                    xorWeighted += (1LL << b) * bitSum;
                }
            }
            long long sum_i = 1LL * l * sum_j + xorWeighted;
            ans += sum_i + 1LL * (1 - L) * sum_j;
        }
        return;
    }

    int mid = (l + r) / 2;
    if (ql < mid) query(idx * 2, l, mid, ql, qr, S, L, type, ans);
    if (qr > mid) query(idx * 2 + 1, mid, r, ql, qr, S, L, type, ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    A.resize(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    K = __builtin_ctz(N);
    sumTree.assign(2 * N, 0);

    layerOffset.assign(K + 2, 0);
    for (int h = 0; h <= K; ++h) {
        int len = 1 << h;
        int nodes = N / len;
        layerOffset[h + 1] = layerOffset[h] + nodes * h;
    }
    bitData.assign(layerOffset[K + 1], 0);

    build(1, 0, N);

    long long S = 0;
    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int X;
            cin >> X;
            S ^= X;
        } else {
            int L, R;
            cin >> L >> R;
            long long ans = 0;
            query(1, 0, N, L, R + 1, S, L, type, ans);
            cout << ans << '\n';
        }
    }
    return 0;
}