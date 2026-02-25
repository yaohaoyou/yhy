---
title: 'AtCoder 做题记录'
date: 2024-10-31 21:38:33
tags: [做题记录]
published: true
hideInList: false
feature: 
isTop: true
---
$$
\def\OO{\mathcal O}
\def\opn#1{\operatorname{#1}}
\def\dia{\Large\color{red}\Diamond}
$$

## AtCoder Regular Contest 186

### [A  mod M Game 2](https://www.luogu.com.cn/problem/AT_arc185_a)

**Difficulty：1042**

> 唐完了，不会做

打表（~~大便~~）题，$1 \le\frac{n\times(n-1)}2 \mod m \le n$ 时 Bob，否则 Alice。

### [B  +1 and -1](https://www.luogu.com.cn/problem/AT_arc185_b)

**Difficulty：1332**

> 我都能场

最后数列的状态固定，从前往后模拟，前面有多的就留个 tag。

### [E  Adjacent GCD](https://www.luogu.com.cn/problem/AT_arc185_e)

**Difficulty：2185**

> 欧拉函数，数论

欧拉函数反演
$$
n=\sum_{d|n} \varphi(d) \\
\gcd(a,b)=\sum_{d|\gcd(a,b)} \varphi(d) = \sum_{d|a \wedge d|b} \varphi(d)
$$
对于本题，每次加入一个 $a_i$ 后，新增 $ans+\sum_{j=1}^{i-1} \gcd(a_j,a_i)\times2^{j-1}$ 的贡献。

由于 $\gcd$ 的其中一项确定，则可以枚举 $a_i$ 的因数 $d$，添加 $sum_d \times \varphi(d)$ 的贡献。最后对于每个因数 $d$，$sum_d +=2^{i-1}$ 即可。

### [D Random Walk on Tree](https://www.luogu.com.cn/problem/AT_arc185_d)

**Difficulty：2649**

> 推式子，期望

就是走完 $n$ 条长度为 $m$ 的链。走完一条链的充要条件是走到叶子节点，钦定 $dep_0=0$。定义有效点为之前没别走过的点。

$f_i$ 表示从深度为 $i$ 的有效点走到 $i+1$ 的有效点期望步数。
$$
f_{i}=\frac12+\frac{1+f_{i-1}+f_{i}}2 \\
f_i=2+f_{i-1}
$$
即有 $\frac12$ 的概率直接走到，和先往 $i-1$ 走再走回来，再到 $i+1$ 的步数期望。

初始化 $f_0$ 与当前有多少条已经走完的链相关，并且如果走到了无效点还要走回来。设可以走到的有效点数为 $k$，$p_i$ 表示从深度为 $i$ 的点走到 $i-1$ 的步数期望。

$p$ 实际上在链上走的情况和 $f$ 相同，故 $p_i=2+p_{i+1}$，初始化 $p_m=1$。
$$
f_0=\frac{k}{n}+(1-\frac{k}{n})\times(1+p_1+f_0)  \\
f_0=\frac{n+(n-k)\times p_1}i
$$


先计算从 $n-1$ 个叶子回到 $0$ 号点的贡献，即为 $(n-1)\times\sum_{i=1}^mp_i$。

再计算从 $0$ 号点到 $dep=1$ 的有效点后再到叶子节点的贡献和，即为 $\sum_{i=1}^n\sum_{j=1}^mf_j$，时间复杂度为 $O(n^2)$（注：每次 $f_j$ 都需要重新计算，因为 $f_0$ 的值会变）。

观察到 $f_i=2+f_{i-1}$ 的式子非常简单，甚至是等差数列，可以得到通项公式 $f_i=f_0+2\times(i-1)$，故
$$
\sum_{i=1}^m f_i=\sum_{i=1}^m(f_0+2\times(i-1))=m\times f_0 +m \times (m-1)
$$
优化后就可以 $O(1)$ 求出 $f_0$ 和 $\sum f_i$ 了，复杂度为 $O(n \log_2n)$，使用预处理逆元做到 $O(n)$~~，但是我懒了~~。

### Code

