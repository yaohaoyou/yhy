---
title: '讲题'
date: 2026-01-30 15:52:29
tags: [做题记录]
published: true
hideInList: false
feature: 
isTop: false
---
$\Large{\color{red}\Diamond}$ 为重点转换步骤。

## [AT_arc201_b [ARC201B] Binary Knapsack](https://www.luogu.com.cn/problem/AT_arc201_b)

因为 $W$ 很大，所以不能是 01 背包的思路，应该想贪心。

思考偏序关系，由于不同重量只有 $\log_2W$ 种，并且两个 $2^{x-1}$ 可以直接合并成 $2^x$，所以每次贪心取当前重量价值最大的一定更优。

对 $W$ 进行二进制拆位，从小到大，若当前第 $i$ 位为 $1$，则选一个重量为 $2^i$ 的一定不劣。$\Large{\color{red}\Diamond}$ 

剩下的排序后两两合并成重量为 $2^{i+1}$ 的物品，继续递归子问题。

## [AT_arc200_e popcount<=2](https://www.luogu.com.cn/problem/AT_arc200_e)

将得到的 $A$ 序列全部异或 $x$ 后依旧满足情况，所以不妨将 $A$ 异或 $A_1$ 后使 $A_1=0$。直接钦定 $A_1=0$，最后将答案 $\times 2^m$ 即可。$\Large{\color{red}\Diamond}$ 

由于 $A_1=0$，$popcount(A_1\oplus A_i)\le 2$，所以 $popcount(A_i)\le2$。接下来分情况讨论。

- $popcount(A_i)\le1$，没有其他限制了，方案数为 $(m+1)^{n-1}$。

- 有且仅有一种 $popcount(A_x)=2$，方案数为 $\binom m 2(4^{n-1}-3^{n-1})$。

- 有多种 $popcount(A_{a_1},A_{a_2},..A_{a_k})=2$，且 $popcount(A_{a_1} \And A_{a_2} \And..\And A_{a_k})=1,k\ge2$，方案数为 $m((m+1)^{n-1}-2^{n-1}-(m-1)(3^{n-1}-2^{n-1}))$。

- 有且仅有三种 $popcount(A_x,A_y,A_z)=2$，此时只能有这三种数和 $0$ 出现，并且两两交的 popcount 都为 $1$，如 $\{A_x,A_y,A_z\}=\{3,5,6\}$。方案数为 $\binom m 3(4^{n-1}-3\times 3^{n-1}+3\times 2^{n-1}-1)$。

## [P9140 THUPC 2023 初赛 背包](https://www.luogu.com.cn/problem/P9140)

