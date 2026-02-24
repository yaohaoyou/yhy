$$
\def\opn#1{\operatorname{#1}}
\def\mex{\opn{mex}}
\def\O{\mathcal{O}}
$$

### [离散对数是个谎言](http://www.gdfzoj.com:23380/contest/858/problem/8590)

正难则反，将函数带入后逆着求。

$\$

2023.10.18

### [/qd](http://www.gdfzoj.com:23380/contest/870/problem/6665)

正难则反，删点很难，将询问离线，改成往图里加点。

2023.10.31

### [CF1151E Number of Components](https://www.luogu.com.cn/problem/CF1151E)

一颗森林的连通块数 = 节点数 - 边数。

分开统计节点数和边数。

### [P3545 [POI2012] HUR-Warehouse Store](https://www.luogu.com.cn/problem/P3545)

发现普通贪心和 DP 都很难做的时候，可以尝试反悔贪心，因为这道是板子。

### [AT_arc137_d [ARC137D] Prefix XORs](https://www.luogu.com.cn/problem/AT_arc137_d)

由 Lucas 定理得，$\binom{n}{m} \bmod 2 = 1$ 当且仅当 $\text{n bitand m = m}$。

### [P4859 已经没有什么好害怕的了](https://www.luogu.com.cn/problem/P4859) & [二项式反演（1）](https://www.luogu.com.cn/blog/yaohaoyou/math-formulas)

看到 **恰好** 的组合题目可以用二项式反演转化成 **至少** 或 **至多**。

### [P3349 [ZJOI2016] 小星星](https://www.luogu.com.cn/problem/P3349)

求一一对应的映射方案数数可以转化成枚举将每个数映射到 $[1,n]$ 的子集，在使用容斥原理算出映射后刚好为 $[1,n]$ 的答案。

### [P4652 [CEOI2017] One-Way Streets](https://www.luogu.com.cn/problem/P4652)

在有向无环图上跑出一棵 **dfs 搜索树**（或是生成树），将边分成**树边**或非树边（返祖边），可以解决许多连通性相关的问题。

### 暂时找不到代表性题目了
将**二分图**和**网格图**相互转换。

### [P10166 [DTCPC 2024] 环](https://www.luogu.com.cn/problem/P10166)
将 **有向图无环无重边，$m \ge n-1$** 转化成 **连通图DAG**。

### [AT_agc030_d [AGC030D] Inversion Sum](https://www.luogu.com.cn/problem/AT_agc030_d)
由期望的线性性将 **总和** 转化成 **期望 × 总方案数**，再将 **和的期望** 转化为 **期望的和**

### [AT_abc351_e [ABC351E] Jump Distance Sum](https://www.luogu.com.cn/problem/AT_abc351_e)
将切比雪夫距离转换成曼哈顿距离。

$\max(|x_1-x_2|,|y_1-y_2|)=|\dfrac{x_1+y_1}{2}-\dfrac{x_2+y_2}{2}|+|\dfrac{x_1-y_1}{2}-\dfrac{x_2-y_2}{2}|$，即将点 $(x,y)$ 变成 $(\dfrac{x+y}{2},\dfrac{x-y}{2})$。

### [PKUSC 2024 D1T1 回文路径](https://qoj.ac/contest/1659/problem/8668)
判断 $s[l,r]$ 是否为回文串时可以二分长度 $k$，找到最大的满足 $s[l,l+k-1] = rev(s[r-k+1,r])$，若 $[l,l+k-1]$ 与 $[r-k+1,r]$ 有交集或 $s[l+k,r-k]$ 为回文串，则 $s[l,r]$ 为回文串，反之则不是。

### [2024 NOI广东集训 D1T3](http://www.gdfzoj.com:23380/contest/975/problem/10011)
判断两个字符串的大小可以使用哈希，二分最长的 LCP，再比较下一位的大小。哈希的维护可以使用主席树（线段树）。

### [P2480 [SDOI2010] 古代猪文](https://www.luogu.com.cn/problem/P2480)
求 $ans=\binom{n}{m} \bmod p$。当 $p$ 很大时，可以将 $p$ 质因数分解。令 $p=a_1^{k_1} \times a_2^{k_2} ...\times a_l^{k_l}$，则可以先求出 $\binom{n}{m} \bmod a_i^{k_i}$ 分别为 $b_i$，然后再使用 CRT（EXCRT）求出 $ans$。