```cpp
p[m]=1;
for(int i=m-1;i;i--)  p[i]=imadd(p[i+1],2);
int invn=qpow(n,mod-2);
int ans=0,sum=0;
for(int i=1;i<=m;i++)   madd(ans,p[i]);
mmul(ans,n-1);
for(int i=1;i<=n;i++){
    int f0=immul(imadd(n,immul(n-i,p[1])),qpow(i,mod-2));
    madd(ans,immul(m,f0));
    madd(ans,immul(m,m-1));
}
```

## AtCoder Regular Contest 186

### [B  Typical Permutation Descriptor](https://www.luogu.com.cn/problem/AT_arc186_b)

**Difficulty：1677**

> 赛时差一点写完的计数，唐

不难得出当前序列中 $p$ 最小的数的位置，然后从这一点断开后形成两个新区间，两个区间相互独立，只要 $\times \binom{r-l}{p-l}$ 将数划分到两个区间即可。

### [C  Ball and Box](https://www.luogu.com.cn/problem/AT_arc186_c)

**Difficulty：2451**

> 贪心，博弈

按容量从小到大排序，相同容量花费从大到小。

最后的状态一定形如 $V_i$ 最大的 $m-1$ 个会只获得 $1$ 的贡献，剩余获得 $V_i$ 的贡献，即 $s=\sum_{i=1}^{k-m+1}V_i+m-1-\sum_{i=1}^kP_i$。

对后缀用大根堆维护最小的 $m-1$ 个 $V_i$ 作为所选的数中最大的 $m-1$ 个，剩余的选取所有 $[1,i-1]$ 中 $(V_i-P_i)$ 为正的，求和即可。

### [A  Underclued](https://www.luogu.com.cn/problem/AT_arc186_a)

**Difficulty：2511**

> 性质，转化

好困难。

看到 01 矩阵，尝试给二分图定向。当 $a_{i,j}=0$ 时，$L_i \leftrightarrow R_j$，当 $a_{i,j}=1$ 时，$R_i \leftrightarrow L_j$，则两个矩阵相似即为对于每个点在两个图中的出入度相同。

原矩阵上 $(i,j)$ 是不动点，当且仅当在二分图中改变图的形态但出入度不变时，上面连的边不变。考虑变一条边的方向后，会继续影响别的点，知道绕回原点，即形成一个简单环后才会结束，则不动点即为二分图上不在简单环上的边。

转化后就不困难了，设 $dp_{i,j,k}$ 表示左部点前 $i$ 个点和右部点前 $j$ 个点，形成的环能否覆盖恰好 $k$ 条边。枚举左部点新加 $u$ 个点，右部点新加 $v$ 个点，且这些点形成一个强连通分量。新覆盖成了 $u\times v$ 条边，即 $u$ 个左部点都会和 $v$ 个右部点的连边一一被覆盖。因为是可行性 dp，转移可以用 bitset，时间复杂度降为 $\mathcal O(\frac{n^6}\omega)$，但不用也能过。

## AtCoder Regular Contest 187

### [D Many Easy Optimizations](https://www.luogu.com.cn/problem/AT_arc187_d)

**Difficulty：2880**

