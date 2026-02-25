---
title: 'CF1995D Cases 题解'
date: 2024-09-25 08:08:33
tags: [题解,Codeforces,DP]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/CF1995D)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/CF1995D-solution/)

### CF 2300

## 前言

我菜了，不会 SOSDP，是学习其他题解的做法。

## 题意

自己去看翻译。

## 做法

SOSDP 好题。

因为每个子串长度不超过 $k$，所以每 $k$ 个位就会有至少一个位是子串的末尾，共有 $n-k+1$ 个这样的区间，所以**充要条件**就是末尾字符构成的集合与 $n-k-1$ 个区间构成的集合都有交。

形象化来说，$S_i=\{c|c \in s[i,i+k-1]\}$，$T$ 为每个子串末尾字符组成的集合，$\forall S_i,S_i \cap T \not=\empty$，求 $|T|_{\min}$。

考虑 SOSDP，先预处理出每个 $S_i$，再使用子集 DP 转移。由于要记录当前状态是否与 $S_i$ 有交，时间和空间复杂度均为为 $O(2^c\times n)$，即使用 bitset 优化，空间依旧开不下，所以考虑正难则反。

上述方法空间较大的主要原因是难以维护当前状态与哪些 $S_i$ 有交，因为这个状态就已经是 $O(n)$ 的。考虑维护当前状态**是否与任意一个** $S_i$ 都无交，对于每个状态就只要 $O(1)$ 的空间了，对于和每个 $S_i$ 都不是无交的状态，即和每个 $S_i$ 都有交的状态，就可以成为 $T$。

具体实现就是预处理出 $sta_i=\{c|c\notin[s,i,i+k-1\}$，则 $sta_i$ 的任意一个子集都与 $s_i$ 无交，暴力枚举子集需要 $O(3^c)$，使用 SOSDP 转移将复杂度将为 $O(c\times 2^c)$，到最后 dp 值为 $0$ 的状态就代表与任意 $s_i$ 都有交，可以成为 $|T|$，更新答案即可。

[AC Code](https://codeforces.com/contest/1995/submission/282786245)