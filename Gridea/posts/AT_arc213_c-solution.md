---
title: 'AT_arc213_c Double X 题解'
date: 2026-01-29 20:32:59
tags: [题解,线段树,网络流]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/AT_arc213_c)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/AT_arc213_c-solution/)

搬运官方题解做法。

显然 $x_1,x_2,x_3,x_4$ 满足在以 $k$ 为根的 $T$ 和 $U$ 中两两之间的 LCA 都是 $k$，这其实是一个类似于二分图匹配的问题。具体的，可以将这个问题转化成对于 $k$ 在 $T$ 上的儿子 $a_1,a_2,\dots,a_{degT_k}$，和在 $U$ 上的儿子 $b_1,b_2,\dots,b_{degU_{k}}$ 之间，若一个点 $x$ 在 $a_i$ 和 $b_j$ 的子树中，则连接一条 $(i,j,A_x)$ 的边，代表一对匹配。这一步转化后，现在只需要求这个二分图中找到大小为 4 的最小匹配。

由于二分图两边点数的总和只有 $degT_k+degU_k$，所以可以对每个 $k$ 考虑 $\tilde{\mathcal O}(degT_k+degU_k)$ 解决这个问题，总复杂度就只有 $\tilde{\mathcal O}(\sum n)$。首先显然重边只用保留边权最小的一条。其次事实上，只要对每个左部点保留边权前 4 小的边也不会影响答案。证明考虑若选择了第 5 小的边，则剩余的 3 组匹配一定无法完全包含前 4 小的边的右端点，所以可以将第 5 小的边调整到没选的前 4 小的边一定不劣。所以每个左部点直接保留前 4 小的边即可，总边数就缩到 $\mathcal O(degT_k+degU_k)$ 级别了。由于流量 $flow=4$ 很小，直接用费用流跑匹配，使用 Primal-Dual 能做到 $\mathcal O(n\log n)$，实测直接 SSP 也能过。

现在思考如何建出这个图，即考虑如何快速求出以 $k$ 为根时，在 $a_x$ 子树中前 4 小的不相同的边。考虑在 $U$ 中将 $b_i$ 的子树内的点 $v$ 在 $T$ 中染色成 $i$，则需要在 $T$ 中找 $a_x$ 的子树中 4 种颜色的点的最小值。注意到我们实际上不可能每次吧 $k$ 提出来做根跑 dfs，但是可以将 $k$ 的邻域分为 $k$ 的父亲和 $k$ 的儿子，$k$ 的父亲对应的子树直接全部染色成 0，每次换根时就只会修改一个位置了，剩下的儿子子树的染色过程可以在 $U$ 上用 dsu on tree 在 $\mathcal O(n\log n)$ 做完。再开一棵线段树维护当前节点对应的 $T$ 上欧拉序区间的最小的 4 种颜色和权值，在 $T$ 上做线段树区间查即可，总复杂度为 $\mathcal O(n\log^2 n+Flow(n))$，$Flow(n)$ 为边数为 $n$ 的费用流的复杂度。

注意最短路要开 long long，虽然最后的增广最短路只会有 $2\times 10^9$，但过程中可能需要经过的最短路会 $<-2\times 10^9$。

[code](https://atcoder.jp/contests/arc213/submissions/72825096)