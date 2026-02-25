---
title: '比赛题解'
date: 2025-07-10 17:14:28
tags: [题解,做题记录]
published: true
hideInList: false
feature: 
isTop: false
---
$\Large{\color{red}\Diamond}$ 为重点转换步骤。

## [typer](http://goj.wiki/d/Union2024/p/P1515)

直接设 $f_{i,j}$ 表示前 $S[1 \sim i]$ 匹配 $T[1\sim j]$ 位的答案。

$$
f_{i,j}=\min(f_{i-1,j}+1,f_{i,j-1}+1,f_{i-1,j-1}+[S_i\not=T_j])
$$

直接做复杂度为 $\mathcal O(|S|m|T|)$。

由于 $|T|\le 20$，并且发现 $i-j\le f_{i,j}\le i+j$，所以 $i+j-f_{i,j}\le2|T|$，由于值域范围小，所以套路性的将值域放在定义维上，将原本的 $i$ 定为 dp 值。$\Large{\color{red}\Diamond}$

设 $g_{i,j}$ 为满足 $f_{x,i}=x+i-j$ 最小的 $x$。

上面的 $f$ 的转移式中前两种方法的 $i+j-f_{i,j}$ 是不变的，所以先 $g_{i,j} \leftarrow g_{i-1,j}$。

若想让 $S_i=T_j$，$g_{i,j} \leftarrow k(k>g_{i-1,j-2},S_k=T_j)$，否则 $g_{i,j} \leftarrow k(k>g_{i-1,j-1},S_k\neq T_j)$。

预处理出每个位置 $nx_{i,j,0/1}$ 表示 $S_i$ 后字符为/不为 $j$ 的第一个位置。

## [sum](http://goj.wiki/d/Union2024/p/P1520)

本题保证了无重边自环。

$k=1$ 简单。

将 $\sum f(S)^2$ 转成 $\sum \binom{f(S)}2$，赋予组合意义即为从 $S$ 的导出子图中任意选两条边的方案数的和，从而可以拆贡献至选取两条边进行计算。$\Large{\color{red}\Diamond}$

$$
f(S)^2=2\binom{f(S)}2+f(S)
$$

两条边的情况可能是两条无交边或有一个公用顶点，分开讨论并枚举公共点即可。

$$
f(S)^3=6\binom{f(S)}3+3f(S)^2-2f(S)
$$

$f(S)^2$ 和 $f(S)$ 直接使用上面的即可，重点讨论 $\binom{f(S)}3$ 如何拆开。

影响结果的只有任选的三条边的点数 $x$ 和方案数 $y$，贡献为 $y2^{n-x}$。

$x={3,4,5,6}$。由于总方案数为 $\binom{m}3$，所以 $x=6$ 可以直接用总的减去其它的计算。

$x=3$，即一个三元环。直接用三元环计数即可，令方案数为 $A$，复杂度为 $O(m\sqrt m)$。

$x=4$，可能是一条链或者一个菊花。

- 链：枚举中间那一条边 $(u,v)$，方案数 $B=(\sum (deg_u-1)\times (deg_v-1))-3A$，最后减 $3A$ 是因为如果形成三元环，每条边都会被作为中间的边多算一次。
- 菊花：枚举度数为 $3$ 的点 $u$，方案数 $C=\sum \binom{deg_u}{3}$。

$x=5$，即分离的一条三元链和一条边，枚举三元链的中心 $u$，方案数 $D=(\sum\binom{deg_u}2(m-2))-3A-2B-3C$。

$3A$ 因为三元环中三个点都会被作为链中心，$2B$ 因为插入的新边可能在链的两端，$3C$ 因为菊花的三条边都会被作为插入的新边。

$x=6$，$E=\binom m 3-A-B-C-D$。

$\binom {f(S)}3=2^{n-3}A+2^{n-4}(B+C)+2^{n-5}D+2^{n-6}E$。

## [sort](http://goj.wiki/d/Union2024/p/P1523)

寻找第 $k$ 小可以先转化成二分答案 + 求有多少个 $\le mid$。$k\leftarrow k-1$

这里的字典序有些不同，可以直接用 $A_i$ 记录 $i$ 出现的次数，比较 $A$ 和 $B$ 时从 $i=1\to n$ 比较 $A_i$ 和 $B_i$ 即可，若 $A_i<B_i$ 则 $A>B$，$A_i>B_i$ 则 $A<B$。

由于增加一个数一定会使字典序变小，所以 $S[l,l]>S[l,l+1]>...>S[l,n]$ 且 $S[1,r]<S[2,r]<...S[r,r]$，于是对于左端点固定的区间具有单调性，设二分的区间是 $[L,R]$，则可以通过双指针或二分对每个 $i$ 求出 $M_i$ 使 $S[i,n]<S[i,n-1]<...<S[i,M_i]\le S[L,R]$，进而求出 $S[L,R]$ 的排名。$\Large{\color{red}\Diamond}$

若 $rnk(S[L,R])\le k$，则将 $pr_i=M_i-1$ 表示删去 $[i,M_i],[i,M_i+1]...[i,n]$，并将 $k\leftarrow k-rnk(S[L,R])$。否则将 $pl_{i}=M_i$ 表示删去 $[i,i],[i,i+1],...[i,M_i-1]$。

生成 $[L,R]$ 时在剩余的所有区间中随机一个即可，期望每次能选到字典序排名的重点左右，所以复杂度是 $O(\log n)$ 的。

双指针的过程就是有 $O(n)$ 次加入和删除一个字符，并查询桶内第一个和 $S[l,r]$ 的桶内的不同值。可以使用线段树维护 $T_i=A_i-B_i$，加入字符 $c$ 时将 $T_c\leftarrow T_c+1$，删除时 $T_c \leftarrow T_c-1$，查询时在线段树上二分或提前存储第一个 $T_i\neq0$，若 $T_i>0$ 则 $A<B$，否则 $A>B$。总复杂度为 $O(n\log^2n)$。

