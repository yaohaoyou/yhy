---
title: 'P16160 [ICPC 2016 NAIPC] Jewel Thief 题解'
date: 2026-07-15 19:45:00
tags: [题解]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P16160)

物体体积种类数更少的 01 背包。

考虑使用 $s$ 较小的性质。显然对于体积相同的物品价值从大到小取，所以可以将每种体积分开做 01 背包。令 $f_{i,j}$ 表示考虑前 $i$ 种体积，总体积为 $j$ 的最大价值，记录 $a_{i,j}$ 表示体积为 $i$ 的物品中价值前 $j$ 大的价值和，显然 $f(x)=a_{i,x}$ 是上凸函数。有转移：$f_{i,j}\gets f_{i-1,j-ik}+a_{i,k}$，将 $\bmod i$ 同余的取出来后，就是类似于 $g_{j}\gets g_{j-k}+a_k$ 的转移，因为 $a_k$ 为上凸函数，所以 $g$ 满足决策单调性。因为需要动态按顺序求 $g$ 来转移，可以使用 cdq 分治套决策单调性分治做到 $\mathcal O(ks\log^2n+n\log n)$，不太能通过，这里介绍一种**简化 LARSCH**算法。

简化 LARSCH 算法其实类似于 cdq 分治套决策单调性分治，令 $opt_t(x)$ 表示只考虑从 $[1,t]$ 的转移到 $x$ 的最优决策，$opt(x)=opt_{x-1}(x)$。具体过程是定义 $solve(l,r)$ 表示已知 $[1,l)$ 的 $g,opt$ 和 $opt_{l-1}(r)$，求解 $[1,r]$ 的 $g,opt$。

1. 用 $i\in [opt(l-1),opt_{l-1}(r)]$ 求出 $opt_{l-1}(mid)$，因为 $opt_{t}(x)\le opt_{t}(y)\le opt_{t}(z),x<y<z$。
2. 调用 $solve(l,mid)$。
3. 用 $opt(i),i\in [l,mid]$ 和 $opt_{l-1}(r)$ 求出 $opt_{mid}(r)$。
4. 调用 $solve(mid+1,r)$。

这样就做完了，复杂度为 $\mathcal O(ks\log n+n\log n)$。