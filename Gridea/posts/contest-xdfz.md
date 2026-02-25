---
title: '比赛'
date: 2026-01-30 15:50:13
tags: [做题记录]
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

## [快速傅里叶变换](https://zhengruioi.com/problem/3438?cid=2033&ui=1)

其实还有 [君子兰](https://zhengruioi.com/problem/2489?cid=2036&ui=1) 和 [double](http://goj.wiki/d/Union2024/p/P1422)

可以直接对差分后的数组 $c$ 进行计数。令 $c_i=a_i-a_{i-1}$，$b$ 为 $c$ 排列后的数组，则 $b,c$ 可以与 $a$ 一一映射当且仅当 $\forall b_i>0,c_i\le c_{i+1}$ 且 $\sum b_i=\sum c_i\le m$。$\Large{\color{red}\Diamond}$

由于期望的线性性，最后做一次前缀和是不需要的，只要求出 $E(b_i)$ 后再做一次前缀和即可，即 $E(\sum_{j=1}^i b_j)=\sum_{j=1}^iE(b_j)$。对于每个位置 $i$ 单独考虑，$E(b_i)=\sum_{j>0}(j\times P(b_i=j))=\sum_{j>0} P(b_i\ge j)$，这一步就是**阶梯化贡献**。若 $b_i\ge j$ 则 $\forall k\ge i,b_k\ge j$，所以就是求出 $c$ 中有至少 $n-i+1$ 个数 $\ge j$ 的概率，转成求方案数后使用二项式反演做容斥。钦定有 $i$ 个数 $\ge j$ 的方案数为 $\binom{n}{i}\binom{m-i(j-1)}{n}$，所以恰好有 $i$ 个数 $\ge j$ 的方案数就是 $\sum_{k=i}^n(-1)^{k-i}\binom{k}{i}\binom{n}{k}\binom{m-k(j-1)+n}{n}$。因为只有 $(-1)^{k-i}$ 中有 $i$，所以可以先预处理出 $f_i=\sum_{j=1}^m\binom{n}{i}\binom{m-i(j-1)+n}{n}$，然后做容斥的时候再枚举 $k\in [1,n]$ 求出的是恰好，最后再做一次后缀和得到至少。复杂度为 $\mathcal O(n^2+m\ln m)$。

## [奖金](https://newoj.daimayuan.top/p/4562?tid=6964a11a54aec22695ba97ba)

### 题意：

给定一个长度为 $2n-1$ 的数组的所有奇数位的值，在偶数位填入数，使得``最大子段和-最大非负区间和``最大，非负区间表示一个区间内的所有数都是非负数。所有数的权值都要在 $[-k,k]$ 中。

### 题解：

令最大子段和区间为 $[l,r]$，最大非负区间为 $[L,R]$。若不是 $l\le L \le R\le r$，则可以将 $[L,R]$ 不在 $[l,r]$ 部分的所有偶数位都填为 $-1$，可以使答案更优，所以必然满足 $l\le L\le R\le r$。若填入 $0\le x< k$，讨论 $x$ 所在位置不难发现将 $x\gets x+1$ 一定不劣，所以偶数位只会填入 $-1/k$。$\Large{\color{red}\Diamond}$

若 $l>2$，则可以将 $[2,l)$ 的所有偶数位都填成 $k$，由于值域上界为 $k$，所以将 $l\gets 1+[a_1<0]$ 时补入的区间最大后缀和 $mx$ 一定 $\ge 0$，此时最大子段和加 $mx$，最大非负区间和至加 $mx$，所以对答案一定不劣，同理 $r\gets n-[a_n<0]$。$\Large{\color{red}\Diamond}$

然后开始 dp，令 $f_{i,j}$ 表示前 $i$ 个位置填了 $j$ 个 $-1$ 时最小的 $sum[L,R]$，求答案时枚举 $j$，然后可以求出填了多少个 $k$，最大子段和就是 $sum[1+[a_1<0],n-[a_n<0]]$。
$$
f_{i,j}=\min_{k=0}^{i-1}
\begin{cases}
\max(f_{k-1,j-1},sum(k+1,i) & k\bmod 2 =0 \\
\max(f_{k-1,j},sum(k+1,i)) & k \bmod 2 =1
\end{cases}
(\forall x\in [k+1,i],a_x\ge 0)
$$
现在直接做是 $\mathcal O(n^3)$。优化考虑将 $\max$ 拆开，由于显然 $f_{i,j}$ 对于固定的 $j$，$i$ 越大 $f_{i,j}$ 单调不减，$sum(k+1,i)$ 也是单调不增，所以可以双指针直接找到 $\max$ 的转折点，然后就是 $\mathcal O(n^2)$。代码实现时为了方便将 $f_{i,j}$ 两维交换了，存储在 $f_{j,i}$ 了。

## [回](https://newoj.daimayuan.top/p/4579?tid=6967b0d454aec22695c021c3)

感觉像脑电波题。赛时一步都想不出来。

首先**观察**到单次操作后 $X_{i,j}=(A_{i-1,j}+A_{i,j-1}+A_{i+1,j}+A_{i,j+1}-4A_{i,j})/2$ 会呈现为操作点的 $X=2$，经过操作点的两条对角线上的点 $X=1$，其余都 $X=0$。$\Large{\color{red}\Diamond}$

然后就是比较套路了。令 $B$ 矩阵为对应点是否被选择的矩阵（即所求的矩阵），将 $B_{i,j} \to P_{i+j}$，$B_{i,j} \to Q_{i-j}$，即 $P$ 和 $Q$ 为主副对角线上 B 的和。不难发现 $P,Q$ 的奇偶位是独立的，并且都满足 $\sum_{i\bmod 2=o} P_i=\sum_{i\bmod2=o} Q_i(o=\{0,1\})$（**这里获得了两条方程**）。

接下来询问形如 $P_{i+j}+Q_{i-j}=X_{i,j}$ 的等式，由于将所有的 $P_i\gets P_i-x$，$Q_i\gets Q_i+x$ 也不会影响所有的等式成立。所以看似有 $(n+1)^2$ 条方程，但实际上只有 $4n-4$ 条本质不同的方程，再加上上面的 $2$ 条共有 $4n-2$ 条方程，而刚好也有 $4n-2$ 个未知数，只要设参然后代入就能求出 $P,Q$。打表手玩后发现只要将含 $P_n,P_{1+n},Q_0,Q_1$ 的方程列完就刚好足够。

考虑将网格图转成二分图$\Large{\color{red}\Diamond}$。将 $B_{i,j}=1$ 视为 $L(i+j)\lrarr R(i-j)$，则此时左右部点的度数序列分别就是 $P,Q$，但是这个二分图会有限制左部点只能连向一个右部点区间（只会包含）。需要构造方案就直接将左部点能到达的区间长度排序，贪心尽量当前左部点连向 $Q$ 中区间最大的点即可，需要用线段树维护，所以总复杂度为 $\mathcal{O}((n+k)\log n)$。

## [pingpong](https://www.luogu.com.cn/problem/P12616)

赛时。

多次询问是假的，直接离线排序。首先 $\sum freq\le 10^6$ 是好做的，只要花费 $\mathcal{O}(\log n)$ 的时间消掉一个网即可。正解考虑优化这个过程，首先会处理左右端点有多个相同位置的网的情况，直接可以 $\mathcal{O}(1)$ 消掉一个位置所有的网，然后每次就可以花费 $\mathcal{O}(\log n)$ 让 $T\gets T-dis,dis\gets dis+1$，所以只会有 $\mathcal{O}(\sqrt T)$ 种坐标，将所有完全相同的网合并后，每种网只会出现 $\mathcal{O}(\frac{\sqrt{T}}{len_i})$ 次，所以总和为 $\mathcal{O}(\sqrt T\ln \sqrt T)$，复杂度是 $\mathcal{O}((N+\sqrt T)(\log N+\ln \sqrt T)+Q\log Q)$。

## [select](https://www.luogu.com.cn/problem/P10656)

赛后。感觉 $\mathcal{O}(n^2)$ 和正解没有任何关系啊，不会分治还是太菜了。

首先是即使没有观察到性质也应该想到 $\mathcal{O}(n\log^2n)$ 的分治做法。分治后钦定第一个区间一定要过 $mid$，离线掉一维后就只要做对于 $b$ 数组的每种选择 $[l_2,r_2]$ 找到包含 $mid$ 的极长合法段 $\Large{\color{red}\Diamond}$。首先 $b_{l_2-1}$ 和 $b_{r_2+1}$ 显然只会是与当前分治区间 $a[l,r]$ 颜色相同的点或 $l_2=1/r_2=m$，否则扩展后一定更优，于是也可以将 $b$ 数组删到只剩 $r-l+1$ 个。

$[l_2,r_2]$ 是二维状态，考虑对 $r_2$ 扫描线，同时数据结构在 $l_2$ 维护 $[l_2,r_2]$ 的状态。对于 $b$ 选择 $[l_2,r_2]$，维护 $[L,R](L\le mid\le R)$ 表示 $a[L,R]$ 是与 $b[l_2,r_2]$ 不重的极大区间，显然对于同一个 $r_2$，随着 $l_2$ 增大对应的 $L$ 单调不增，$R$ 单调不减，所以可以使用类似单调栈的思路解决。当 $r_2\gets r_2+1$，令 $b_{r_2}=a_x$，若 $x\le mid$，所有的 $L$ 和 $x$ 取 $\max$。若 $x\ge mid$，所有的 $R$ 和 $x$ 取 $\min$，刚好对应一段后缀，单调栈维护即可，过程中需要做区间加求区间最值，总复杂度 $\mathcal{O}(n\log^2 n)$。

考虑用性质优化，首先显然答案至少为 $\max(\sum x,\sum y)$，而最后的答案为 $x[l_1,r_1]+y[l_2,r_2]$，所以一定有 $x[l_1,r_1]>\frac{\sum x}2$ 或 $y[l_2,r_2]>\frac{\sum_x}2$，否则还不如全选一个区间，所以找到最小的 $\sum_{i=1}^px_i\ge\frac{\sum x} 2$，$\sum_{i=1}^q y_q\ge\frac{\sum y}2$，则一定有 $[l_1,r_1]$ 跨过 $p$ 或 $[l_2,r_2]$ 跨过 $q$，然后就不用分治和去重了，把 $p,q$ 当作上面的 $mid$ 做即可，复杂度为 $\mathcal{O}(n\log n)$。

## [区间](https://qoj.ac/problem/2070)

赛后。这个也太抽象了，第一步都想不到。

首先有个显然的性质，一次取肯定会取完一个 ``LDS``，所以可以考虑直接将 ``LDS`` 缩起来。（这个是赛时想到的）

然后就是将这个思路继续拓展。实际上，由于一个``LDS``内的选取顺序一定是连续的，所以影响他们什么时候取的就只有平均数（总和）了 $\Large{\color{red}\Diamond}$，所以对于相邻同侧的两个块 $(s_1,len_1)$，$(s2,len_2)$ 只要满足 $\frac{s_1}{len_1}\ge \frac{s_2}{len_2}$ 就一定会取完第一个块后立刻取第二个块（因为平均值拼上会更大），所以直接将两个块合并。此刻，$k$ 左右两侧的块就会分别单调了，即平均值形成 ``\k/`` 的样子，对于先选左边和先选右边做差后能证明先选平均值更小的一定更优，所以直接将左右的块组成的序列归并就能得到操作顺序了。

现在需要一个数据结构，支持增删区间，维护排序后的带系数的全局贡献和，直接使用平衡树维护，插入删除对其他贡献系数的影响求区间和即可。也可以提前将所有的单调栈的块信息预处理后按平均值离散化后在线段树上做单点修区间求和，复杂度 $\mathcal{O}(n\log n)$。

## [序列](https://qoj.ac/problem/964)

赛后。其中 $\mathcal{O}(n\sqrt n\alpha(n))$ 和 $\mathcal{O}(n\log n)$ 的做法都在[代码源](http://oj.daimayuan.top/contest/417/problem/3402)的题解中亦有记载，不改题导致的。

首先 $\mathcal{O}(n\sqrt n \log n)$ 的做法很显然，如果使用莫队尝试根号平衡。这个应该是比较套路的做法了，使用回滚莫队后，如果右端点只有向右移动，则每次就类似于初始时 $b_i=-i$，给后缀加一，求最后一个 $\ge 0$ 的位置。考虑使用单调栈维护后缀最大值，每次增加 $[x,n]$ 就找到 $x$ 在单调栈中的前驱后继（包括 $x$），然后将前驱删除，这个过程不难用链表+并查集维护。然后考虑左端点也可能会乱动，如果暴力撤销单调栈和链表会影响复杂度均摊，所以考虑和询问平衡复杂度。

考虑对值域分块，维护每个块内的后缀最大值（单调栈），后缀加 $[x,n]$ 的时候会将 $x$ 所在块分裂，只要使用上面的链表+并查集维护单调栈即可，然后剩余的块直接在 $id_x+1$ 打上差分标记即可，询问时再做前缀和。比较妙的是可以提前将 $a_l$ 的 $\sqrt n$ 种取值也作为分块的端点，这样所有的后缀加/减都只要打差分标记了，不会因为维护单调栈而影响均摊。查询的时候先找到答案在那个块后在块中跑单调栈即可，总复杂度为 $\mathcal{O}(n\sqrt n\alpha(n))$。

另一种做法就是让 $x$ 从 $n$ 到 $1$，由于对于 $[l_1,r_1]\sube [l_2,r_2],ans[l_1,r_1]\le ans[l_2,r_2]$，所以可以在求出 $ans[l_2,r_2]$ 前忽略 $[l_1,r_1]$，这样当前的询问区间就是互不相交的，所以左右端点分别递增，可以使用线段树维护后缀加，当确定一个 $ans[l,r]=x$ 时，将 $[l,r]$ 删除，然后在线段树上二分来加入新的极长询问区间。复杂度 $\mathcal{O}(n\log n)$。

## [染色](https://newoj.daimayuan.top/p/3388?tid=69818a06f0fd3b148a6f06b0)

令 $f_T$ 表示 $g(c,S)=T$ 的方案数。
$$
ans=\sum_{T=g(c,S)}f_T|T|^k\\ =\sum_{S}f_S\sum_{i=1}^k\binom{|S|}{i}i!\left\{{k\atop i}\right\} \\ =\sum_{i=1}^ki! {k \brace i}\sum_{S} f_S\binom{|S|}i
$$
考虑 $\binom{|S|}i$ 的意义是在 $S$ 中选 $i$ 种颜色的方案数，则可以转为枚举选出后的集合 $T\sube S,|T|=i$，令 $g_T=\sum_{T\sube S} f_S$，则 $ans=\sum_{i=1}^ki! {k \brace i}\sum_{|T|=i} g_T$。由于颜色集合无标号，所以可以令 $g_{S}=g_{T},|S|=|T|$，令 $h_i=g_S,|S|=i$，则 $ans=\sum_{i=1}^ki! {k \brace i}\binom{m}{i}h_i$。 

考虑求 $h$。$h_i$ 表示 $[1,i]\sube g(c,S)$ 的方案数，正着不好求，考虑容斥，令 $d_i$ 表示钦定选的都是 $>i$ 的方案数，则二项式反演得 $h_i=\sum_{j=0}^i(-1)^j\binom{i}{j}d_j$。做 $d_i$ 可以直接简单 dp 转移。总复杂度 $\mathcal{O}(nk+k^2)$。

 [原神，启动！](http://goj.wiki/d/Union2024/p/P1318)

## [整数序列](https://qoj.ac/problem/7417)

没想到做闵可夫斯基和。

令 $f(x)$ 表示恰好分 $x$ 段的答案，显然 $f(x)$ 是一个上凸包。考虑对于一个线段树区间 $[l,r]$ 暴力维护出长度为 $r-l+1$ 的 $f$ 函数，合并的时候就是做 $(\max,+)$ 卷积，由于两个函数都是凸的，所以直接归并差分数组即可（闵可夫斯基和）$\Large{\color{red}\Diamond}$。

然后每次询问就是有 $\mathcal{O}(\log n)$ 个凸包，求出他们合并后的第 $k$ 项。直接合并就 $\mathcal{O}(n)$ 了，可以 wqs 二分后在每个凸包中再二分求出交点，复杂度为 $\mathcal{O}(n\log n+q\log^2 n\log V)$。

实际上可以将最后一个求交点的二分离线下来做一次整体二分，复杂度优化到 $\mathcal{O}(n\log n+q\log n\log V)$。