$$
\begin{cases}
ans \equiv b_1 (\bmod a_1^{k_1}) \\
ans \equiv b_2 (\bmod a_2^{k_2}) \\
...\\
ans \equiv b_m (\bmod a_m^{k_m}) \\
\end{cases}
$$

### [CF1305F Kuroni and the Punishment](https://www.luogu.com.cn/problem/CF1305F)
当数列 $a$ 的众数出现次数大于 $\dfrac{n}{2}$ 时，~~学长~~叫他绝对众数。当你随机 $k$ 次时，无法随机到众数的概率为 $\dfrac{1}{2^k}$。

### [NOIP 模拟赛4 T1 矩阵](http://goj.wiki/d/Union2024/p/P1017)
做数论题记得尝试使用筛法预处理优化，特别是积性函数。此题中是求 $i^n$，$n$ 固定，$i\in [1,k]$，使用线性筛可以做到 $\O(k)$ 预处理。

PS：对于指数固定可以使用线性筛求积性函数，对于底数固定可以使用 $\O(\sqrt {mod})-\O(1)$ 光速幂（bsgs） 优化。

### [NOIP 模拟赛11 T2 笛卡尔树](http://goj.wiki/d/Union2024/p/P1042)
序列中 $a_i$ 最右的 $a_l>a_i$ 和最左的 $a_r>a_i$ 满足 $[a_{l+1},a_{r-1}]$ 在笛卡尔树上就是 $i$ 的子树。

### [NOIP 模拟赛12 T2 括号串](https://www.luogu.com.cn/problem/CF1264D2)

