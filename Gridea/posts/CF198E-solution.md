---
title: 'CF198E Gripping Story题解'
date: 2024-11-14 18:14:43
tags: [题解,线段树]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/CF198E)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/CF198E-solution/)

### CF 2400

## 前言

好题啊，但是为什么题解区没有单 log 做法。

[双倍经验](https://www.luogu.com.cn/problem/P10590)

## 做法

首先不难想出 $O(n^2)$ 的 bfs 做法。

思考一个机械臂能抓住哪些新的机械臂，即 $dis(i)\le r \land m_i \le p$ 的所有 $i$，这是一个较为明显的二维偏序，应该可以直接使用线段树套线段树优化建图解决（不知道会不会 MLE）。

回顾[弹跳](https://www.luogu.com.cn/problem/P5471)的 Trick，对于一个点向一个坐标轴中的左下角矩阵连边，可以先使用排序后离线一维，再使用数据结构维护剩下一维。

具体的，对每个机械臂按照 $m_i$ 排序，将 $dis(i)$ 离散化后挂在线段树上。线段树上每个节点记录一个``queue``表示 $dis_i$ 在当前区间的 $i$ 集合，由于提前按照 $m_i$ 排序了，所以当前队列中的 $m_i$ 是单调不减的。利用这一条性质就可以类似于双指针，每次队首加入 bfs 后退队，如果当前队首不满足 $m_i \le p$ 则后面的必然也不满足。

实现时``queue``的空间常数非常大，会直接 MLE，可以使用``vector``并记录队头的位置。每个机械臂会在线段树中被加入 $O(\log_2n)$ 次，也只会被删除 $O(\log_2n)$ 次，所以时空复杂度都是 $O(n\times \log_2n)$。

[AC Code](https://codeforces.com/contest/198/submission/291406094)