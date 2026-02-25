---
title: 'AT_arc187_d Many Easy Optimizations 题解'
date: 2024-11-22 19:41:34
tags: [题解,AtCoder]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/AT_arc187_d)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/AT_arc187_d-solution/)

## 前言

怎么没有人写官方做法，``set`` 应该比线段树好写吧。

## 题意

给定长为 $n$ 的序列 $a,b$，对 $k\in[1,n]$ 求 $\min\{\max_{i=1}^kc_i-\min_{i=1}^kc_i,c_i=a_i \vee c_i=b_i\}$。

## 做法

开始也没什么信息，所以可以先钦定 $c_1=a_1\vee c_1=b_1$。当 $c_1$ 固定后，可以分析出一些结论了。设 $a_i\le b_i$，若不是就交换一下，则变成在区间上取两个端点之一。对于 $a_i\le b_i\le c_1$，显然 $c_i=b_i$ 是不劣的，同理，$c_1\le a_i\le b_i$，选择 $c_i=a_i$ 是不劣的。当固定这些 $c_i$ 后，又可以固定更多的 $c_j$。形式化的，设 $L$ 为当前固定的 $c_i$ 中的最小值，$R$ 为最大值，则满足剩下的 $a_i< L\le R< b_i$。

接着考虑剩下的区间，若存在 $a_i\le a_j \le b_j\le b_i$，即存在包含关系时，$i$ 所形成的极差一定不会比 $j$ 的更小，所以 $j$ 必然不会贡献答案，可以删除 $j$。

将最后剩下的区间设为 $l_1\le\dots\le l_m\le L\le R\le r_1\le\dots\le r_m$，则答案为 $\min\{\min_{i=1}^{m-1}(r_i-l_{i+1}),L-l_1,r_m-R\}$。

开一个 ``set`` 维护 $[l_i,r_i]$ 和一个 ``multiset`` 维护 $(r_i-l_{i+1})$。每次插入一个区间 $[a_i,b_i]$ 时先检查 ``set`` 中是否存在 $[l_j,r_j]$ 包含了 $[a_i,b_i]$，若有则不用修改，否则再将所有被 $[a_i,b_i]$ 包含的 $[l_j,r_j]$ 从 ``set`` 中删除，最后类似于链表的插入，将 $[a_i,b_i]$ 插入到 ``set`` 中，同时删除和插入时需要同步更新 ``multiset`` 中的答案集合。

由于每个区间只会插入和删除一次，所以时间复杂度为 $\mathcal{O}(n\times \log_2n)$。实际上要跑 1s 左右，STL 常数较大，但比较好写。

### [Submission](https://atcoder.jp/contests/arc187/submissions/60015816)