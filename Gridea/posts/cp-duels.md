---
title: 'CP duels记录'
date: 2024-11-19 16:22:23
tags: [Codeforces,做题记录]
published: true
hideInList: false
feature: 
isTop: true
---
## [CF1368E Ski Accidents](https://www.luogu.com.cn/problem/CF1368E)

比较神的构造，被对手 10min 秒了。

看到 $\frac47$ 和 $out_i\le2$，然后就应该想到 $\frac47=\frac{2^2}{2^0+2^1+2^2}$，尝试将 $n$ 划分为 $3$ 个集合。感觉比较结论，所以直接说了。将 $n$ 划分成 $3$ 个无交且并为全集的集合 $A,B,C$，满足
$$
\forall a\in A,\{\forall u \rarr a,u\in C\}
$$
$$
\forall b\in B,\{\exist u \rarr b,u\in A\},\{\not\exist u\rarr b,u\in B\}
$$
$$
\forall c\in C,\{\exist u \rarr c,u\in B\}
$$
分类讨论一下，不难发现 $A,B,C$ 交且并为全集。由于 $\forall b\in B,\exist a \rarr b$，$|B|\le2|A|$，同理，$|B|\le2|C|$，即 $4|A|\ge2|B|\ge|C|$，$|C|\le\frac47n$。删除 $C$ 中的所有点后 $A$ 的入度都是 $0$，$B$ 的出度都是 $0$，故最多只有 $a\rarr b$ 的边，满足条件。

因为是 DAG，分集合时可以做拓扑排序。复杂度线性。