## [countcircle](http://goj.wiki/d/dx2025/p/S1216)

设 $L_{i,j},R_{i,j},U_{i,j},D_{i,j}$ 分别表示 $(i,j)$ 向左，向右，向上，向下能走到的最远的位置。

原题就是求

$$
\sum_{i=1}^n\sum_{j=1}^m\sum_{x=U_i}^{i-1}\sum_{y=L_j}^{j-1}[D_{x,y}\ge i\wedge R_{x,y}\ge j]
$$

明显上面的式子是四维的，无法直接做。将矩阵进行分治，选择竖着的中线 $mid$，分别对左右独立讨论经过中线的方案数再乘起来，将四维转换为三维。$\Large{\color{red}\Diamond}$

两边情况相似，只考虑左侧穿过中线的情况。先枚举 $u\in[1,n],v\in (u,n]$，计算左侧选取的 ``匚`` 的数量。

![countcircle配图](D:\yhy\Blog\countcircle配图.png)

于是现在只要求

$$
\sum_{u=L}^R\sum_{v=u+1}^R\sum_{x=\max(l,L_{u,mid},L_{v,mid})}^{mid-1}[D_{u,x}\ge v]
$$

枚举完 $u,v$ 后分类讨论 $\max(l,L_{u,mid})$ 和 $\max(l,L_{v,mid})$ 哪个更大，若前者更大，则对于所有 $u$ 询问的区间已经固定，所以只要开一个桶记录 $D_{u,x}$ 的后缀个数和。如果是后者更大，就相当于求 $\displaystyle\sum_{x=\max(l,L_{v,mid})}^{mid-1}[U_{v,x}\le u]$，处理方式和上面类似，开另一个桶记录 $U_{v,x}$ 的前缀个数和。这样就能单次 $O(1)$ 解决。

设 $len=r-l+1,LEN=R-L+1$，这样单次的复杂度为 $\mathcal O(LEN^2+len\times LEN)$，由于分治时面积每次一定会减半，所以递归层数为 $\mathcal O(\log_2nm)$。若能保证 $LEN\le len$ 则单次复杂度为 $\mathcal O(len\times LEN)$，此时总复杂度正确。每次递归后若 $LEN>len$ 则从 $[l,r]$ 中间取中线变为从 $[L,R]$ 中间取中线，复杂度为 $\mathcal O(nm\log_2nm)$。

## [frame](http://goj.wiki/d/dx2025/p/P1548)

多树问题和距离问题考虑点分治和点分树。

点分树的性质：原树上 $u,v$ 的路径会经过点分树上的 $LCA(u,v)$，所以 $dis(x,y)=dis(x,LCA'(x,y))+dis(LCA'(x,y),y)$，$LCA'$ 表示在点分树上的 lca。$\Large{\color{red}\Diamond}$

考虑对第一棵树进行点分治，若当前分治中心为 $rt$，已经处理过的点集为 $S$，当前需要求 $u$ 到 $S$ 的答案。设 $i$ 以 $rt$ 为根的深度为 $a_i$，则需要求 $\min_{v\in S} a_u+a_v+dis_2(u,v)$，由点分治的性质可得

$$
\min_{v\in S} a_u+a_v+dis_2(u,v)=\min_{v\in S}a_u+a_v+dis_2(u,LCA_{2'}(u,v))+dis_2(LCA_{2'}(u,v),v) \\
=\min_{v\in S,x=LCA_{2'}(u,v)}(a_u+dis_2(u,x))+(a_v+dis_2(v,x)) & \Large{\color{red}\Diamond}
$$

$x$ 为点分树上 $u$ 和 $v$ 的祖先，所以 $x$ 只有 $\mathcal O (\log_2n)$ 个，当将 $v$ 加入 $S$ 时，跳过 $v$ 的每个祖先 $x$ 并将 $a_v+dis_2(v,x)$ 的贡献挂在 $x$ 上，$u$ 查询时只要将挂在所有祖先的贡献加上 $a_u+dis_2(u,x)$ 后求最大值即可，若 $u,v$ 在 $x$ 的同一颗子树内，则长度只会更大，不影响最小值更新。

复杂度为 $\mathcal O(n\log^2n)$，瓶颈在点分治和在点分树上跳祖先。

## [岁月](http://oj.daimayuan.top/contest/386/problem/3331)

正难则反。先容斥一下，考虑计算有多少方案使得没有一个点能被 $1，2$ 同时到达。$\Large{\color{red}\Diamond}$

令 $f_S$ 表示只保留 $S$ 导出子图并给其定向，$1$ 恰好能到达 $x\in S$ 的方案数，$g_S$ 和 $f_S$ 同理，从 $2$ 号点出发，$w(S)$ 表示 $S$ 的导出子图的边数。

$$
ans=2^m-\sum_{S \cap T=\empty}f_Sg_T2^{w(U-S-T)}
$$

由于 $S\cap T=\empty$，所以只需枚举 $T\sube U-S$ 即可，复杂度为 $\mathcal O(3^n)$。

思考如何求 $f,g$，同样用总方案数 $2^{w(S)}$ 减去不合法的。

先枚举 $T\sub S$，计算只能到达 $T$ 的方案数。内部可达为 $f_T$，外部 $S-T$ 的导出子图随意，一条边 $(u,v),u\in T,v\in S-T$ 的只能定向为 $(v,u)$，所以方案数为 $2^{w(S-T)}f_T$，枚举子集复杂度也是 $\mathcal O(3^n)$。

总复杂度为 $\mathcal O(3^n)$。