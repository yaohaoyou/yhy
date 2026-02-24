## [The 3rd Universal Cup. Stage 15: Chengdu](https://contest.ucup.ac/contest/1821)

### [L. Recover Statistics](https://contest.ucup.ac/contest/1821/problem/9546) by matt

签到中的签到。直接输出 $50$ 个 a，$45$ 个 b，$4$ 个 c，和 $1$ 个 inf.

### [B.Athlete Welcome Ceremony](https://contest.ucup.ac/contest/1821/problem/9536) by matt

设 $dp_{i,j,k,0/1/2}$ 表示前 $i$ 个中花钱购买了 $j$ 个 a，$k$ 个 b，$s_i-j-k$ 个 c，上一个位置是 $0/1/2$ 的方案数，$s_i$ 表示前 $i$ 个字符中 ``?`` 的个数。

不难写出 $O(n^3)$ 的 DP 转移。

最后给 dp 数组写一个三维前缀和（$O(n^3+q)$）或二维前缀和（$O(n^3+nq)$）预处理答案。