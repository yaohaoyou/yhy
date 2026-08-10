---
title: 'AT_arc221_a Two Arithmetic Progressions 题解'
date: 2026-06-02 14:43:00
tags: [题解,数学]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/AT_arc221_a)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/AT_arc221_a-solution/)

由于辗转相减可得 $\gcd(Ai+B,Ci+D)=\gcd((A-C)i+B-D,Ci+D)$，不难发现直接这样做一遍类似 exgcd 就能将 $A\to 0$，接下来令 $\gcd(Ai+B,Ci+D)=\gcd(b,ci+d)$，现在就变成求 $\sum_{i=1}^n \gcd(b,ci+d)$，其中 $b,d\in [-V^2,V^2],c\in [1,V]$。

首先将 $b\gets|b|$，看到 $\sum \gcd$ 形式套路地转化成 $\sum_{x|b}\varphi(x)\sum_{i=1}^n[x|ci+d]$，对于后半部分的 $\sum[x|ci+d]$ 可以写成二元一次不定方程 $ci+xk=-d$，其中 $i,k$ 为未知数，通过 exgcd 解这个方程可以得到 $i=px+q,p\in \Z$（$q$ 已知）的形式，求一下在 $[1,n]$ 中有多少个 $p$ 即可。

总复杂度为 $\mathcal O(TV\log V+V^2)$，瓶颈在预处理 $[1,V^2]$ 的欧拉函数，感觉还是比较劣，不知道有没有更快的做法。