---
title: 'P3688 [ZJOI2017] 树状数组 题解'
date: 2025-09-04 21:11:08
tags: [题解,线段树]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P3688)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p3688-solution)

## 做法 

不一样的 cdq 分治做法。

记 $sum[l,r]=(\sum_{i=l}^r a_i)\bmod 2$

对树状数组熟悉的应该可以看出错误代码求解的是 $\begin{cases}
    sum[l-1,r-1] & l\not=1 \\
    sum[r,n] & l=1
\end{cases}$。

若询问的 $l\not=1$，则答案为 $a_{l-1}=a_r$ 的概率，若 $l=1$，则答案为 $a_r\oplus sum[1,n] = 0$ 的概率。其中 $sum[1,n]$ 就是在这次询问之前的操作的次数，直接记录即可。处理 $l=1$ 时开一个 $a_0=0$，由于 $a_0$ 永远不变，所以 $a_r=[a_r= a_0]$，思考如何维护 $a_x =a_y$ 的概率，令 $p_{x,y}$ 为 $a_x=a_y$ 的概率。

对于一次修改 $[l,r]$，分讨对 $p$ 的影响，令 $P=\frac 1 {r-l+1}$。不难得出
- 对于 $x\in[0,l),y\in[l,r]$，$p_{x,y}=p_{x,y}(1-P)+(1-p_{x,y})P$。
- 对于 $x\in[l,r],y\in[l,r]$，$p_{x,y}=p_{x,y}(1-2P)+(1-p_{x,y})2P$。
- 对于 $x\in[l,r],y\in(r,n]$，$p_{x,y}=p_{x,y}(1-P)+(1-p_{x,y})P$。

显然是对矩阵进行操作，先定义运算 $a\odot b=ab+(1-a)(1-b)$，思考 $\odot$ 运算的性质。

手玩一下可以发现 $\odot$ 满足交换律和结合律，所一可以使用线段树维护。下面的维护方式就五花八门了，这里给出一种和其他题解不同的 cdq 分治做法。

由于原题是矩阵操作，若想改成三维偏序就需要进行差分。解一下方程发现 $\odot$ 存在类似逆元，所以可以进行差分。具体的，$b \odot \frac b{2b-1}=1$（这里可能存在 $b=\frac 1 2$ 的情况，但后面再解决），所以对于不在所需矩阵内的可以通过多 $\odot \frac{b}{2b-1}$ 来取消贡献。

然后就将类似 $[l,r][L,R]$ 的操作差分成了四个 $[0,x][0,y]$ 形式的操作了，对于第 $i$ 个询问 $(a,b)$，会影响其答案的就是第 $j$ 次操作 $[0,x][0,y]$ 满足 $j<i \wedge a\le x \wedge b\le y$，于是转化成了三维偏序问题，由于 $\odot$ 满足结合律和交换律，所以 cdq 内使用线段树维护即可。

现在处理 $b=\frac 1 2$ 的情况，此时不存在逆元，即无法差分。但带回原式子发现只有满足 $r=l+1$ 或 $r=l+3$ 时会出现这种情况。对于 $r=l+1$，可以暴力 $O(r-l+1)$ 将操作记录，离线后再扫一遍解决。对于 $r=l+3$，只要 $O((r-l+1)^2)$ 暴力操作会影响的 $p_{x,y}$。

总复杂度为 $\mathcal O(n\log n+q\log n^2)$，无需卡常和卡空间，个人认为还是比较自然和好写的。

[AC Code](https://www.luogu.com.cn/paste/7noi0w4w)