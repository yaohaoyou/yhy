---
title: 'P4593 [TJOI2018] 教科书般的亵渎 题解'
date: 2024-08-19 11:49:38
tags: [题解,数学,拉格朗日插值]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P4593)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p4593-solution/)

## 前言

太笨了，不会拆贡献，所以复杂度比较劣。

## 题意

给定操作 A 和操作 B。

定义**操作 A **是将 $x_i \gets x_i-1(x_i>0)$ 并获得 $\sum x_i^k$ 分数，$x_i$ 是第 $i$ 个怪物扣血前的血量，$k$ 是**总操作 B **次数。如果一次操作后会有新的 $x_i=0$，则继续进行**操作 A**。

定义**操作 B** 是当此时没有新的 $x_i=0$，进行一次**操作 A**。

给定集合 $S=\{x\in[1,n] \wedge x \notin a \}$ 表示怪物血量所构成的集合，求最后的总分数。

## 做法

$k$ 是好算的。

将 $S$ 拆成一段段连续的区间分别考虑，一段连续的区间必定是在同一次操作 B 中扣为 $0$。

设当前处理的血量区间为 $[l_i,r_i]$，对于 $j\ge i$ 的区间**当前**血量为 $[l_j,r_j]$，则当前的贡献 $\sum_{j=i}^{m+1}\sum_{x=l_j}^{r_j}\sum_{y=x-l_i+1}^{x} y^k$。

直接计算是 $O(Tm^2n^2)$，[这里放一份代码](https://www.luogu.com.cn/record/173524637)。

思考如何优化计算 $\sum_{x=l_j}^{r_j}\sum_{y=x-l_i+1}^{x} y^k$，设 $f(x)=\sum_{i=1}^x i^x,g(x,len)=\sum_{i=1}^x(f(i)-f(i-len))$，则 $ans=\sum_{i=1}^{m+1}\sum_{j=i}^{m+1}g(r_j,l_i)-g(l_j-1,l_i)$。

可以先使用一次拉格朗日插值 $O(m)$ 算出 $f(x)$，进而再使用一次拉格朗日插值 $O(m^2)$ 算出 $g(x)$。

总时间复杂度为 $O(T\times m^4)$，需要轻微卡常。

[AC Code](https://loj.ac/s/2138254)