[范德蒙德卷积](https://oi-wiki.org/math/combinatorics/vandermonde-convolution/)（其实就是组合意义）

还有	，就是 
$$
\binom{a}{f(i)-b}f(i)=\binom{a}{f(i)-b}[f(i)-b+b]=a\times\binom{a-1}{f(i)-b-1}+b\binom{a}{f(i)-b}
$$

### [NOIP 模拟赛39 T2 洄游](http://goj.wiki/d/Union2024/p/P1166)
求多边形面积时可以进行定向，从一点走一圈走回原点，路途中向左走时贡献为 $-x$，向右为 $x$，最后多边形面积即为贡献和。

### [NOIP 模拟赛39 T3 城市](http://goj.wiki/d/Union2024/p/P1167)
记得在给答案取 min/max 时将 res 打表出来，因为这题答案可三分。

### [NOIP 模拟赛44 T2 命运](http://goj.wiki/d/Union2024/p/P1890)
他们说这是``上角标求和``？

$$
\sum_{i=x}^n\binom{i}{x}=\binom{n+1}{x+1}
$$
同理，即可求出 $\sum_{i=l}^{r}\binom{i}{x}=\binom{r+1}{x+1}-\binom{l}{x+1}$。

### [AT_abc221_g Jumping sequence](https://www.luogu.com.cn/problem/AT_abc221_g)
tricky 好题？

对于一个二维坐标 $(x,y)$ 的横向或纵向移动，可以将其变为 $(x+y,x-y)$ 后，两维的移动就变得相互独立了，也可以进一步转化为切比雪夫距离。

$b_1\times a_1 + b_2 \times a_2 + ... + b_n \times a_n = x$，其中 $a_i$ 和 $x$ 为定值，$b_i$ 为 $\pm 1$，可以两侧同时 $+\sum a_i$ 再 $\div 2$，变为 $a_{p_1}+a_{p_2}+...+a_{p_k} = \frac{x+\sum a_i}2$，可以使用 01 背包求一组可行解。

### [CF1368E Ski Accidents](https://www.luogu.com.cn/problem/CF1368E)
$\frac47=\frac{2^2}{2^0+2^1+2^2}$。

### [Pjudge NOIP Round #8 偷塔](https://pjudge.ac/contest/1847/problem/21862)
求极差最大可以转化为选择一个数 +，和选择一个数 -，最优时必然是选择最大数 +，最小数 -。可以使用 dp 维护状态 0/1/2/3 表示是否选过数 +，是否选过数 -。

### [AT_abc242_h Random Painting](https://www.luogu.com.cn/problem/AT_abc242_h)
min-max 容斥：
$$
ans=E(\max_{i=1}^n a_i)=E(\sum_{S\in\{1,2,\dots n\}} (-1)^{|S|-1} \min_{j\in S} a_{S_j})
$$
$a_i$ 表示第 $i$ 个位置被覆盖的时刻。

期望的线性性：
$$
ans=E(\sum_{S\in\{1,2,\dots n\}} (-1)^{|S|-1} \min_{j\in S} a_{S_j})=\sum_{S\in\{1,2,\dots n\}} (-1)^{|S|-1} E(\min_{j\in S} a_{S_j})
$$

### [PKUWC2020 火山哥与集合](http://www.gdfzoj.com:23380/problem/2011)

[题解](http://www.gdfzoj.com:23380/download.php?type=solution-pdf&id=2013)

由期望的线性性，和剩下的集合只和其集合大小相关。
$$
ans=\sum_A \dfrac{(\max(A)-\min(A))^2}{P(A)}=\sum_{S} (\max(S)-\min(S))^2\times p(S,k)=\sum_{i=1}^n h(i)g(i,k)
$$
$p(S,i)$ 表示合并得只剩下 $i$ 个集合时，$S$ 是其中一个的概率。

$h(i)$ 表示所有大小为 $i$ 的集合的 $(\max(S)-\min(S))^2$ 的和。

$g(i,k)$ 表示合并得只剩下 $k$ 个集合时，其中有一个集合大小为 $i$ 的概率。

> 这一步可以将枚举集合转换为枚举 $\max(S)$ 和 $\min(S)$ 后计算集合方案数和出现概率。（从指数级暴力转变成多项式做法）

### [PKUWC2025 D2T1 网友小 Z 的树](https://qoj.ac/contest/1896/problem/9678)
记住一种比较方便求直径的方式为先找出距离 $1$ 最远的点 $x$，再找距离 $x$ 最远的点 $y$，此时 $x$ 和 $y$ 即为直径，满足 $dis(x,y)$ 最大。

设 $dis'(x,y,z)=dis(x,y)+dis(x,z)+dis(y,z)$。

同理（~~不会证~~），找到使 $dis'(1,2,x)$ 最大的点 $x$，再找 $dis'(1,x,y)$ 最大的点 $y$，最后找 $dis'(x,y,z)$ 最大的点 $z$。此时 $dis'(x,y,z)$ 为全图中 dis' 最大的三点。

$x,y,z$ 中的两点此时必刚好为直径两端点。

### [CF1481F AB tree](https://www.luogu.com.cn/problem/CF1481F)
求可行性 01 背包及构造，空间线性，时间 $\O(\frac{nV+V^2}{\omega})$。

在直接用 bitset 做的时候，维护当前容量是从哪里转移的，实际上 ``tmp=dp^(dp|(dp<<w[i]))``，即转移前后相异或的 bitset 中为 1 的位就是从 ``w[i]`` 转移的。直接遍历 ``tmp`` 的每一位，因为每种容量只会被遍历 1 次，单次最劣复杂度为 $\O(\frac{V}{\omega})$，故求构造总复杂度为 $\O(\frac{V^2}{\omega})$。常数可能较大。

设 $\sum w_i=S$，则共有 $\O(\sqrt S)$ 种不同的 $w_i$，如果改成做多重背包就能将 $n$ 降到 $\sqrt S$，直接二进制优化复杂度为 $\O(\sqrt S\times V \times \log_2n)$，但实际上好像是 $\O(\sqrt S\times V)$。

### [The 3rd Universal Cup. Stage 30: Northern G](https://contest.ucup.ac/contest/1917/problem/10093)
有两个 $k\times k$ 的矩阵 $A$ 和 $B$，求 $A\times B$ 时直接做的复杂度为 $\O(k^3)$，如果 $A$ 和 $B$ 中有意义的值的个数的 $\min$ 只有 $\O(k)$ 时，可以先枚举 $\O(k)$ 个有值的位置，再枚举一维后复杂度就是 $\O(k^2)$。

### [省选模拟赛23 T1 和平外交](http://goj.wiki/d/Union2024/p/P1427)
单点加链差，直接用树剖做做 $\O(\log^2n)$，但是用树状数组维护当前点到根的链和，修改就是在树状数组上修改整个子树的和，维护区间加单点查，复杂度 $\O(\log n)$。

### [countcircle](http://goj.wiki/d/dx2025/p/S1216)
在[比赛题解](https://yaohaoyou.github.io/post/contest-solution/)里。

对于矩阵上求偏序关系，可以先用分治降一个维度，为保证复杂度正确，每次要将长度更长的边从中间劈开。分治层数为 $\O(\log nm)$。

### [frame](http://goj.wiki/d/dx2025/p/P1548)
多树问题和距离问题考虑点分治和点分树。本题在第一颗树上进行点分治，第二棵树点分树。

点分树的性质：原树上 $u,v$ 的路径会经过点分树上的 $LCA(u,v)$，所以 $dis(x,y)=dis(x,LCA'(x,y))+dis(LCA'(x,y),y)$，$LCA'$ 表示在点分树上的 lca。

### [P2481 [SDOI2010] 代码拍卖会](https://www.luogu.com.cn/problem/P2481)
一个 $n$ 位数 $a_1a_2a_3\dots a_n$ 满足 $a_1\le a_2 \le a_3\dots \le a_n$ 可以转化为若干个 $111\dots111$ 相加。

### [P11504 [NordicOI 2018] French Fries](https://www.luogu.com.cn/problem/P11504)
对于求两个大数浮点数相除后形成一个较小的浮点数时，如果直接算出两个大数后相除会导致精度极为不准，而可以转为求解两个大数的 $\log$，除法就转化成了减法，最后再 $\text{pow}$ 回去就可以了。

比如本题求解的是 $\frac {\binom{x}{m}} {2^m},m\le 10^5$，递推会超时。于是可以转为预处理 $\log_2(i!)$ 求 $2^{(\log_2\binom{x}{m})-m}$。

### [P9528 [JOISC 2022] 蚂蚁与方糖](https://www.luogu.com.cn/problem/P9528)
由 HALL 定理可以推出二分图 $G=(X,Y,E)$ 的最大匹配数 $ans=|X|-\max_{S\in X}(|S|-|N(S)|)$，其中 $N(S)$ 为 $S$ 的邻域，后记 $d=\max_{S\in X}(|S|-|N(S)|)$。

上界证明，即 $ans \le |X|-d$：

可以找到一个集合 $S$ 满足 $|S|-|N(S)|=d$，此时显然最多存在 $N(S)$ 组匹配，并且会剩下至少 $d$ 个点无法匹配，由 HALL 定理，需要满足 $|N(S)|\ge |S|$ 需要删除至少 $d$ 个点，所以 $ans\le |X|-d$。

下界证明，即 $ans\ge |X|-d$：

往 $Y$ 中加入 $d$ 个点并都向 $X$ 的每个点连边，令 $d$ 个点形成的集合为 $D$，$Y'=Y+D$。下面只要证明 $G'=(X,Y',E')$ 为完美匹配即可。

$\forall S\in X,|S|-|N'(S)|=|S|-|N(S)\cup D|=|S|-|N(S)|-d\le 0$，即 $\forall S\in X,|N'(S)|\ge |S|$，所以由 HALL 定理得此时存在完美匹配，故 $ans\ge |X|-d$。

综上，$ans=|X|-d=|X|-\max_{S\in X}(|S|-|N(S)|)$。

### [P9962 [THUPC 2024 初赛] 一棵树](https://www.luogu.com.cn/problem/P9962)
参考 [<min/max,+>卷积与背包优化](https://www.luogu.com.cn/article/fzd5rr7p)。

两个下凸包做 (min/max,+) 可以直接归并差分数组，$\O(n+m)$ 做，此题中使用可并堆维护差分数组做到均摊单次 $\O(\log_2(n+m))$。

一个下凸包和另一个平凡函数可以 $\O(n\log_2(n+m))$ 做。

[对顶堆](https://oi-wiki.org/ds/binary-heap/#%E5%AF%B9%E9%A1%B6%E5%A0%86)可以一定情况下解决堆无法做区间加的情况。

### [The Profiteer](https://qoj.ac/problem/3998)
做多次保留除了一个区间的物品的背包时，可以使用整体二分或 cdq 分治，将区间挂在分治树上，当递归到 $[l,r]$ 时提前将除了 $[l,r]$ 的物品放入背包，因为往下递归时一定还会用这些物品，递归结束后要撤销还原。

### [P13662 「TPOI-5A」Luminescence](https://www.luogu.com.cn/problem/P13662)
mex = 补集的 min。在排列中，一段区间 $[l,r]$ 的 mex 可以变为 $\min(\min[1,l-1],\min[r+1,n])$。

### [CF1389G Directing Edges](https://www.luogu.com.cn/problem/CF1389G)
一个边双连通分量存在边定向方案使得变为一个强连通分量。

### [Yet Another Mex Problem](https://qoj.ac/contest/1392/problem/7605)
$i=1\to n$，直接维护 $1\le j\le i,\operatorname{mex} [j,i]$ 的集合 $S_i$，可以得到 $\sum |S_i|=\O(n)$。
首先显然 $\operatorname{mex}[i,j] \le n$，其次由于若 $[l,r]\sube [L,R]$ $\operatorname{mex}[l,r]\le \operatorname{mex}[L,R]$，所以列出一个矩形维护 $a_{i,j}=\operatorname{mex}[i,j]$，则每个数字会出现在一个连通块内，所以直接遍历 $S_i$ 的复杂度为 $\O(n)$。

### [CF2159B Rectangles](https://www.luogu.com.cn/problem/CF2159B)
ST 表可以实现操作和查询分离的区间取 min，区间查询 min（$\O(1)-\O(n\log n)-\O(1)$）。具体实现就是类似于将朴素的 st 表倒着做，修改区间 $i\in[l,r],a_i\gets\min(a_i,v)$ 时相当于给区间 $[l,l+2^k)$ 和 $(r-2^k,r]$ 做取 min 操作，直接在那个节点上打 tag 即可。所有操作做完后的 build 就是 tag 下传，从高位向低位转移，然后就可以求出每个 $a_i$ 了。

参考[这份代码](https://codeforces.com/contest/2159/submission/345110303)的 DS 部分。

### [P5311 [Ynoi2011] 成都七中](https://www.luogu.com.cn/problem/P5311)
首先 $T$ 的点分树 $T'$ 满足对于两个点 $u,v$，$lca_{T'}(u,v)$ 在 $T$ 上 $u$ 到 $v$ 的路径上，所以 $dis_T(u,v)=dis_T(u,lca_{T'}(u,v))+dis_T(lca_{T'}(u,v),v)$。这个是经典结论，在点分治过程中证明即可。

此题需要的结论：一个 $T$ 上的连通块点集 $S$ 满足在 $T'$ 中存在一个点 $u$ 满足 $\forall x\in S,x\in subtree_{T'}u$。

### 关于 AC 自动机的 fail 树
fail 树满足两个点 $p,q$ 表示的字符串 $S,T$，$S$ 为 $T$ 的后缀当且仅当 $q \in subtree(p)$。所以匹配问题中，与 $p$ 的字符串匹配的次数为文本串经过 $subtree(p)$ 的次数之和。

#### [CF710F String Set Queries](https://www.luogu.com.cn/problem/CF710F) AC自动机部分 做法
另外一种求解文本串匹配次数之和的方法是，若文本串匹配到了 $p$ 表示的字符串，则文本串一定可以匹配到 $p$ 的所有祖先，所以可以提前记录下 dep，插入文本串时加上经过的点的 dep 就是答案，于是也可以做修改点权了。

[参考](https://www.cnblogs.com/alex-wei/p/Common_String_Theory_Theory_automaton_related.html)

### [CF1810G The Maximum Prefix](https://www.luogu.com.cn/problem/CF1810G)
dp 求最大前缀和正着做比较困难，需要记录当前和 & 最大前缀和，但是倒着做可以记录 $dp_{i,j}$ 表示 $[i,n]$ 的最大前缀和为 $j$，转移可以贪心看是否加入 $a_i$，即 $dp_{i,\max(j+a_i,0)} \gets dp_{i,j}$。

另外就是对于多次转移系数相同的 dp，只有初值不同的，可以记录 $f_{i,j}$ 表示 $dp_{i,j}$ 对答案的系数贡献。参考 zlt 的题解，没写代码。

### [P13693 [CEOI 2025] Equal Mex](https://www.luogu.com.cn/problem/P13693)

有结论：称满足 $\not\exist [l',r']\sub [l,r],\mex[l',r']=\mex[l,r]$ 的区间 $[l,r]$ 为极小区间（类似支配对），则满足所有的极小区间只有 $\O(n)$ 个，至多有 $2n$ 个。证明可以讨论得出每个 $l$ 至多对应一个 $a_l>a_r$ 的极小区间，每个 $r$ 至多对应一个 $a_l<a_r$ 的极小区间，所以总共至多有 $2n$ 个。

思考如何求极小区间。将 $l$ 从 $1$ 到 $n$，动态维护 $b_i=\mex[l,i]$，每次删除 $l$ 时会将 $b_i\ge a_l,i<nxt_i$ 的 $b$ 全部推平成 $a_l$，此时 $l$ 对应的极小区间就是 $[l,i]$，$i$ 为被推平的部分（区间内 $\mex$ 相同的显然只取最小的 $i$）。可以使用 odt 或线段树维护。