[here](https://yaohaoyou.github.io/post/AT_arc187_d-solution/)

## AtCoder Regular Contest 197

### [D Ancestor Relation](https://atcoder.jp/contests/arc197/tasks/arc197_d)

**Difficulty：2062**

> 性质

$1$ 作为根，将 $A_{i,1}$ 取出后剩下的 $A$ 会被分成几个相同的集合，对于$A_{a_1}=A_{a_2}=...=A_{a_k}$  的集合，使答案 $\times k!$，因为这 $k$ 个点形成一条链，可以随意排列。每次由 $u$ 跑出在祖先-孙子关系图上的可达点作为集合递归，若该集合 $S$ 有几个点 $rt$ 满足 $rt$ 直接到达 $S$ 的所有点则为根，否则无解。

## AtCoder Regular Contest 198

### [D Many Palindromes on Tree](https://www.luogu.com.cn/problem/AT_arc198_d)

**Difficulty：2299**

> 构造

按照给定的矩阵构造出一个满足的带边权树再算答案即可。

暴力做就是若 $A_{u,v}=1$，预处理 $nx_{u,v}$ 表示从 $u$ 走到 $v$ 的下一步到达的点，暴力从 $u$ 走到 $v$，将相等的两个位置在并查集合并，复杂度为 $O(N^3\alpha(N))$。

思考到中途会重复走过很多路，所以考虑标记 $(u,v)$ 对是否走过。若当前的点 $(x,y)$ 标记过，就可以直接``break``，由于状态数只有 $O(N^2)$，所以复杂度也是 $O(N^2)$。

最后求答案可以将所有二元组按之间的距离从小到大排序，$ans_{u,v}=ans_{nx_{u,v},nx_{v,u}}\vee(find(u)=find(v))$，复杂度为 $O(N^2\alpha(N))$。

## AtCoder Regular Contest 200

[E popcount<=2](https://www.luogu.com.cn/problem/AT_arc200_e)

**Difficulty：2299**

> 分类讨论

将得到的 $A$ 序列全部异或 $x$ 后依旧满足情况，所以不妨将 $A$ 异或 $A_1$ 后使 $A_1=0$。直接钦定 $A_1=0$，最后将答案 $\times 2^m$ 即可。$\Large{\color{red}\Diamond}$ 

由于 $A_1=0$，$popcount(A_1\oplus A_i)\le 2$，所以 $popcount(A_i)\le2$。接下来分情况讨论。

- $popcount(A_i)\le1$，没有其他限制了，方案数为 $(m+1)^{n-1}$。

- 有且仅有一种 $popcount(A_x)=2$，方案数为 $\binom m 2(4^{n-1}-3^{n-1})$。

- 有多种 $popcount(A_{a_1},A_{a_2},..A_{a_k})=2$，且 $popcount(A_{a_1} \And A_{a_2} \And..\And A_{a_k})=1,k\ge2$，方案数为 $m((m+1)^{n-1}-2^{n-1}-(m-1)(3^{n-1}-2^{n-1}))$。

- 有且仅有三种 $popcount(A_x,A_y,A_z)=2$，此时只能有这三种数和 $0$ 出现，并且两两交的 popcount 都为 $1$，如 $\{A_x,A_y,A_z\}=\{3,5,6\}$。方案数为 $\binom m 3(4^{n-1}-3\times 3^{n-1}+3\times 2^{n-1}-1)$。

## AtCoder Regular Contest 201

[B Binary Knapsack](https://www.luogu.com.cn/problem/AT_arc201_b)

**Difficulty:1808**

> 贪心

因为 $W$ 很大，所以不能是 01 背包的思路，应该想贪心。

思考偏序关系，由于不同重量只有 $\log_2W$ 种，并且两个 $2^{x-1}$ 可以直接合并成 $2^x$，所以每次贪心取当前重量价值最大的一定更优。

对 $W$ 进行二进制拆位，从小到大，若当前第 $i$ 位为 $1$，则选一个重量为 $2^i$ 的一定不劣。$\Large{\color{red}\Diamond}$ 

剩下的排序后两两合并成重量为 $2^{i+1}$ 的物品，继续递归子问题。

## AtCoder Grand Contest 073

#### [A Chords and Checkered](https://atcoder.jp/contests/agc073/tasks/agc073_a)

**Difficulty:2219**

> 数学

由于 $2K<L$，所以每条弦围出的图形一定都不会包含圆心，所以初始一定为黑色，而当有一条新的弦交到这条弦时，会将这块图形分成新的两个部分，所以令与当前弦相交的弦的条数为 $x$，则会贡献 $\lceil\frac{x+1}{2}\rceil$。使用双指针求出能与当前弦的相交的弦的条数为 $m$，则这条弦的贡献为
$$
2^{n-m}\sum_{i=0}^m \binom{m}{i}\lceil\frac {i+1} 2\rceil\\
\sum_{i=0}^m \binom mi\lceil\frac i 2\rceil=\sum_{i=0}^m \binom mi\frac{i+2-i\bmod 2}2\\
=\frac 12(\sum_{i=0}^m \binom mi i+2\sum_{i=0}^m \binom mi+\sum_{i=0}^m \binom mi(i\bmod 2))\\
\sum_{i=0}^m \binom mii=\sum_{i=1}^m\frac{m!}{i!(m-i)!}i=m\sum_{i=1}^m \frac{(m-1)!}{(i-1)!(m-i)!}=m\sum_{i=1}^m \binom{m-1}{i-1}=m2^{m-1}\\
2\sum_{i=0}^m \binom mi=2^{m+1}
$$
$\sum_{i=0}^m \binom mi(i\bmod 2)$ 的意义为大小为奇数的集合的个数，前 $m-1$ 个选不选都可以，最后一个数要满足集合大小为奇数的限制，所以方案数为 $2^{m-1}$。

综上，一条弦的贡献为 $2^{n-m-1}\times((m+3)2^{m-2})$，$m=0/1$ 时特判一下即可。总复杂度为 $\mathcal O(n)$。

## AtCoder Regular Contest 213 (Div. 1)

#### [C Double X](https://atcoder.jp/contests/arc213/tasks/arc213_c)

**Difficulty:3241**

> 图论，数据结构

没想到我还会更新这个 md。

显然 $x_1,x_2,x_3,x_4$ 满足在以 $k$ 为根的 $T$ 和 $U$ 中两两之间的 LCA 都是 $k$，这其实是一个类似于二分图匹配的问题。具体的，可以将这个问题转化成对于 $k$ 在 $T$ 上的儿子 $a_1,a_2,\dots,a_{degT_k}$，和在 $U$ 上的儿子 $b_1,b_2,\dots,b_{degU_{k}}$ 之间，若一个点 $x$ 在 $a_i$ 和 $b_j$ 的子树中，则连接一条 $(i,j,A_x)$ 的边，代表一对匹配$\dia$。这一步转化后，现在只需要求这个二分图中找到大小为 4 的最小匹配。

由于二分图两边点数的总和只有 $degT_k+degU_k$，所以可以对每个 $k$ 考虑 $\tilde\OO(degT_k+degU_k)$ 解决这个问题，总复杂度就只有 $\tilde\OO(\sum n)$。首先显然重边只用保留边权最小的一条。其次事实上，只要对每个左部点保留边权前 4 小的边也不会影响答案。证明考虑若选择了第 5 小的边，则剩余的 3 组匹配一定无法完全包含前 4 小的边的右端点，所以可以将第 5 小的边调整到没选的前 4 小的边一定不劣。所以每个左部点直接保留前 4 小的边即可，总边数就缩到 $\OO(degT_k+degU_k)$ 级别了。由于流量 $flow=4$ 很小，直接用费用流跑匹配，使用 Primal-Dual 能做到 $\OO(n\log n)$，实测直接 SSP 也能过。

现在思考如何建出这个图，即考虑如何快速求出以 $k$ 为根时，在 $a_x$ 子树中前 4 小的不相同的边。考虑在 $U$ 中将 $b_i$ 的子树内的点 $v$ 在 $T$ 中染色成 $i$，则需要在 $T$ 中找 $a_x$ 的子树中 4 种颜色的点的最小值。注意到我们实际上不可能每次吧 $k$ 提出来做根跑 dfs，但是可以将 $k$ 的邻域分为 $k$ 的父亲和 $k$ 的儿子，$k$ 的父亲对应的子树直接全部染色成 0，每次换根时就只会修改一个位置了，剩下的儿子子树的染色过程可以在 $U$ 上用 dsu on tree 在 $\OO(n\log n)$ 做完。再开一棵线段树维护当前节点对应的 $T$ 上欧拉序区间的最小的 4 种颜色和权值，在 $T$ 上做线段树区间查即可，总复杂度为 $\OO(n\log^2 n+Flow(n))$，$Flow(n)$ 为边数为 $n$ 的费用流的复杂度。

注意最短路要开 long long，虽然最后的增广最短路只会有 $2\times 10^9$，但过程中可能需要经过的最短路会 $<-2\times 10^9$。

[code](https://atcoder.jp/contests/arc213/submissions/72825096)

