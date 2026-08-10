---
title: 'ZR暑假集训讲题'
date: 2026-08-03 16:24:16
tags: [做题记录]
published: true
hideInList: false
feature: 
isTop: false
---
$\Large{\color{red}\Diamond}$ 为重点转换步骤。

## [P15246 [WC2026] 猫和老鼠](https://www.luogu.com.cn/problem/P15246)

感觉像是几个套路拼在一起的缝合题目，但我好像都无法快速识别。

先将这条数轴拉成一个平面图，x 轴是数轴，y 轴是时间，有左右边界 $x=0$ 和 $x=m$，那么 Jerry 需要从 $(0,x)$ 到 $(+\inf,x')$，而 Tom 需要通过若干条 $(a_i,t_i) \to (b_i,t_i+|b_i-a_i|)$ 的线段将这个平面图割开使 Jerry 无法通过。$\Large{\color{red}\Diamond}$

Tom 的线段都是斜率为 $\pm 1$ 的，Jerry 移动的斜率为 $[-1,1]$，考虑将这个图顺时针旋转 $45\degree$ 并扩大 $\sqrt2$ 倍（即将点 $(x,y) \to (x+y,y-x)$），左右边界变成 $y=x$ 和 $y=x-2m$。机器猫变成使用水平和竖直的线段将左右边界断开，有两种方式：

1. 一条水平和竖直线段直接相交，阻止 Jerry 通过。
2. 因为 Jerry 旋转后只能向右上（包含右和上）移动，所以可以使用两条不相交的线将 Jerry 的 x/y 坐标限制在一个区间中（如下图中红色线段是机器猫的不相交限制线段，Jerry 可以走绿色的路径，但到达了 ? 后就无法继续走）。

![](D:\yhy\Blog\[WC2026] 猫和老鼠配图.png)

考虑刻画这样的限制，对于每条竖线，令上面的点是 in，下面的是 out，横线左边的是 in，右边的是 out。可以发现对于两种方式都能用以下方式刻画：$in_x \to out_x$，对于满足 $in_x$ 在 $out_y$ 左上角的点连接 $out_y \to in_x$。$\Large{\color{red}\Diamond}$若最后能从在 $y=x$ 的点到达 $y=x-2m$ 的点，则经过的边的长度和就是 $k=1$ 时的答案。

继续拓展到 $k>1$ 的情况，要选出 $k$ 条不相交的，可以构建费用流模型 $\Large{\color{red}\Diamond}$

1. 将 $S$ 连向所有在 $y=x$ 上的点，容量为 $1$，费用为 $0$。
2. $in_x\to out_x$ 容量为 $1$，费用为 $w_x$。
3. $out_y\to in_x$ 容量为 $+\infty / k$，费用为 $0$。
4. 将所有在 $y=x-2m$ 上的点连向 $T$，容量为 $1$，费用为 $0$。

答案就是这个图在流量为 $k$ 时的最小费用。注意 $1$ 和 $4$ 的容量不是 $+\infty/k$ 是因为若在这个点重合时，Jerry 直接走到这个点只需要扣 $1$ 的血量，而 $3$ 是因为这条边只是虚构的边，实际画一下可以发现 Jerry 至少会扣两滴血量。

但是现在还是有 $\mathcal O(n^2)$ 条边，考虑优化建图，每个 $out$ 向左上角的 $in$ 连边，显然是一个二维偏序关系，使用主席树/可持久化树状数组优化即可。因为 $flow$ 很小，使用原始对偶求费用流最后复杂度为 $\mathcal O(nk\log^2n)$。

## [CF2097F Lost Luggage](https://www.luogu.com.cn/problem/CF2097F)

好像应该之前讲过，但当时不会轮廓线 dp 就没改。

列出一个 $m\times n$ 的矩阵，其中 $G_{i,j}$ 表示第 $i$ 天机场 $j$ 剩余的行李数量。不难建出网络流模型：

1. $(i,j) \to (i+1,j-1)$，容量为 $a_{i,j}$。
2. $(i,j)\to (i+1,j)$，容量为 $b_{i,j}$。
3. $(i,j)\to (i+1,j+1)$，容量为 $c_{i,j}$。
4. $S\to(1,i)$，容量为 $s_i$。
5. $(k,i)\to T$，容量为 $+\infty$。

第 $k$ 天的答案就是最大流，直接做复杂度是 $\mathcal O(nm^3)$，无法通过。

考虑 $n$ 很小时的做法，因为最大流 = 最小割，所以可以考虑维护 $n$ 个点到 $S$ 的连通性来计算最小割。记 $f_{i,j,S,0/1}$ 表示前 $i$ 行，目前到达 $j$，$(i,[1,j)$ 和 $(i-1,[j,n])$ 的连通状态为 $S$，$(i,j)$ 是否连通 $S$ 的最小割。用轮廓线 dp 不难做到 $\mathcal O(nm2^n)$。

## [【UER #11】企鹅游戏](https://uoj.ac/problem/772)

有结论：$\sum_{i=1}^m\sum_{j=1}^n [c_{i,j}>0]=\mathcal O(L^\frac43)$，其中 $c_{i,j}$ 表示 $s_j$ 匹配 $t_i$ 的次数。证明：

所以若将 $t_i$ 放入 $s$ 构建的 AC 自动机中跑，只在成功匹配的 $t$ 中计数是能够接受的。建出一棵 $end$ 树，$fa_x \to x$ 表示 $endpos(s_{fa_x})$ 是 $endpos(s_x)$ 在 fail 树上最深的终点的祖先。对于每次询问 $t$，将 $t$ 在 AC 自动机上匹配的 $endpos$ 集合 $S$ 的所有点在 $end$ 树中暴力 dfs 子树并贡献答案即可，复杂度为 $\mathcal O(L^\frac43)$。

直接暴力 dfs 常数比较大，可以类似按照拓扑序，从原来加边的地方改成维护从下到上的链，常数较小可以通过。

## [P6640 [BJOI2020] 封印](https://www.luogu.com.cn/problem/P6640)

最长公共子串考虑 SA。不难发现答案就是求 $\displaystyle\max_{i=l}^r\min(r-i+1,lcp(sufS_i,sufT_j))$。先把 $S+\#+T$ 拼起来，然后对于固定的 $i$，$lcp(sufS_i,sufT_j)$ 的最大值就是找 $rk_j$ 距离 $rk_i$ 最近的属于 $T$ 的 $j$，只用找前面和后面即可。然后处理对 $r-i+1$ 的限制，可以直接二分答案 $x$，然后在 $[l,r-x+1]$ 中寻找最大的 $lcp(sufS_i,sufT_j)$ 即可。复杂度为 $\mathcal O(n\log n+q\log n)$。

## OGF 入门题

给定 $n$ 和 $m$，你需要计数长度为 $n$ 的序列，每个数是 $1,2,3,4$ 之一，满足 $1$ 的数量减 $2$ 的数量等于 $m$。
$$
f_{i,j}=\sum f_{i-1,j-1}+f_{i-1,j+1}+2f_{i-1,j},f_{0,i}=0 \\
F_i(x)=F_{i-1}(x)(x+\frac 1x+2) \\
F_n(x)=(x+\frac 1x+2)^n\\
ans=[m](\frac{x^2+2x+1}x)^n\\
ans=[n+m](x+1)^{2n} \\
ans=[n+m]\sum_{i=0}^{2n} \binom{2n}i x^i\\
ans=\binom{2n}{n+m}
$$

## [P6624 [省选联考 2020 A 卷] 作业题](https://www.luogu.com.cn/problem/P6624)

考虑拆开 $val(T)$：
$$
val(T)=(\sum_{i=1}^{n-1}w_i)\times \gcd(w_1,w_2,\dots,w_{n-1})\\
=(\sum_{i=1}^{n-1}w_i)\times \sum_{d|w_1,d|w_2,\dots d|w_{n-1}} \varphi(d) \\
=\sum_d \varphi(d)[d|w_1\wedge\dots\wedge d|w_{n-1}]\sum_{i=1}^{n-1}w_i\\
$$
将 $d$ 的倍数的边拉出来做 Matrix-Tree 即可，但是还有问题就是矩阵树定理求解的是 $w_i$ 的积的和，但我们需要求 $w_i$ 的和。实际上 Matrix-Tree 的权值 $w_i$ 不一定是常数，还可以是函数，所以将 $w'_i=w_ix+1$，这样求出来的函数的一次项就是答案了$\Large{\color{red}\Diamond}$。做的过程只需要记录一次项和常数项即可，复杂度为 $\mathcal O(Vn^3)$，实际上准确的上界是 $\mathcal O(n\max d(V)n^3)$，可以通过。

## [AT_agc044_e Random Pawn](https://www.luogu.com.cn/problem/AT_agc044_e)

精妙的转化，积累一下套路。

首先不难发现可以在 $\max a_i$ 处断开，完成断环成链，移动至 $a_1=\max a_i$。令 $f_i$ 表示目前在 $i$ 的期望收益，不难列出方程$f_i=\max(a_i,\frac{f_{i-1}+f_{i+1}}2-b_i)$。尝试将 $b_i$ 提出来做常数项，构造 $g_i=f_i+d_i\Large{\color{red}\Diamond}$。
$$
g_i=\max(a_i,\frac{f_{i-1}+f_{i+1}}2-b_i)+d_i \\
g_i=\max(a_i+d_i,\frac{g_{i-1}-d_{i-1}+g_{i+1}-d_{i+1}}2-b_i+d_i)\\
g_i=\max(a_i+d_i,\frac{g_{i-1}+g_{i+1}}2-\frac{d_{i-1}+d_{i+1}-2d_i+2b_i}2)\\
$$
因为要让 $\max$ 后半部分的常数剔除，所以构造 $d_{i-1}+d_{i+1}-2d_i+2b_i=0$，即 $d_i=-2b_{i-1}+2d_{i-1}-d_{i-2}$，初始项随便设成 $d_0=d_1=0$ 即可。
$$
g_i=\max(a_i+d_i,\frac{g_{i-1}+g_{i+1}}2)
$$
$a_i+d_i$ 已经是常数了，考虑后面是一个类似取中点的形式，若将点 $(i,g_i)$ 放到坐标系中，取后面的部分代表了 $i-1,i,i+1$ 三点共线。但加上和常数取 $\max$ 时，发现会将 $i$ 的点往上提，会形成一个类似凸包的形态$\Large{\color{red}\Diamond}$。具体证明大概是 $2g_i\ge g_{i-1}+g_{i+1}$，即 $g_i-g_{i-1}\ge g_{i+1}-g_i$，所以会形成一个下凸壳，注意有 $a_{n+1}=a_1$。

## [AT_dwango2016qual_e 花火](https://www.luogu.com.cn/problem/AT_dwango2016qual_e)

好像依旧不太会 Slope Trick /ll

记 $S_i$ 表示在 $i$ 时刻的烟花的位置集合，$f_{i,j}$ 表示前 $i$ 时刻在 $j$ 的答案，不难列出 $f_{i,j}=\min_{k=1}^j f_{i-1,k}+\sum_{x\in S_i}|j-x|$。后面的 $\sum$ 部分显然是下凸函数，然后可以归纳证明 $F_i(x)=f_{i,j}$ 也是下凸函数，考虑使用 Slope Trick。$\Large{\color{red}\Diamond}$

使用堆维护斜率拐点（经过堆中的拐点时斜率会 $-1$），因为需要做前缀取 $\min$，即将所有的斜率和 $0$ 取 $\min$，考虑倒着维护从右往左的拐点。直接记录 $k,b$ 表示在 $+\infty$ 处的 $F(x)=kx+b$，当加入 $|x-p|$ 函数时，在 $x\ge p$ 时会 $k\gets k+1,b\gets b-p$，到了 $p$ 处时还原成 $p-x$，即设置两个在 $p$ 处的拐点时 $k\gets k-2,b\gets b+2p$。

做完了加凸函数，然后再前缀取 $\min$，直接从右往左走直到 $k\le 0$ 时即可。复杂度 $\mathcal O(n\log n)$。代码很好写，但理解了挺久的。