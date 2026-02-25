---
title: 'P10716 【MX-X1-T4】「KDOI-05」简单的字符串问题 题解'
date: 2025-02-08 16:52:00
tags: [题解,字符串]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P10716)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p10716-solution/)

## 做法 

前面的部分都和其他题解一样，先建出失配树，将问题转化成寻找有多少个点 $u(u>0)$ 满足在 $u$ 的子树中编号跳 $k-1$ 次后到达的节点 $p$ 满足 $p\le i$。

先使用启发式合并动态维护 $u$ 子树内的每个节点构成的集合，然后在这个集合中暴力跳，并储存 $dp_{u,i}$ 表示 $u$ 跳 $i$ 步后到达的节点。因为每次会从 $p$ 跳到至少为 $p+u$ 的节点，所以复杂度为 $\mathcal O(n+\frac n2+\frac n3+\dots)=\mathcal O(n\times \ln n)$。

接下来的处理询问。对于询问 $(x,k)$ 即求有多少个 $x$ 的祖先 $u$ 满足 $dp_{u,k-1}\le x$。

将询问离线下来，跑 dfs 的时候模拟栈就能直接记录从当前点到跟的路径上的信息，开 $n$ 个数据结构，第 $i$ 个维护当前链上的节点跳 $i$ 步后到达的节点的集合，需要支持增删，求排名。这里使用平衡树，应该也可以使用主席树。

总复杂度为 $O((n+q)\times \ln n \times \log_2n)$。

[AC Code](https://www.luogu.com.cn/paste/hkdq4nl6)