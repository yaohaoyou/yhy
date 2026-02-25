---
title: 'P8180 「EZEC-11」Unmemorable 题解'
date: 2024-11-01 16:30:39
tags: [题解,洛谷月赛,线段树]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P8180)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/P8180-solution/)

## 前言

赛时会了，结果预处理忘优化了，大样例跑得飞快，$O(n^2)$ 假完~~甲烷~~了，喜提暴力分。

## 题意

自己看题面。

## 做法

先大眼暴力，观察结论（我也不会证明，但把表打出来后还比较明显）：

1. $r$ 数组无用
2. 顺序正确的 $l$ 数组唯一
3. 先从大到小排序，对于当前值 $i$，放入第一个 $l_j=0$ 的位置，$j>i$。形成最后的 $l$。

对于第 $3$ 点的观察，可以自己参考别的题解的做法，反正能确定 $l$ 数组即可。

现在已经得到了 $l$ 数组了，$r$ 数组已经固定，有保证有解，所以算出多少个排列 $p$ 满足 $l$ 的限制即可。

其实做到这一步，就完全是[这题](https://www.luogu.com.cn/problem/AT_arc186_b)了，接下来讲一讲具体的做法。

对于当前数组能推出的信息很少，所以先从局部推结论。不难发现在当前 $l$ 数组中 $p$ 最小的位置一定是当前最后一个 $l_i=0$ 的 $i$，证明可以设 $a_k=\min_{i=1}^na_i$，因为是最小值，所以前面不会再有 $p_k<p_i$，故 $l_k$ 一定是 $0$，最后一个 $l_k=0$ 一定会满足前面的 $\forall l_j=0,p_k<p_j$。

推出当前序列的最小值后，序列就又分成了两个独立的区间，因为保证有解，所以 $\forall j>k,p_j\ge k$，将 $i \in [k+1,n]$ 的 $l_i \gets l_i-k$ 后，后面的部分就与前面独立了。接下来就类似于分治的做法，将当前区间分成两段，递归求解。设当前区间为 $[L,R]$，这个区间的最小值已经确定，从剩下的 $R-L$ 个数中选取 $k-L$ 个数作为左边区间，剩下就是右边区间，所以要再乘上 $\binom{R-L}{k-L}$。形式化的，设 $f(L,R)$ 为区间 $[L,R]$ 的分配方案数（数的集合已经固定，相当于离散化后的方案数）。
$$
f(L,R)=\begin{cases}
1 & L>R \\
f(L,k-1)\times f(k+1,R) \times \binom{R-L}{k-L} & L<=R
\end{cases}
$$
想到这里就完成了，实现并不难。注意 $l_k$ 是区间最小值，但并不一定是 $mid$，所以直接做不是 $O(n\times\log_2n)$ 的，而是卡不满的 $O(n^2)$。可以使用 st 表或线段树做 rmq。本题空间要求线性，于是只能使用线段树，复杂度为 $O(n\times \log_2n)$。

## Code

递归求 $f$ 的主要代码如下：

```c
void dfs(int l,int r){
    if(l>r)    return;
    int x=-query(all,l,r).se;  // 区间最小值的位置
    mmul(ans,C(r-l,x-l));
    dfs(l,x-1);
    dfs(x+1,r);
}
```

[完整代码](https://www.luogu.com.cn/paste/nea3m78u)