类似于[P2371 墨墨的等式](https://www.luogu.com.cn/problem/P2371)的思路，先取 $\frac{c_i}{v_i}$ 最大的物品作为基准并设 $m=v_i,k=c_i$，由于若 $V'$ 可以被凑出，则 $V'\equiv V(\bmod m)$ 的 $V$ 可以通过加入多个 $m$ 凑出，所以将物品的总大小在 $\bmod m$ 的剩余系上处理。$\Large{\color{red}\Diamond}$ 

对于 $(V',C'),V\equiv V'(\bmod m)$ 的情况，此时的总贡献为 $C'+\frac{V-V'}mk$，由于 $\frac V m$ 固定，所以需要使 $C'-\lfloor\frac{V'}m\rfloor k$ 最大，将这个值设为同余最长路上的距离。转移时从 $p$ 加上物品 $x$ 后转移至 $q=(p+v_x)\bmod m$，$f_q=f_p+c_x-\lfloor\frac{p+v_x}m\rfloor k$。

转移过程中需要保证没有正环和 $V'>V$。

- 若有正权环 $u_1\to u_2\to...\to u_{siz}\to u_1$，由于转一圈后物品总体积一定为 $m$ 的倍数，而由于选择的基准为 $\frac{c_i}{w_i}$ 最大，所以一定不如全部选择物品 $i$，矛盾，所以不存在正权环。
- 设 $\forall i\in[1,n], v_i\le lim_v=10^5$。图上共有 $m$ 个点，因为没有正权环，所以每个点最多走过 $1$ 次，走过的边数最多也只有 $m-1$ 条，每条边增加的体积 $\le lim_v$，所以 $V'\le (lim_v)^2=10^{10}<10^{11}$，所以 $V'<V$。$\Large{\color{red}\Diamond}$ 

由于有负边权，所以不能用 dijkstra。这个题数据水，最短路直接用 SPFA 就过了，正解应该使用转两圈的做法将复杂度做到 $O(nm)$。

建边的过程实际是枚举 $i\in[1,n],u\in[0,m)$ 并连边 $(u,(u+v_i)\bmod m,w)$，手玩一下（其实比较显然）可以发现对于 $i$ 会产生 $\gcd(v_i,m)$ 个环。由于本质上是在模意义下做完全背包，所以转移顺序并不影响。并且由于每个点只会在最短路上走一次，所以最短路只要在已知的 $\gcd(v_i,m)$ 个环上找到最小的 $dis$ 值，并用其转一圈更新这圈的其他点即可，也就是 $x\in[0,v_i):x\to (x+v_i)\bmod \to (x+2v_i)\bmod m\to...\to x$。写代码时为了方便，可以不用找到 $dis$ 最小值，直接在环上转两圈更新即可，复杂度为 $O(nm)$。

## [P7320 「PMOI-4」可怜的团主](https://www.luogu.com.cn/problem/p7320)

首先由一个结论是一棵树至少由 $\lceil\frac{leaf}2\rceil$ 条路径覆盖，构造是将叶子按 dfs 序排序后，路径为 $(lf_1,lf_{\lceil\frac{leaf}2\rceil}),(lf_2,lf_{\lceil\frac{leaf}2\rceil+1})\dots$，若 $leaf$ 是奇数则最后连一条 $(1,lf_{leaf})$。$\Large{\color{red}\Diamond}$

必要性显然，应为一条路径最多覆盖两个叶子。充分性是这样的路径可以使相邻两条路径都有交集。若有一个点 $u$ 没有被覆盖。

- 若 $u$ 有至少两个在 $u$ 儿子 dfs 序排列中相邻的 $v,w$，则必有一条经过 $v$ 子树的路径与一条经过 $w$ 子树的路径相交，所以 $u$ 一定被覆盖。

- 若 $u$ 只有一个儿子，若有不在 $u$ 子树内的叶子则有一条从 $u$ 子树内到外的路径，否则从 $1\to u$ 的路径上 $deg_f=1$，则存在从 $u$ 子树内到 $1$ 的路径。

综上，至少用 $\lceil\frac {leaf} 2\rceil$ 条路径一定能覆盖所有节点。

由于 $\lceil\frac n 6\rceil$ 和 $\lfloor\frac n 3\rfloor$  的关系与 $\lceil\frac x 2\rceil$ 相似，所以考虑提出 dfs 树并看叶子考虑。$\Large{\color{red}\Diamond}$

显然，若 $leaf\ge \lfloor\frac n 3\rfloor$，则选择第二种并将叶子节点输出即可。反之 $leaf < \lfloor\frac n 3\rfloor$，则覆盖所有点的路径数 $\lceil\frac {leaf} 2\rceil<\lceil\frac {\lfloor\frac n 3\rfloor} 2\rceil<\lceil\frac n 6\rceil$，使用上述的叶子节点相互匹配的做法后，剩下的路径用 $(x,x)$ 浪费掉即可。

## [AT_agc037_d Sorting a Grid](https://www.luogu.com.cn/problem/AT_agc037_d)

从无序的状态转移到有序的状态可以倒着思考，从有序的状态思考能到达的状态的共同点。 

由有序的状态进行每``行重排``后每行的值域集合不会变，设行重排后的矩阵为：
$$
\begin{matrix}
A&A&A&A&A\\
B&B&B&B&B\\
C&C&C&C&C\\
D&D&D&D&D\\
E&E&E&E&E\\
\end{matrix}
$$
$1\le A\le m,m+1\le B\le 2m \dots$

再``列重排``后矩阵的每一列都会包含 $A,B,C\dots$ 各一个，这是操作两步的必然结论。

最后一步再回到输入的乱序矩阵，则此时乱序矩阵进行``行重排``后需要满足每列都各有 $A,B,C\dots$ 各一个的性质。$\Large{\color{red}\Diamond}$

进行构造时将枚举 $(i,j)$ 后将 $i \leftrightarrow \lceil\frac {a_{i,j}-1} m\rceil+nm$，由于每行有 $m$ 个数，每种字符会出现 $m$ 次，所以最终连出的是**正则二分图（每个点度数都相同的二分图）**，每次需要寻找出一组完美匹配表示当前列的状态，随后删除这组边并继续寻找二分图完美匹配。本图任选一个左部点集合都满足 $out(S)=|S|$，由于 Hall 定理，存在完美匹配，删除匹配后依旧满足 $out(S)=|S|$，所以一定可以找出 $m$ 组完美匹配。$\Large{\color{red}\Diamond}$

## [AT_agc061_c First Come First Serve](https://www.luogu.com.cn/problem/AT_agc061_c)

设 $dp_i$ 表示 $[1,i]$ 的答案，转移为 $dp_i\leftarrow 2dp_{i-1}-C$，$C$ 为容斥掉的方案数。设 $i$ 最终取的值为 $t_i\in\{a_i,b_i\}$，则 $t_i$ 取 $a_i$ 和 $b_i$ 时结果相同当且仅当 $\forall t_j\notin[a_i,b_i]$，思考如何容斥掉这一部分。

因为 $a_i<a_{i+1},b_i<b_{i+1}$，所以区间之间不存在包含。若使 $\not\exist t_j\in[a_i,b_i]$，则对于 $L_i=\min j(b_j>a_i),R_i=\max j(a_j<b_i)$，当 $j\in[L_i,i)$ 选 $t_j=a_j$，$j\in(i,R_i]$ 选 $t_j=b_j$，可以使 $k\in[L_i,R_i]$ 都可以选出 $t_k\notin[a_i,b_i]$，即满足 $\not\exist t_j\in[a_i,b_i]$。$\Large{\color{red}\Diamond}$

所以对于 $dp_{R_i}$ 需要删去 $a_i$ 和 $b_i$ 重复的贡献，由于此时 $[L_i,R_i]$ 的方案固定，所以 $dp_{R_i}\leftarrow -dp_{L_{i-1}}$。

求 $L_i$ 和 $R_i$ 直接二分或双指针即可，复杂度为 $\mathcal O(n)/\mathcal O(n\log_2n)$。

## [P6657 【模板】LGV 引理](https://www.luogu.com.cn/problem/P6657)

感觉原本的定义还是比较复杂，尝试用比较简洁但不一定足够适用的讲述。

先构造矩阵
$$
M=\left[\begin{matrix}
f(sx_1,sy_1,tx_1,ty_1) & \dots & f(sx_1,sy_1,tx_n,ty_n)\\
f(sx_2,sy_2,tx_1,ty_1) & \dots & f(sx_2,sy_2,tx_n,ty_n)\\
&\ddots\\
f(sx_{n-1},sy_{n-1},tx_1,ty_1) & \dots & f(sx_{n-1},sy_{n-1},tx_n,ty_n)\\
f(sx_n,sy_n,tx_1,ty_1) & \dots & f(sx_n,sy_n,tx_n,ty_n)\\
\end{matrix}\right]
$$
使用 LGV 引理需要保证**存在构造**从 $(sx_i,sy_i)$ 到达 $(tx_{p_i},ty_{p_j})$ 的 $n$ 条路径之间互不相交，排列 $p$ **只能**为 $p=\{1,2,3..,n\}$。换言之，若 $\exist p_i\neq i$，则无法构造 $n$ 条互不相交的路径。LGV 引理只适用于 DAG。

LGV 引理：从 $(sx_i,sy_i)$ 到达 $(tx_i,ty_i)$ 的 $n$ 条路径互不相交的方案数为 $\det(M)$。

## [AT_agc057_d Sum Avoidance](https://www.luogu.com.cn/problem/AT_agc057_d)

神仙题，根本不可能想出来。

首先 $|A|$ 的上界显然是 $\lfloor\frac {S-1} 2\rfloor$，因为 $(1,S-1),(2,S-2)\dots$ 不能同时存在，若 $2|S$，也不能出现 $\frac S2$。而这个上界也可以直接构造出来，只要取最大的 $\lfloor\frac {S-1} 2\rfloor$ 个数即可，因为任意两个数相加已经 $>S$。此时想要让字典序尽量小。令选择的集合包括 $A\subseteq[1,\lfloor\frac {S-1} 2\rfloor]$，$B\subseteq [S-\lfloor\frac {S-1} 2\rfloor,S-1]$。

将字典序变小的过程就是将一些 $x\in B$ 的换成 $S-x$。可以证明，直接从小到大，如果加入 $x$ 后依旧凑不出 $S$，则在答案集合加入 $x$ 一定更优。$\Large{\color{red}\Diamond}$

>证明：对于任意一个 $x\in [1,\lfloor\frac {S-1} 2\rfloor]$，若前面的数能凑出 $x$，则加入 $x$ 不影响凑其他数。否则前面的数无法凑出 $x$，则可以加入 $S-x$，由于后面的加入集合的数都 $>x$，所以不会导致 $S-x$ 和其他数凑出 $S$。

这样就可以比较方便的 $O(S)$ 求答案，思考如何继续加速贪心过程。

设加入的最小数为 $d$，由于 $d\not\mid S$，$lcm(1,2,...43)>10^{18}$，所以 $d\le43$。思考两种添加方式，添加的数 $x\le \lfloor\frac {S-1} 2\rfloor$。

1. $x$ 可以由 $A$ 中的数凑出。
2. $x$ 不能被 $A$ 中的数凑出，但加入后也无法凑出 $S$。

$1$ 的做法可以后面二分时再处理，思考 $2$ 会加入哪些数。因为 $d\in A$，所以$2$ 加入的数在 $\bmod d$ 意义下互不相同，否则可以用 $1$ 做出，所以 $2$ 加入的数至多 $\mathcal O(d)$，复杂度可以接受。$\Large{\color{red}\Diamond}$

令 $f_i,i\in[1,d)$ 表示 $2$ 加入的数 $\bmod d=i$ 的最小的数，转移时枚举加入 $v$，若能加入需保证 $f_{(S-iv)\bmod d}+iv>S$，即保证 
$$
v\ge \max_{i=1}^{d-1}(\lfloor\frac{S-f_{(S-iv)\bmod d}}i\rfloor+1)
$$
由于转移式中只与 $v \bmod d$ 相关，所以枚举 $x = v_x\bmod d$，按上面的式子跑一遍后将 $v_x$ 加到 $v_x\equiv x(\bmod d)$ 为止。这一步需要枚举 $x$ 和 $i$，单次复杂度为 $\mathcal O(d^2)$。由于要从小到大进行贪心，所以对于所有的 $v_x$，每次只会选取最小的 $v_{mn}$ 更新所有的 $f$。更新 $f$ 时枚举 $i,j\in[1,d)$。
$$
f_{(i+j\times v_{mn})\bmod d}\leftarrow f_i + j \times v_{mn}
$$
由于每个 $x\in [0,d)$ 只会有至多一次 $x=mn$ 将 $f_x$ 更新至最小值（最终值），所以会进行 $\mathcal O(d)$ 次上述的``单次``，复杂度为 $\mathcal O(d^3)$。

$A$ 中 $\le x$ 的个数为 $\sum_{i=0}^{d-1} \max(0,\lfloor\frac {x-f_i} d\rfloor+[i\not=0])$。注意 $f_0=0$，$i=0$ 时不加一是因为无法选取 $0\in A$。

对于询问二分答案后求有多少个凑出的数 $\le x$，对于 $\le \lfloor\frac {S-1} 2\rfloor$ 的答案直接二分答案即可，$>\lfloor\frac {S-1} 2\rfloor$ 的答案先将 $k\leftarrow k-|A|$ 后反着二分。本题最终复杂度为 $\mathcal O(T(d^3+d\log_2k))$。

## [CF1389G Directing Edges](https://www.luogu.com.cn/problem/CF1389G)

ran_qwq 的讲题，感觉有点像答辩缝合怪。

连通性和给无向边定向先想到使用边双缩点，因为一个边双内的点一定可以定向成强连通分量，这样一定更优。此时从无向图变成了一棵树，然后考虑关键点的限制。

先随便取一个关键点做根，若一个子树内没有关键点，则将边全部定向为 $u\rightarrow fa_u$ 一定不劣，由于这种子树的贡献固定，所以再缩起来。具体的，若一条边 $(u,fa_u)$ 满足 $u$ 子树内没有关键点，而 $fa_u$ 子树内有关键点，则 $[\text{关键点能到达}fa_u]=[\text{关键点能到达}u]$，此时将 $u$ 子树和 $fa_u$ 缩到一起。此时所有叶子节点都是关键点。

可以开始树形 DP 了。令 $f_u$ 表示 $u$ 子树内强制选 $u$ 为饱和点的收益，$f_u=\max(f_v-w(u,v),0)+c_u$，当让顶点 $i$ 强制选为饱和点时将 $i$ 钦定为根即可，写下换根 DP 即可。

代码没写，感觉依托。

## [CF1017G The Tree](https://www.luogu.com.cn/problem/CF1017G)

lbw 的题感觉都很妙。

考虑将修改和查询的复杂度平衡，尝试类似于线段树标记永久化的思路。先不管 2 操作，若一个操作 ``1 v`` 能影响到 $u$，则 $v\to fa_u$ 的点一定已经被标记为黑色，手玩可以发现修改之间的顺序其实不影响，所以将修改合并，即维护 $c_u$ 表示在 $u$ 节点进行了 $c_u$ 次操作，则操作 ``1 v`` 能影响到 $u$ 当且仅当 $\sum_\text{i is on path(v,u)}c_i\ge dep_u-dep_v+1$，套路地，将 $dep_u-dep_v+1$ 移到左边，分给每个 $\text{i is on path(v,u)}$。将 $c_u$ 的初始值设为 $-1$，然后求最大后缀和（一定要包含自己）是否 $\ge 0$ 即可。

现在考虑操作 ``2 u``，首先肯定要将 $u$ 子树内的所有 $c_i$ 设为 $-1$，此外，需要让 $u$ 向上的最大后缀和变为 $-1$，所以将 $c_u\gets c_u-query(u)-1$。

直接上树剖维护，复杂度 $\mathcal O(n\log^2n)$。

## [AT_abc230_g [ABC230G] GCD Permutation](https://www.luogu.com.cn/problem/AT_abc230_g)

令 $S(p)$ 表示满足 $p$ 命题的方案数。
$$
ans=S(\gcd(i,j)\ne 1\wedge \gcd(P_i,P_j)\ne 1)\\
=S(1)-S(\gcd(i,j)=1)-S(\gcd(P_i,P_j)=1)+S(\gcd(i,j)=1 \wedge \gcd(P_i,P_j)=1)\\
=\frac{n(n+1)}2-2\sum_{i=1}^n \varphi(i)+S(\gcd(i,j)=1\wedge \gcd(P_i,P_j)=1)\\
$$
只要解决 $\beta=S(\gcd(i,j)=1 \wedge \gcd(P_i,P_j)=1)=\sum_{i=1}^n\sum_{j=1}^n [\gcd(i,j)=1\wedge\gcd(P_i,P_j)=1]$ 即可。

由莫反可得
$$
\beta=\sum_{x=1}^n\sum_{y=1}^n \mu(x)\mu(y)\sum_{i=1}^n\sum_{j=1}^n[(x|\gcd(i,j))\wedge (y|\gcd(P_i,P_j))]\\
=\sum_{x=1}^n\sum_{y=1}^n\mu(x)\mu(y)\binom{(\sum_{x|i,y|P_i}1)+1}2\\
\text{let} f(x,y)=\sum_{i=1}^n [x|i\wedge y|p_i]\\
\beta=\sum_{x=1}^n\sum_{y=1}^n \mu(x)\mu(y) \frac{(f(x,y)+1)f(x,y)}2
$$
每次加入一个新的数时枚举 $x|i,y|P_i$ 并修改对 $\beta$ 的贡献即可，复杂度为 $\mathcal O(n\ln n+\sum_{i=1}^n d(i)^2)$，打表得 $N=2\times10^5$ 时大约为 $6\times 10^7$。

## [P13997 【MX-X19-T6】「FeOI Round 4.5」はぐ](https://www.luogu.com.cn/problem/P13997)

路径上求可以差分转化成四个点到根求，同时可能有 $a_i\gets a_i\pm dep_i$，然后就是求 $\bigoplus_{i=0}^{dis(1,x)}(a_{p_i}+k)$，其中 $p_i$ 为 $1$ 走到 $x$ 的经过的第 $i$ 个点。每个位单独考虑，$x_k$ 表示 $x$ 二进制下的第 $k$ 位的值，拆项得
$$
(a_j+k)_i=(a_j)_i\oplus k_i\oplus[(a_j\bmod 2^i+k\bmod 2^i)\ge2^i]
$$
$\bigoplus(a_j)_i$ 可以直接预处理出根到 $x$ 的 $a$ 的异或和，$k$ 直接看 $dep_x$ 的奇偶性即可，最后一个考虑离线下来，将询问 $(x,k,i)$ 挂在 $x$ 上，使用 BIT 维护当前点祖先的 $a_j \bmod 2^i$ 即可，复杂度为 $\mathcal O(n\log^2 n)$。



## [One, Two, Three](https://qoj.ac/problem/6537)

怎么出了若干次的题都还没补过。

设共匹配 $A$ 组 $(1,2,3)$ 和 $B$ 组 $(3,2,1)$，求 $\max(A+B)$。显然 $(1,2,3)$ 选定的一定是最左边的 $A$ 个 $1$ 和最右边的 $A$ 个 $3$，$(3,2,1)$ 同理。再分讨一下发现取的 $(1,2,3)$ 匹配 $(a_i,b_i,c_i)$ 满足 $a_1<a_2<\dots<a_A$，$b_1<b_2<\dots<b_A$，$c_1<c_2<\dots<c_A$ 一定是不劣的，证明可以讨论 $2$ 的位置。现在就可以将匹配对应到 $A+B$ 个区间了。

过程其实就类似二分图匹配，需要对 $A+B$ 个区间 $[l_i,r_i]$ 匹配所在区间内的 $2$。考虑 HALL 定理，即需要满足对于任意一个 $S\in [A+B]$，满足 $|S|\le cnt2(\cup [l_i,r_i]),i\in S$，由于区间之间有偏序关系，即 $\forall l_i<l_j,r_i<r_j$，所以实际上 $S$ 取到一个区间是本质相同的，即 $R-L+1\le cnt2[l_L,r_R]$。

换一种说法，就是对于每一个区间 $[l,r]$，令被 $[l,r]$ 严格包含的区间数量为 $f_{l,r}$，则满足 $\forall l\le r,f_{l,r}\le cnt2[l,r]$。

对于每对 $(A,B)$，考虑 $f_{l,r}$ 的下界，先考虑 $(1,2,3)$ 的情况，令 $x\gets cnt1(1,l-1),y\gets cnt3(r+1,n)$，则 $[l,r]$ 需要包含 $\max(0,A-x)$ 个 $1$ 和 $\max(0,A-y)$ 个 $3$，按照匹配的顺序左右端点都单调可以发现 $[l,r]$ 的最右边 $y$ 个 $1$ 和最左边 $x$ 个 $3$ 会被外面的点匹配，所以内部就会剩下 $\max(A-x-y,0)$ 组 $(1,3)$ 需要匹配，所以有 $\max(A-x-y,0)\le cnt2[l,r]$。

同理考虑 $(3,2,1)$ 的情况能得到 $\max(A-cnt1[0,l-1]-cnt3[r+1,n],0)+\max(B-cnt3[0,l-1]-cnt1[r+1,n],0)\le f_{l,r}\le cnt2[l,r]$。

分讨两个 $\max$ 的取值，就能得到 $A,B,A+B$ 的范围了，构造由于 $(1,2,3)$ 和 $(3,2,1)$ 的区间内部满足左右端点都是单调的，所以在左端点加入，发现一个 $2$ 时贪心匹配最小的右端点即可。时间复杂度为 $\mathcal O(n)$。


## [AT_arc210_e [ARC210E] Subset Sum Gaps](https://www.luogu.com.cn/problem/AT_arc210_e)

首先 $k$ 的种树显然只有 $\mathcal O(\log_{1.01}\sum A)$，所以不用担心输出不完的情况。显然有一个暴力，每次加入 $a_i$ 时将所有的和的加上 $a_i$ 后和原来的进行归并。

而正解就是基于此的优化，发现若过程中有两个相邻的和 $s_i,s_{i+1}$ 满足 $s_i\le s_{i+1}<1.01\times s_i$，则后面过程中 $1.01\times s_i$ 和下一个数的差只会越来越大（同时因为 $a_i>0$，所以 $1.01\times a_i>a_i$），不可能 $\le 0$，所以此时 $s_i$ 就可以类似做删除处理。考虑记录若干个连续段的最左边和最右边的和以及长度，表示单个连续段内都不可能存在满足条件的和，而相邻连续段的相邻两个位置一定会满足条件，由最开始的证明，显然连续段个数也只有 $\mathcal O(\log_{1.01}\sum A)$。总复杂度为 $\mathcal O(n \log_{1.01}\sum A)$。

## [AT_agc076_a [AGC076A] Hamming-Distant Arrays](https://www.luogu.com.cn/problem/AT_agc076_a)

给求的东西取反，$f(x,y)=n-d(x,y)$，就是求有多少种 $(x_1,\dots x_n)$ 满足存在一个 $y$ 满足 $f(x_i,y)>n$，所以显然有一个必要条件是 $n^2$ 个位置每个位置的最大相同数的和 $\ge n^2+n$，不知道是不是充分的。

写完了，过了，那就是充要的了。复杂度 $\mathcal O(n^5)$。

## [P4948 数列求和](https://www.luogu.com.cn/problem/P4948)

其实是[这里](https://www.luogu.com.cn/article/4jicxaql)的题目，感觉挺牛的，本质上应该还是快速幂，所以写一下。
$$
f_k(n)=\sum_{i=1}^n i^ka^i
$$
当 $n$ 为偶数时，令 $m\gets \frac n2$：$\Large{\color{red}\Diamond}$
$$
f_k(n)=\sum_{i=1}^{m}i^ka^i+\sum_{i=m+1}^n i^ka^i\\
=f_k(m)+a^m\sum_{i=1}^m (i+m)^ka^i\\
=f_k(m)+a^m\sum_{i=1}^m (\sum_{j=0}^k \binom{k}{j}i^jm^{k-j})a^i\\
=f_k(m)+a^m\sum_{j=0}^k\binom{k}{j}m^{k-j}\sum_{i=1}^mi^ja^i\\
=f_k(m)+a^m\sum_{j=0}^k\binom{k}{j}m^{k-j} f_j(m)\\
$$
当 $n$ 为奇数时：
$$
f_k(n)=a+\sum_{i=2}^n i^ka^i\\
=a+a\sum_{i=1}^{n-1}(i+1)^ka^i\\
=a+a\sum_{i=1}^{n-1}\sum_{j=0}^k\binom kj i^ja^i\\
=a+a\sum_{j=0}^k \binom kj f_j(n-1)
$$
现在每次就能花费 $\mathcal O(k^2)$ 的代价将 $n\gets \lfloor \frac n2 \rfloor$，并求出 $\forall i\in [1,k]$ 的 $f_i(n)$，所以一共有 $\log n$ 层，复杂度为 $\mathcal O(k^2\log n)$。

## [P14829 [THUPC 2026 初赛] Asian Soul](https://www.luogu.com.cn/problem/P14829)

感觉对树上 lca 性质还是不太熟练。

将询问挂在线段树上离线，这样即使对每个区间内的所有数操作也只有 $\mathcal O(n\log n)$。要求一个点和多个点的分别的 lca，考虑先对每个线段树区间和插入其中的询问节点建出虚树，此时所有的 $lca(a_k,u)$ 都会在虚树上出现。$\Large\color{red}\Diamond$

接下来只要处理在虚树上求答案了，令 $f_u$ 表示 $u$ 子树内为线段树区间上的点的个数。思考一个点何时会作为 lca 产生贡献，即若一条虚树边 $u \to v$ 满足 $f_u>f_v$，则说明 $v$ 子树和 （$u$ 子树/$v$ 子树内的线段树区间中的点）之间的 lca 都为 $u$，即 $v$ 子树内的询问都会获得 $u$ 的贡献。只要在 $v$ 打上标记下传即可。

总复杂度为 $\mathcal O((n+m+q)\log^2 n)$，瓶颈在给所有区间建虚树。如果用单调栈建虚树，那一次排序可以在线段树上归并处理，复杂度少一个 $\log$。注意要用 $\mathcal O(1)$ lca。

## [Fake Plastic Trees 2](https://qoj.ac/problem/2562)

首先有个比较简单的 dp，令 $f_{u,i,j}$ 表示 $u$ 子树内删了 $i$ 条边，目前 $u$ 连通块的大小为 $j$ 是否可行。

转移就类似树上背包合并，考虑如何优化 $j$ 这一维。

显然 $j$ 的最大值是 $T_u-iL$，最小值是 $T_u-iR$，其中 $T_u$ 表示 $u$ 子树内的 $A$ 和，所以 $j$ 的极差 $\le i(R-L)$。

接着证明对于 $j=x,y,z(x<y<z,z-x<R-L)$ 时，状态 $y$ 可以省略掉$\Large\color{red}\Diamond$，设选择了 $y$ 后最后形成的连通块大小为 $sz\in[l,r]$，则新增了 $sz-y$，分讨后可以证明 $sz-y+x$ 和 $sz-y+z$ 至少一个会 $\in [l,r]$，所以 $y$ 状态可以不计。此时所有记录的递增状态 $j_1,j_2\dots j_s$ 都满足 $j_{i+2}-j_i\ge R-L$，而又$\mathcal O(k)$ 个。所以状态只有 $\mathcal O(nk^2)$ 了，总复杂度为 $\mathcal O(nk^3)$。具体为什么不是 $\mathcal O (nk^4)$，是因为 $f_{u,i}$ 和 $f_{v,j}$ 卷的时候由于树上背包的证明是 $\mathcal O(nk)$ 的，剩余两个卷积是 $\mathcal O(k^2)$ 的。

## [P9266 [PA 2022] Nawiasowe podziały](https://www.luogu.com.cn/problem/P9266)

令 $w(l,r)$ 表示区间 $[l,r]$ 中所有子串中合法括号序列数量，可以证明 $w$ 满足四边形不等式。令 $f_{i,j}$ 表示前 $i$ 个字符分成了 $j$ 段的方案数，则 $f_{i,j}=\min_{k<i}f_{k-1,j-1}+w(k,i)$，所以 $F(x)=f_{n,x}$ 为下凸函数。

套路地，显示使用 wqs 二分，然后需要求 $g_i=\min_{j<i}g_{j-1}+w(j,i)-mid$。因为 $w$ 满足四边形不等式，所以 $g$ 满足决策单调性，但 $w$ 不好直接求，并且 $g$ 求解过程需要在线。

发现 $w(l,r)$ 在做 $l\to l\pm 1$ 或 $r\to r\pm 1$ 时可以直接 $\mathcal O(1)$ 求解，所以可以用 cdq 分治套决策单调性分治解决，复杂度为 $\mathcal O(n\log^3n)$。但是可以使用**LARSCH/简化 LARSCH**（感觉像科技）算法优化至 dp 部分只要 $\mathcal O(n)/\mathcal O(n\log n)$，总复杂度为 $\mathcal O(n\log n/n\log^2n)$。$\Large\color{red}\Diamond$

简化 LARSCH 算法其实类似于 cdq 分治套决策单调性分治，令 $opt_t(x)$ 表示只考虑从 $[1,t]$ 的转移到 $x$ 的最优决策，$opt(x)=opt_{x-1}(x)$。具体过程是定义 $solve(l,r)$ 表示已知 $[1,l)$ 的 $g,opt$ 和 $opt_{l-1}(r)$，求解 $[1,r]$ 的 $g,opt$。

1. 用 $i\in [opt_{l-1},opt_{l-1,r}]$ 求出 $opt_{l-1}(mid)$，因为 $opt_{t}(x)\le opt_{t}(y)\le opt_{t}(z),x<y<z$。
2. 调用 $solve(l,mid)$。
3. 用 $opt(i),i\in [l,mid]$ 和 $opt_{l-1}(r)$ 求出 $opt_{mid}(r)$。
4. 调用 $solve(mid+1,r)$。

注意 1 操作中要移动 $w1$ 的指针，3 操作中要移动 $w2$ 的指针，可以证明整个过程中 $w1$ 和 $w2$ 的指针一共只会移动 $\mathcal O(n\log n)$ 次，若两种操作移动同一对指针会退化到 $\mathcal O(n^2)$ 次。

## [P6782 [Ynoi2008] rplexq](https://www.luogu.com.cn/problem/P6782)

考虑对于每个点的度数和儿子子树大小根号分治，对于度数 $\le B$ 的点的询问考虑暴力枚举每个儿子，$>B$ 的点只有 $\mathcal O(\sqrt n)$ 个再考虑优化。$\Large\color{red}\Diamond$

记 $f(u,l,r)$ 表示 $u$ 子树中编号在 $[l,r]$ 的点的数量，则对于询问 $(l,r,x)$ 答案就是 $\binom{f(x,l,r)}2-\sum_\text{v is son of x}\binom{f(v,l,r)}{2}$。对于 $deg_x\le \sqrt n$，直接枚举 $v$ 后就会形成 $\mathcal O(n\sqrt n)$ 个求子树内编号在 $[l,r]$ 的数量的询问，把子树用 dfs 序拍掉就是 $\mathcal O(n)$ 个点 $\mathcal O(n\sqrt n)$ 次询问二维数点，离线后就是 $\mathcal O(n)$ 次单点加，$\mathcal O(n\sqrt n)$ 次区间求和，可以使用分块内记录块内和块间前缀和做到 $\mathcal O(\sqrt n)-\mathcal O(1)$ 修改/查询，复杂度为 $\mathcal O(n\sqrt n)$。但是空间还是 $\mathcal O(n\sqrt n)$，因为要存下 $\mathcal O(n\sqrt n)$ 个询问，可以发现 $x$ 的儿子的询问区间互不相交，所以可以扫描求完最小的区间后再把下一个加入，空间就是 $\mathcal O(n)$ 的了。

剩下考虑 $deg_x >\sqrt n$ 的怎么做。再次考虑分成两种情况，对于 $x$ 的儿子 $v$ 的子树大小 $>\sqrt n$ 的，$x$ 只会有 $\sqrt n$ 个这种儿子，可以理解为度数只有 $\sqrt n$，所以直接套用上面的做法即可。$\Large\color{red}\Diamond$对于 $v$ 子树大小 $\le \sqrt n$，直接暴力 $\mathcal O(siz_v^2)$ 枚举出所有二元组 $(x,y),x<y$，若满足 $l\le x< y\le r$ 就会贡献答案，这也是一个二维偏序（数点），但是现在有 $\mathcal O(n\sqrt n)$ 对修改，$\mathcal O(m)$ 个询问，使用 $\mathcal O(1)-\mathcal O(\sqrt n)$ 的分块处理即可。这部分的复杂度还是 $\mathcal O(n\sqrt n)$ 的，修改简单处理就可以做到线性空间。

总结一下就是直接对于每个点的儿子子树中前 $\sqrt n$ 大的做 $\mathcal O(\sqrt n) -O(1)$ 的二维数点，对剩余的做 $\mathcal O(1)-\mathcal O(\sqrt n)$ 的二维数点。

## [Omniscient Artist](https://qoj.ac/problem/11109)

首先将二维数点离线扫描线改成对 $a$ 做区间 $\pm 1$，由于 $a_i\le n$，所以 $m$ 的倍数只会有 $\mathcal O(\frac nm)$ 种。考虑以 $B$ 为块长做序列分块，区间加是好做的，由于初始时 $a$ 的差分数组都是 $c_i=0$，每次区间加会让 $c_l\gets c_{l}\pm 1,c_{r+1}\gets c_{r+1}\mp 1$，只会有 $\mathcal O(n)$ 次区间加，所以 $\sum |c_i|\le 2n$，所以每个块内的 $\max-\min$ 的和是 $\mathcal O(n)$ 级别的。询问时对每个块内枚举 $m$ 的倍数并查询出现次数即可，$m$ 的倍数一共只会有 $\mathcal O(\frac {\max-\min} m)$ 个，所以查询复杂度为 $\mathcal O(\frac n m)$，区间加复杂度为 $\mathcal O(\frac nB+B)$，平衡后整体复杂度为 $\mathcal O(n\sqrt n)$。注意重构的时候应该对每个块内的数删除而不是 $\mathcal O(\max-\min)$ 的清空，否则复杂度会退化到 $\mathcal O(n^2)$。

## [P14836 [THUPC 2026 初赛] 能量分配](https://www.luogu.com.cn/problem/P14836)

这也太困难了。

$p\gets 317$，固定 $c$ 数组后，分配宝石的方案数就是 $\binom {n}{c_1,c_2,\dots c_m}$，由 Lucas 定理的过程可以得到 $\binom{n}{c_1,c_2\dots c_n}\not\equiv 0(\bmod p)$ 的必要条件是 $\forall k,\sum bit_k(c_i)=bit_k(n)$，其中 $bit_k(x)$ 表示 $x$ 在 $p$ 进制下的第 $k$ 位，即需要满足 $\sum c_i$ 求和过程中不能在 $p$ 进制下进位。$\Large\color{red}\Diamond$

先考虑 $n<p$，此时就只有一层。考虑直接枚举排序后 $c_i$ 之间的偏序关系，即相邻的两个位置之间的关系是 ``<`` 还是 ``=``，一共只有 $\mathcal O(2^{m-1})$ 种。然后在确定相对偏序关系后，$\binom n {c_1,c_2\dots c_m}$ 的贡献和 $A,B$ 造成的贡献就独立了，分别考虑。$\Large\color{red}\Diamond$

先考虑求出 $A,B$ 的贡献。令 $dp_{S1,S2}$ 表示已经填入了集合 $S1$ 的选手，前面的偏序关系是 $S2$ 的贡献和，转移考虑枚举一个新的极长的相等段，选手编号集合为 $S3$，然后可以提前预处理出 $w_{S1,S3}$ 造成的贡献进行转移。复杂度为 $\mathcal O(\sum_{i=1}^m \binom{m}{i}\times 2^{i-1}\times 2^{m-i})=\mathcal O(4^m)$。

然后考虑求 $\binom{n}{c_1,c_2\dots c_m}$ 的贡献。由于 $c_i$ 的顺序不影响，所以这里只计算 $c$ 有序时的贡献和。令 $f_{i,j,S}$ 表示前 $i$ 个数和为 $j$，相对偏序关系为 $S$ 的总贡献，转移时讨论 $c_{i+1}$ 与 $c_i$ 的偏序关系。复杂度为 $\mathcal O(\sum_{i=1}^m 2^{i-1}p^2)=\mathcal O(2^mp^2)$。

拓展到 $n\ge p$，现在一共有 $\log_p n$ 层。类似上面的做法，将两种贡献分开计算，$A,B$ 造成的贡献直接 $\mathcal O(4^m)$ 预处理即可。考虑如何适应层数对偏序关系的影响。从高位到低位，原本相等的一段区间可能会分裂成几个有序的区间，考虑用 dp 记录这个过程。令 $f_{i,S}$ 表示到达 $i$ 层时的偏序关系为 $S$ 的方案数（$bit_2(S)=[c_i \ne c_{i+1}]$），考虑从 $f_{i,S}$ 转移到 $f_{i-1,S'}$（$S\sube S'$） 的转移系数 $g_{S,S',bit_{i-1}(n)}$，实际上 $g_{S,S',i}$ 可以将这个过程分成 $S$ 的每个 0 区间（等价类）变成 $S'$ 对应区间后对 $\sum bit_k(c)$ 维做卷积得来的。具体的，令 $h_{S,i}$ 表示相对偏序关系为 $S$，$\sum c=i$ 的方案数，则 $(S,S')$ 的转移可以通过 $h_{S,i}$ 的第二维 $i$ 的和卷积得来。$h$ 的转移和上一段落中的类似，$g$ 的状态中有许多可以通过记忆化解决$\Large\color{red}\Diamond$，比如下图中三个绿色段的相对顺序不会影响 $g$ 的值，所以可以将其排序后存入``map``进行记忆化。令``map``的大小为 $F(m)$，则预处理 $g$ 的复杂度为 $\mathcal O(F(m)p^2)$。若没有记忆化，$F(m)=3^m$（即枚举 $S\sube S'$），但是显然记忆化后会大幅减少状态数，实际上 $\color{red}F(12)=17547$。对于每次询问跑 $f$ 转移后记得最后与前面算的 $A,B$ 造成的贡献 $dp$ 拼起来。总复杂度为 $\mathcal O(4^m+F(m)p^2+q3^m\log_p n)$。

 ![](能量分配 配图.png)

倒闭了，写不了一点，还要卡常，下播了。upd. 改完了。

## [最小乘积](https://qoj.ac/problem/12170)

由于 $A,B$ 很小，所以考虑直接枚举其中一个。令 $f_{u,i}$ 表示到 $u$ 时经过的 $\sum a=i$ 的最小的 $\sum b$，转移不难发现由于 $a_i>0$，所以这个转移是分层图，可以从小到大枚举 $i$ 后枚举每条边转移，复杂度为 $\mathcal O((n+m)mV)$，若没有发现分层图直接跑 dijkstra 会多一只 log 无法通过。

## [CF280D k-Maximum Subsequence Sum](https://www.luogu.com.cn/problem/CF280D)

由于 $k$ 和 $\sum k$ 很小，可以考虑模拟费用流。首先有个显然的费用流模型，对每个 $i$ 连边 $(S,i,1,0),(i,i+1,1,a_i),(i,T,1,0)$，还有 $k$ 的限制所以答案就是在这个图中增广 $k$ 次的最大花费。每次增广就是找到当前的最大区间和，然后将经过的链上的边反向并将费用变成相反数 $\Large\color{red}\Diamond$。这个过程可以使用线段树模拟，就是做最大子段和还有区间取相反数，复杂度为 $\mathcal O(q\log n+\sum kn\log n)$。

其实也可以从反悔贪心的方面思考刚刚的过程，就是先取当前和最大的区间 $[l,r]$，然后反悔再选取 $[l',r'] \sube [l,r]$ 并减去 $sum[l',r']$，这样区间就断成了 $[l,l')$ 和 $(r',r]$，完成了反悔操作，也就对应模拟费用流的反向弧的操作。

## [Poor Students](https://qoj.ac/contest/1356/problem/7185)

依旧是模拟费用流。首先这显然是一个带权二分图匹配问题，考虑建立费用流后如何优化。

如果手玩这个退流和走反向弧的过程不难发现每次实际上就是在右边选出一个序列 $p_1,p_2,\dots p_m$ 满足 $p[1,m)$ 都曾经被流满了（匹配完 $c_{p_i}$ 个左部点了），然后不断进行退流操作（即走反向弧）直到最后走到了一个没有流满的点 $p_m$ 后走到 $T$，下图红色的边就体现了退流的过程。由于 $m\le k\le 10$，所以考虑对右部点做一些本质的操作。$\Large\color{red}\Diamond$实际上每次寻找最短路时可以看作从 $p_i$ 走到 $p_{i+1}$，距离就是 $p_i\to x \to p_{i+1}$ 两条边的距离之和，这个可以提前预处理出任意两个右部点的 $x$ 的集合处理，所以就是已知任意两个右部点之间的距离求一条最短路 $rs\rightsquigarrow rt$ 且保证 $rt$ 没有流满。直接 $\mathcal O(k^3)$ 跑 floyd 即可，由于要模拟退流，所以要记录转移点来复原路径。复杂度为 $\mathcal O(nk^3+nk^2\log n)$。

![](Poor Students 配图.png)

## [Cool Problem](https://codeforces.com/contest/2187/problem/D)

题解做法简直抽象。

将两个操作变得更相似，可以发现
$$
r_i=0:c_i-\frac{x+y}2=c_{i-1}+\frac{x-y}2 \\
r_i=1:c_i-\frac{x+y}2=-c_{i-1}-\frac{x-y}2 \Large\color{red}\Diamond
$$
所以任意操作后都有 $(c_i-\frac{x+y}2)^2=(c_{i-1}+\frac {x-y}2)^2$，拆开得到 $c_i^2-c_{i-1}^2-(x+y)c_i-(x-y)c_{i-1}+xy=0$。对于 $i \in[1,n]$ 求和后就得到了 $c_n^2-yc_n+nxy=x\sum(c_i+c_{i+1})$，由于 $f(r)=\sum c-i$，所以 $f(r)=\frac{c_n^2+(x-y)c_n+nxy}{2x}$，所以知道 $c_n$ 就能直接求出 $f(r)$ 了。由于每次操作二都会将之前的 $y$ 的系数 $\times(-1)+1$，由归纳法可得 $y$ 的系数只会是 $0/1$，所以只会有至多 $2n$ 种 $c_n$，求解直接设 $f_{i,j\in\{0,1\},k}$ 表示前 $i$ 个数 $y$ 的系数为 $j$，$x$ 的系数为 $k$ 是否可行，转移用 bitset 优化，复杂度 $\mathcal O(\frac{n^2}\omega)$，要滚动数组。

## [CF1098F Ж-function](https://www.luogu.com.cn/problem/CF1098F)

*3500。这种题写还是算了，太恐怖了一点。$\operatorname{Ж}(l,r)\to f(l,r)$
$$
f(l,r)=\sum_{i=l}^r|\operatorname{lcp}(s[l,r],s[i,r])|=\sum_{i=l}^r|\min(\operatorname{lcp}(s[l,n],s[i,n]),r-i+1)|
$$
由于 $\operatorname{lcp}(s[i,n],s[j,n])=\min_{k=rk_{i}+1}^{rk_{j}}ht_k$，所以考虑将 $i\in [l,r]$ 分成 $rk_i< rk_l$ 和 $rk_i>rk_l$ 和 $i=l$，然后将询问挂在 $rk_l$ 上。后面其实就是数据结构的事了。

$rk_i>rk_l$ 和 $rk_i<rk_l$ 是本质相同的，这里只讨论前者。区间最小值的拆贡献考虑离线后对 $rk$ 分治，令 $suf_i=\min_{j=i}^{mid} ht_j$，$pre_i=\min_{j=mid}^i ht_j$。从 $mid\to L$ 扫描线，当遇到询问 $[l,r]$ 时，令 $mn=suf_{rk_l}$，满足$\forall mid<i\le p,pre_i\ge mn$ 的 $p$ 最大，$mn$ 单调不降，$pre$ 单调不降，因此 $p$ 单调不降，考虑拆开贡献成 $\sum_{i=mid+1}^p [sa_i\in [l,r]]\min(mn,r-sa_i+1)+\sum_{i=p+1}^R[sa_i\in [l,r]\min(pre_i,r-sa_i+1)]$。前半部分是讨论对 $(sa_i,i)$ 的二维数点，扫 $p$ 的时候加入树状数组即可。后半部分当 $pre_i\le r-sa_i+1$ 时还需要满足 $sa_i\in [l,r],i\in [p+1,R]$，所以是对 $(i,sa_i,sa_i+pre_i)$ 的三维数点，考虑优化。题解做法是将限制拆成 $mn\le r-sa_i+1$ 加上 $pre_i\le r-sa_i+1< mn$，因为 $pre_i< mn$。第一个限制是二维数点，乍一看第二个限制还是三维数点，但是由于对于 $i\in (mid,p]$ 的都满足 $pre_i\ge mn$，所以就忽略掉了对 $i\in [p+1,R]$ 的限制也不会多算，所以就改成了二维数点。$\Large\color{red}\Diamond$其他的讨论都类似就算了。

复杂度为 $\mathcal O((n+q)\log^2n)$。

## [最短路径](https://qoj.ac/problem/9903)

由于每次询问只会删除一个点，所以可以考虑缺一分治。$\Large\color{red}\Diamond$同时由于 $n\le 300$，所以考虑用 floyd 做最短路。具体的令 $solve(l,r)$ 表示进入时 $[1,l)$ 和 $(r,n]$ 都已经加入图中并处理完最短路，则答案直接离线后在 $solve(p_i,p_i)$ 中求即可。每次加入一段区间 $[l,r]$ 只要将其设为 floyd 中的转移点即可，因为不是它作为转移点的在之前已经处理过了，大概过程就是 $i\in[l,r],j\in [1,n],k\in [1,n] :f_{j,k}\gets f_{j,i}+f_{j,k}$，这个过程单次复杂度为 $\mathcal O(n^2siz)$，由于在分治过程中 $\sum siz=\mathcal O(n\log n)$，所以总复杂度为 $\mathcal O(n^3\log n+q)$。由于 floyd 无法删除，撤销只能记录当时的最短路数组后拷贝，所以空间复杂度是 $\mathcal O(n^3)$。

## [No Rest for the Wicked](https://qoj.ac/contest/697/problem/1878)

每次新到达的点 $x$ 都要满足 $t_x\ge maxc$，所以考虑从小到大枚举 $maxc$ 并转移能到达的最大 $s$。若 $t_i<maxc$ 则现在无法被加入和到达，直接全部删除不考虑。剩余的若 $c_i\le maxc$ 则当前点可以转移到其他点也可以被转移到，将其称为 1 类点，否则只能被其他点到达转移称为 2 类点。若一条边连接了两个 1 类点，则可以互相转移，令 $bel(x)$ 为 $x$ 所在的极大 1 类点连通块。而 1 类点连向 2 类点的边只能单向转移，并且 2 类点当前无法再向外转移，所以最后的图就是若干个 1 类连通块像菊花一样向外连若干条单向边。

对于一条边 $(u,v)$ 会在 $maxc\in [\max(c_u,c_v),\min(t_u,t_v)]$ 时称为 1 类边，在 $maxc\in [c_u,\min(t_u,c_v-1)]$ 时成为 2 类边，注意反向边也要建。考虑如何顺着这个图进行转移，由于连通块之间的信息是相同的，而且不好撤销，而一条边会在一个区间出现，所以套路地使用线段树分治，1 类连通块用可撤销并查集维护。复杂度为 $\mathcal O(n\log^2n)$。

其实到这一步时可以求出每个时刻每个连通块的答案，但是还无法将连通块的贡献传到每个点。优化可以发现对于一条无向边 $(u,v)$，其产生的 1 类边时间一定完全晚于 2 类边时间，所以需要在线段树上倒着扫 $maxc$，否则就会导致先扫到的 2 类点在被删掉后更新 1 类连通块。

## [CF997C Sky Full of Stars](https://www.luogu.com.cn/problem/CF997C)

容斥一下，方案数为
$$
ans = \sum_{i+j>0}(-1)^{i+j-1}\binom{n}{i}\binom{n}{j}f(i,j)
$$
其中 $f(i,j)$ 表示至少有 $i$ 列同色和 $j$ 行同色的方案数，则 $f(0,i)=f(i,0)=3^{i+n(n-i)}$，$f(i,j)=3^{n^2-(i+j)n+ij+1}$。$i=0$ 和 $j=0$ 分开讨论，剩下是 $i,j>0$。
$$
\sum_{i,j>0}(-1)^{i+j-1}\binom ni\binom nj3^{n^2-(i+j)n+ij+1} \\
=3^{n^2+1}\sum_{i=1}^n (-1)^{i-1}3^{-in}\binom ni\sum_{j=1}^n(-1)^j\binom nj 3^{-jn+ij}\\
=-3^{n^2+1}\sum_{i=1}^n (-1)^{i}3^{-in}\binom ni\sum_{j=1}^n\binom nj (-(3^{-n+i}))^j
$$
看到 $j$ 式子的很像二项式定义，考虑
$$
(-(3^{-n+i})+1)^n=\sum_{j=0}^n\binom nj(-3^{-n+i})^j \\
\sum_{j=1}^n\binom nj (-(3^{-n+i}))^j=(-(3^{-n+i})+1)^n-1
$$
然后把式子带回去就可以 $\mathcal O(n\log n)$ 做完了。

## [CF1716F Bags with Balls](https://www.luogu.com.cn/problem/CF1716F)

$$
\begin{align}
\sum F^k &= \sum_{i=0}^k{k\brace i}i!\sum \binom{F}{i} \\
&= \sum_{i=0}^k{k\brace i}i!\binom{n}{i}\lceil\frac{m}2\rceil^i m^{n-i}
\end{align}
$$

第二个式子是因为考虑 $\binom Fi$ 的组合意义就是在所有的奇数编号球中选择 $i$ 个的方案数，所以可以先钦定被选择的 $i$ 个位置选奇数，然后剩下的随便选。代码实现时将 $i!\binom ni$ 转成了 $n^{\underline i}$ 求解，复杂度 $\mathcal O(Tk^2)$。枚举 $i$ 时动态维护 $n^{\underline i}$ 做到 $\mathcal O(Tk)$。

## [P12999 [GCJ 2022 #3] Mascot Maze](https://www.luogu.com.cn/problem/P12999)

神秘困难图染色构造题，这个 $|S|=13$ 甚至有用。

先把限制 $ans_u\neq ans_v$ 的边 $(u,v)$ 先建出来，无向边数只有 $6n$ 条，若有自环则显然无解。考虑稀疏图的性质，由于有向边数只有 $12n$，而一共只有 $n$ 个点，由鸽巢原理得至少有一个点的度数 $\le 12\Large\color{red}\Diamond$，否则至少会有 $13n$ 条有向边，矛盾。然后删除一个点后一定还有至少一个点度数 $\le 12$，所以可以考虑做一个拓扑排序类似的事情。取到拓扑序后倒着染色，每个点此时至多会有 $12$ 条出度，但是有 $13$ 种颜色，所以可以染上。

## [P7220 [JOISC 2020] 掃除](https://www.luogu.com.cn/problem/P7220)

考虑将一个在二维上的点 $(x,y)$ 转化成一维上的一段区间 $[x,n-y]$ $\Large\color{red}\Diamond$，由于所有的点在直角三角形中所以一定有 $x+y\le n$。然后发现 H 操作就是将 $r\ge n-L,l\gets \max(l,n-L)$，V 操作就是将 $l\le L,r\gets \min(r,L)$。考虑建立猫树（线段树）后将所有区间挂上去，下面只考虑操作 H 对于 $r\ge x,l\gets \max(l,x)$。

若 $x\le mid$，则需要将所有区间按照 $l$ 排序后取一段前缀推平成 $x$，直接维护 $l$ 相同的连续段即可。

若 $x>mid$，则所有当前线段树节点上的区间都会被移动到右儿子，这个过程对于每个区间显然只会出现 $\mathcal O(\log n)$ 次，所以直接暴力将当前节点的区间取出后全部重新插入即可。

维护这个过程应该直接对每个线段树节点都使用堆和 odt 维护就可以了。总复杂度为 $\mathcal O((n+q)\log^2n)$，难写+难调+速度慢+空间大。

## [P12962 [GCJ Farewell Round #4] Genetic Sequences](https://www.luogu.com.cn/problem/P12962)

题面太臭了，其实就是要求：
$$
n\gets |A|,m\gets |B|\\
\max_{i=1}^P \operatorname{LCP}(A[i,P],B[m-S+1,m]) \\
=\max_{i=1}^P \min(P-i+1,\operatorname{LCP}(A[i,n],B[m-S+1,m])) \\
$$
求两个串后缀的 LCP，套路地对串 ``A+#+B`` 做 SA$\Large\color{red}\Diamond$，则答案就变成了
$$
\max_{i=1}^P\min(P-i+1,\min_{j=rk_i+1}^{rk_{len-S+1}} ht_j)
$$
后面的 $\min$ 实际上是上下界可能会相反，大概意思知道就行了。

这个区间 $\min$ 还是不太好求，考虑将 $rk_i$ 排序后建立对应的 $ht$ 的小根笛卡尔树，然后就将区间 $\min$ 转化成求笛卡尔树上的 LCA$\Large\color{red}\Diamond$。考虑枚举 $rk_{len-Q+1}$ 的 LCA 为 $u$，则对答案贡献 $\min(P-mn_u+1,ht_u)$，其中 $mn_u$ 表示 $u$ 子树内的编号最小值。发现 $u$ 越往上 $mn_u$ 越小，$P-mn_u+1$ 越大，$ht_u$ 越小，所以可以在链上二分求解两个函数交点就是答案。复杂度 $\mathcal O(\sum (n+m+q)\log (n+m))$。

## [CF1874E Jellyfish and Hack](https://www.luogu.com.cn/problem/CF1874E)

令 $f_{i,j}$ 表示长度为 $i$ 的排列，当前的权值和为 $j$ 的方案数。
$$
f_{i,j}=\sum_{k=0}^{i-1}\sum_{l=0}^{j-i} \binom{i-1}k f_{k,l}f_{i-1-k,j-i-l}
$$
由于第二维的大小为 $\mathcal O(n^2)$ 的，所有直接做复杂度是 $\mathcal O(n^6)$，即使用 FFT 也只能做到 $\mathcal O(n^4\log n)$。

看到第二维是卷积形式，考虑对序列 $f_i$ 做生成函数$\Large\color{red}\Diamond$。令 $F_i(x)=\sum_{j=i}^{n^2}f_{i,j} x^j$，则转移式可以写成
$$
F_i=\sum_{k=0}^{i-1}\binom{i-1}k x^i F_kF_{i-1-k}
$$
由于 $F_i$ 是一个至多 $n^2$ 次的多项式，所以只要求出 $\mathcal O(n^2)$ 个点值后拉差即可复原系数。$\Large\color{red}\Diamond$对于每个 $i$ 维护 $g_{i,j}=F_i(j)$，卷积时直接对位乘即可，最后要给 $n^2$ 次多项式做拉差复杂度为 $\mathcal O((n^2)^2)=\mathcal O(n^4)$。

这题能对 FFT 加速的主要原因是需要做 $\mathcal O(n^2)$ 次卷积，若只维护点值单次做卷积的复杂度就是 $\mathcal O(n^2)$，最后在拉差还原时也是 $\mathcal O(n^4)$ 的。若只做一次，拉差还原部分就已经是 $\mathcal O(n^2)$ 的，不如暴力。

#### 已知 $k$ 次多项式的 $k+1$ 个点值，$\mathcal O(k^2)$还原多项式。

将拉格朗日插值式子展开：
$$
\begin{align}
f(x)&=\sum_if(x_i)\prod_{j\neq i}\frac{x-x_j}{x_i-x_j} \\
&=\sum_{i}\frac{f(x_i)}{\prod_{j\neq i}(x_i-x_j)} \prod_{j\neq i} (x-x_j) \\
\end{align}
$$
前半部分的值是已知的，直接 $\mathcal O(k^2)$ 枚举 $i,j$ 求即可，后半部分就是多个一次函数相乘，直接每次暴力展开是 $\mathcal O(k^3)$ 的，但是可以写成 $\frac{\prod(x-x_j)}{x-x_i}$，然后预处理 $\prod(x-x_i)$ 的系数后每次做大除法即可，复杂度为 $\mathcal O(k^2)$。

## [2026 省选模拟赛 Day 17 #B. 追忆](https://newoj.daimayuan.top/p/4775?tid=69a5374fbff5d4356a21b04f)

假的追忆，但更困难了。

首先这个题的空间是开不下 $\mathcal O(n^2)$ 的 bitset 的，但是由于只需要求可达的集合大小，所以可以类似将 $[1,n]$ 按照 $B$ 分块$\Large\color{red}\Diamond$，每次只求到达一个块内元素的可达性，空间为 $\mathcal O(nB)$，时间为 $\mathcal O(\frac{n^2}\omega+\frac{n^2}B)$，只要将 $B$ 开到刚好卡到空间限制就基本不会对时间复杂度有影响。

其实这个矩阵内的点是假的，就算开到**空间内的点/k 维偏序**也只是常数上的区别，因为都已经有 $\mathcal O(\frac{n^2}\omega)$ 的复杂度了就不用考虑怎么拆多维偏序了，直接对于每一维求出在询问区间内的点的集合，然后全部 ``&`` 起来就是满足的集合。需要求满足的点的可达集合，就可以先对每个点 $u$ 记录 $bs_{u,i}$ 表示 $u$ 是否在第 $i$ 个询问中，然后转移时跑拓扑排序，将 $u$ 可达的点 $t$ 都做 $bs_t\gets bs_t \vee bs_u$ 表示 $t$ 会贡献到询问 $i$ $\Large\color{red}\Diamond$。

现在有一个 $n\times q$ 的 ``bitset`` 记录了 $bs_{u,i}$ 表示 $u$ 是否会贡献到询问 $i$，若把其当成一个 01 矩阵，则第 $i$ 个询问的答案就是第 $i$ 列的和。考虑 [诡异操作](https://uoj.ac/problem/671) 的 trick，记录 $cnt_{i,j}$ 表示第 $i$ 列的和的第 $j$ 个二进制位，然后将 $cnt$ 转置后就变成了一个 $\log_2n \times q$ 的矩阵，每次做对两个矩阵的每一行依次做二进制加法，单次复杂度为 $\mathcal O(\frac{q\log n}\omega)$，做 $n$ 次加法复杂度就是 $\mathcal O(\frac{nq\log n}{\omega})$。但是可以使用分治将 $\log n$ 进一步减小，具体的，每次递归求解 $[l,mid]$ 和 $[mid+1,r]$ 的和，再做一次加法，复杂度 $T(n)=2T(\frac n2)+\mathcal O(\frac{q\log n}\omega)$，由主定理可以得到 $T(n)=\mathcal O(\frac{nq}\omega)$，虽然都是做 $n-1$ 次加法，但分治可以将 $\log n$ 不卡满，所以复杂度少一个 $\log$。总复杂度为 $\mathcal O(\frac{nq}\omega)$，需要使用第一段的卡空间方法，将 $q$ 次询问分块处理，平衡后时间复杂度做到 $\mathcal O(\frac{nq}\omega+qB)$，空间 $\mathcal O(\frac{nB}\omega)$。

