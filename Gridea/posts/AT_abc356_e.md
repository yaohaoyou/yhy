---
title: 'AT_abc356_e Max/Min'
date: 2024-06-04 19:05:49
tags: [题解,AtCoder,分块]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/AT_abc356_e)
### [更爽的阅读体验](https://yaohaoyou.github.io/post/AT_abc356_e)

### AT 1506
## 前言
赛时小丑以为写假了，遂写篇题解。

我不强，我不知道调和级数，但我会根号做法。

## 题意
求 $\sum_{i=1}^{N-1}\sum_{j=i+1}^{N}\left\lfloor\frac{\max(A_i,A_j)}{\min(A_i,A_j)}\right\rfloor$。

## 做法
显然可以先将 A 从小到大排序，然后答案就变成了 $\sum_{i=2}^{N}\sum_{j=1}^{i-1}\left\lfloor\frac{A_i}{A_j}\right\rfloor$。

然后这就是一个经典的整除分块。具体的，先枚举 $A_i$，那此时 $\left\lfloor\frac{A_i}{A_j}\right\rfloor$ 的答案只有 $O(\sqrt V)$ 种。对于当前的 $k=\left\lfloor\frac{A_i}{A_j}\right\rfloor$，可以求出 $\left\lfloor\frac{A_i}{A_{nxt}}\right\rfloor=k$ 的另一个边界 $nxt$，然后直接跳到 $nxt-1$ 即可。由于 $k$ 的取值只有 $O(\sqrt V)$ 种，找到 $nxt$ 的过程可以使用二分答案，于是复杂度就是 $O(n \times \sqrt V \times \log_2 n)$。

放个代码。赛时代码比较丑，二分答案就不要细看了。
### [Code](https://atcoder.jp/contests/abc356/submissions/54228754)

然而这样是需要在 2s 内跑 $4 \times 10^9$ 的。明显会 TLE。思考如何优化。

发现整除分块不好优化，所以尝试将 $\log_2n$ 优化掉。发现二分答案的值域只有 $O(V)$，所以可以开一个数组提前预处理。时间复杂度为 $O(n \times \sqrt V + V \times \log_2 n)$。

### [AC Code](https://atcoder.jp/contests/abc356/submissions/54227955)


## 总结
时间复杂度为 $O(n\times \sqrt V+V \times \log_2 n)$，相比其他做法的却劣了不少，需要 1600ms+。

赛时真是小丑，同时感谢 \_maojun\_。