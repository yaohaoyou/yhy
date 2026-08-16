### [离散对数是个谎言](http://www.gdfzoj.com:23380/contest/858/problem/8590)

正难则反，将函数带入后逆着求。

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

做数论题记得尝试使用筛法预处理优化，特别是积性函数。此题中是求 $i^n$，$n$ 固定，$i\in [1,k]$，使用线性筛可以做到 $O(k)$ 预处理。

PS：对于指数固定可以使用线性筛求积性函数，对于底数固定可以使用 $O(\sqrt {mod})-O(1)$ 光速幂（bsgs） 优化。

### [NOIP 模拟赛11 T2 笛卡尔树](http://goj.wiki/d/Union2024/p/P1042)

序列中 $a_i$ 最右的 $a_l>a_i$ 和最左的 $a_r>a_i$ 满足 $[a_{l+1},a_{r-1}]$ 在笛卡尔树上就是 $i$ 的子树。

### [NOIP 模拟赛12 T2 括号串](https://www.luogu.com.cn/problem/CF1264D2)

[范德蒙德卷积](https://oi-wiki.org/math/combinatorics/vandermonde-convolution/)（其实就是组合意义）

还有，就是 
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

求可行性 01 背包及构造，空间线性，时间 $O(\frac{nV+V^2}{\omega})$。

在直接用 bitset 做的时候，维护当前容量是从哪里转移的，实际上 ``tmp=dp^(dp|(dp<<w[i]))``，即转移前后相异或的 bitset 中为 1 的位就是从 ``w[i]`` 转移的。直接遍历 ``tmp`` 的每一位，因为每种容量只会被遍历 1 次，单次最劣复杂度为 $O(\frac{V}{\omega})$，故求构造总复杂度为 $O(\frac{V^2}{\omega})$。常数可能较大。

设 $\sum w_i=S$，则共有 $O(\sqrt S)$ 种不同的 $w_i$，如果改成做多重背包就能将 $n$ 降到 $\sqrt S$，直接二进制优化复杂度为 $O(\sqrt S\times V \times \log_2n)$，但实际上好像是 $O(\sqrt S\times V)$。

### [The 3rd Universal Cup. Stage 30: Northern G](https://contest.ucup.ac/contest/1917/problem/10093)

有两个 $k\times k$ 的矩阵 $A$ 和 $B$，求 $A\times B$ 时直接做的复杂度为 $O(k^3)$，如果 $A$ 和 $B$ 中有意义的值的个数的 $\min$ 只有 $O(k)$ 时，可以先枚举 $O(k)$ 个有值的位置，再枚举一维后复杂度就是 $O(k^2)$。

### [省选模拟赛23 T1 和平外交](http://goj.wiki/d/Union2024/p/P1427)

单点加链差，直接用树剖做做 $\mathcal O(\log^2n)$，但是用树状数组维护当前点到根的链和，修改就是在树状数组上修改整个子树的和，维护区间加单点查，复杂度 $\mathcal O(\log n)$。

### [countcircle](http://goj.wiki/d/dx2025/p/S1216)

在[比赛题解](https://yaohaoyou.github.io/post/contest-solution/)里。

对于矩阵上求偏序关系，可以先用分治降一个维度，为保证复杂度正确，每次要将长度更长的边从中间劈开。分治层数为 $\mathcal O(\log nm)$。

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



::::info[证明]{}

上界证明，即 $ans \le |X|-d$：

可以找到一个集合 $S$ 满足 $|S|-|N(S)|=d$，此时显然最多存在 $N(S)$ 组匹配，并且会剩下至少 $d$ 个点无法匹配，由 HALL 定理，需要满足 $|N(S)|\ge |S|$ 需要删除至少 $d$ 个点，所以 $ans\le |X|-d$。

下界证明，即 $ans\ge |X|-d$：

往 $Y$ 中加入 $d$ 个点并都向 $X$ 的每个点连边，令 $d$ 个点形成的集合为 $D$，$Y'=Y+D$。下面只要证明 $G'=(X,Y',E')$ 为完美匹配即可。

$\forall S\in X,|S|-|N'(S)|=|S|-|N(S)\cup D|=|S|-|N(S)|-d\le 0$，即 $\forall S\in X,|N'(S)|\ge |S|$，所以由 HALL 定理得此时存在完美匹配，故 $ans\ge |X|-d$。

综上，$ans=|X|-d=|X|-\max_{S\in X}(|S|-|N(S)|)$。
::::

### [P9962 [THUPC 2024 初赛] 一棵树](https://www.luogu.com.cn/problem/P9962)

参考 [<min/max,+>卷积与背包优化](https://www.luogu.com.cn/article/fzd5rr7p)。

两个下凸包做 (min/max,+) 可以直接归并差分数组，$O(n+m)$ 做，此题中使用可并堆维护差分数组做到均摊单次 $\mathcal O(\log_2(n+m))$。

一个下凸包和另一个平凡函数可以 $O(n\log_2(n+m))$ 做。

[对顶堆](https://oi-wiki.org/ds/binary-heap/#%E5%AF%B9%E9%A1%B6%E5%A0%86)可以一定情况下解决堆无法做区间加的情况。

### [The Profiteer](https://qoj.ac/problem/3998)

做多次保留除了一个区间的物品的背包时，可以使用整体二分或 cdq 分治，将区间挂在分治树上，当递归到 $[l,r]$ 时提前将除了 $[l,r]$ 的物品放入背包，因为往下递归时一定还会用这些物品，递归结束后要撤销还原。

### [P13662 「TPOI-5A」Luminescence](https://www.luogu.com.cn/problem/P13662)

mex = 补集的 min。在排列中，一段区间 $[l,r]$ 的 mex 可以变为 $\min(\min[1,l-1],\min[r+1,n])$。

### [CF1389G Directing Edges](https://www.luogu.com.cn/problem/CF1389G)

一个边双连通分量存在边定向方案使得变为一个强连通分量。

### [Yet Another Mex Problem](https://qoj.ac/contest/1392/problem/7605)

$i=1\to n$，直接维护 $1\le j\le i,\operatorname{mex} [j,i]$ 的集合 $S_i$，可以得到 $\sum |S_i|=\mathcal O(n)$。
::::info[证明]
首先显然 $\operatorname{mex}[i,j] \le n$，其次由于若 $[l,r]\sube [L,R]$ $\operatorname{mex}[l,r]\le \operatorname{mex}[L,R]$，所以列出一个矩形维护 $a_{i,j}=\operatorname{mex}[i,j]$，则每个数字会出现在一个连通块内，所以直接遍历 $S_i$ 的复杂度为 $\mathcal O(n)$。
::::

### [CF2159B Rectangles](https://www.luogu.com.cn/problem/CF2159B)

ST 表可以实现操作和查询分离的区间取 min，区间查询 min（$\mathcal O(1)-\mathcal O(n\log n)-\mathcal O(1)$）。具体实现就是类似于将朴素的 st 表倒着做，修改区间 $i\in[l,r],a_i\gets\min(a_i,v)$ 时相当于给区间 $[l,l+2^k)$ 和 $(r-2^k,r]$ 做取 min 操作，直接在那个节点上打 tag 即可。所有操作做完后的 build 就是 tag 下传，从高位向低位转移，然后就可以求出每个 $a_i$ 了。

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

有结论：称满足 $\not\exist [l',r']\sub [l,r],\operatorname{mex}[l',r']=\operatorname{mex}[l,r]$ 的区间 $[l,r]$ 为极小区间（类似支配对），则满足所有的极小区间只有 $\mathcal O(n)$ 个，至多有 $2n$ 个。证明可以讨论得出每个 $l$ 至多对应一个 $a_l>a_r$ 的极小区间，每个 $r$ 至多对应一个 $a_l<a_r$ 的极小区间，所以总共至多有 $2n$ 个。

思考如何求极小区间。将 $l$ 从 $1$ 到 $n$，动态维护 $b_i=\operatorname{mex}[l,i]$，每次删除 $l$ 时会将 $b_i\ge a_l,i<nxt_i$ 的 $b$ 全部推平成 $a_l$，此时 $l$ 对应的极小区间就是 $[l,i]$，$i$ 为被推平的部分（区间内 $\operatorname{mex}$ 相同的显然只取最小的 $i$）。可以使用 odt 或线段树维护。

### [P4948 数列求和](https://www.luogu.com.cn/problem/P4948)
[这里](https://www.luogu.com.cn/article/4jicxaql)或去讲题 md 里找。

### [P7597 「EZEC-8」猜树 加强版](https://www.luogu.com.cn/problem/P7597)
重剖的经典结论是所有点到根的路径上的轻边数量和为 $\mathcal O(n\log_2 n)$ 的。

由此也可以推出二级结论：$\sum_{u=1}^n (siz_u-siz_{son_u})=\mathcal O(n\log_2 n)$，证明就是一个点的所有轻儿子子树会在这个位置贡献一次，这就等同于每个点 $u$ 会在根到 $u$ 的路径上的轻边贡献，套用上面的结论即可证明。

### [P11364 [NOIP2024] 树上查询](https://www.luogu.com.cn/problem/P11364)
补一下。

$$
dep_{LCA[l,r]}=\min_{i=l}^{r-1} dep_{LCA(i,i+1)}
$$
并且 $LCA[l,r]$ 也等于取到右边最小值的位置，可以用虚树的构造证明。

### [Fake Plastic Trees 2](https://qoj.ac/problem/2562)
对于点 $u$ 的背包容量为 $siz_u$ 的树上背包的总复杂度为 $\mathcal O(n^2)$。对于点 $u$ 的背包容量为 $\min(siz_u,k)$ 的树上背包的总复杂度为 $\mathcal O(nk)$。

::::info[证明]
第一个可以理解为在任意两个点会在 LCA 处合并，所以是 $n^2$ 的。

第二个考虑将 $siz_u\ge k$ 的 $u$ 子树称为大树，$siz_u<k$ 的称为小树。显然极大的小树之间互不相交，极小的大树之间互不相交。

极大的小树合成时的复杂度由上面的证明可知为 $siz_u^2$，总复杂度为 $\sum siz_u^2$，因为 $\sum siz_u\le n,siz_u<k$，所以 $\sum siz_u^2<(n/k)\times k^2=nk$，当每个 $siz_u$ 都为 $k$ 时最大。

极大的小树向上合成为极小的大树时复杂度为 $\sum_{u=fa_v} k\times siz_v=k\sum siz_v\le nk$。

极大的小树合成时复杂度为 $\sum_{u} k^2$，由于互不相交，所以至多有 $\lfloor\frac n k\rfloor$ 棵，复杂度为 $k^2\times \frac nk=nk$。

综上，总复杂度为 $\mathcal O(nk)$。证明参考了[这里](https://blog.csdn.net/lyd_7_29/article/details/79854245)。
::::

### [Excluded Min](https://qoj.ac/problem/964)
可能是一个比较典的回滚莫队+并查集链表维护单调栈的套路，具体的看比赛 md 或 [代码源 T4](http://oj.daimayuan.top/contest/417/tutorial)。代码源 T4 的第二个做法可以将本题优化至 $\mathcal O(n\log n)$。

### [P6790 [SNOI2020] 生成树](https://www.luogu.com.cn/problem/P6790)
原图是广义串并联图，即不存在任意四个点之间的六条路径两两无交。

可以使用删一度点，缩二度点，叠合重边简化图的形态，在此过程中进行计数即可。

### [AT_arc213_c Double X](https://www.luogu.com.cn/problem/AT_arc213_c)
二分图的最小 k-匹配可以将重边保留最小的边权后只保留每个左部点的前 $k$ 小边，不影响正确性，然后就只剩 $nk$ 条边了。

### [abc443_g  Another Mod of Linear Problem](https://atcoder.jp/contests/abc443/tasks/abc443_g)
$$
[a\bmod m < b \bmod m]=\lfloor\frac am \rfloor-\lfloor\frac bm \rfloor - \lfloor\frac {a-b}m \rfloor \\
[a\bmod m <k]=\lfloor\frac am \rfloor - \lfloor\frac {a-k}m \rfloor
$$

### [Range Periodicity Query](https://qoj.ac/problem/8079)
称 $k$ 为 $S$ 的周期当 $\forall i\in [1,|S|-k],S_i=S_{i+k}$，则对于 $S$ 的任意一段 border $S[1,k]$ 都满足 $[k+1,|S|]$ 是 $S$ 的周期，即 $S[1,k]\text{ is border}\lrarr S[k+1,|S|]$ 是周期。

当 $S[1,k]$ 为 $S$ 的 border 时，$|S|-k$ 是任意 $S[i+1,|S|-j],i+j=k$ 的周期。

### [CF1098F Ж-function](https://www.luogu.com.cn/problem/CF1098F)
使用 SA 性质在题目中从三维数点转化成两个二位数点的方法，详见 [XDFZ](https://www.luogu.com.cn/article/jutl9wek)。

### [染色](https://newoj.daimayuan.top/p/3388?tid=69818a06f0fd3b148a6f06b0)
$$
n^k=\sum_{i=0}^k n^{\underline i}{k\brace i}=\sum_{i=0}^k \binom{n}{i}i!{k\brace i}
$$

### [AT_abc221_h Count Multiset](https://www.luogu.com.cn/problem/AT_abc221_h)
将求 multiset/set 方案书转化成每次操作在末尾加入 0 或整体 +1。

### [盆栽展示](https://newoj.daimayuan.top/p/4721?tid=69875186f0fd3b148a82e96c)
对于转移 $f_i=\min_{j<i}f_j+(a_i\oplus a_j)$，直接做复杂度是 $\mathcal O(n^2)$，若还有 $a_i\le V$ 的限制可以通过将 $f_i$ 存进 $buc_{a_i}$ 中，转移变成 $\mathcal O(nV)$。但是此时修改的复杂度为 $\mathcal O(1)$，查询复杂度为 $\mathcal O(V)$，考虑平衡一下，将桶 $buc_x$改成 $buc_{i,j}$ 表示 $i=\lfloor \frac{x}{\sqrt V}\rfloor,j=x\bmod \sqrt V$，修改时枚举 $i$，查询时枚举 $j$，复杂度优化成 $\mathcal O(n\sqrt V)$。

### [P7220 [JOISC 2020] 掃除](https://www.luogu.com.cn/problem/P7220)
对于一个直角三角形内的点 $(x,y)$ 满足 $x+y\le L$，可以转化成区间 $[x,L-y]$。

对于多个区间的端点修改操作可以在猫树/线段树上维护，若区间单调增/单调减，则一个区间永远只会在线段树上出现在 $\mathcal O(\log n)$ 个节点。

### [P13342 [EGOI 2025] Wind Turbines / 风力涡轮机](https://www.luogu.com.cn/problem/P13342)
好像有好几个 Ynoi 都有的类似的思想。

对于一个节点 $u$，若存在两个点满足 $LCA(x,y)=u$ 且询问区间 $[l,r]$ 满足 $[x,y]\sube [l,r]$，$u$ 就能对这个询问产生贡献。若有 $x1\le x2\le y2\le y1$，则 $[x1,y1]$ 无用，称 $[x2,y2]$ 支配 $[x1,y1]$。有结论对于所有的 $u\in [n]$，一共只有 $\mathcal O(n\log n)$ 对极小支配对。求法可以考虑 dsu on tree，每个节点 $u$ 先求出重儿子的子树信息，然后每个轻子树在里面找前驱后驱即可。支配对数量级证明和树剖复杂度证明类似。

### [O(n)-O(1) rmq](https://oi-wiki.org/topic/rmq/#%E5%9F%BA%E4%BA%8E%E7%8A%B6%E5%8E%8B%E7%9A%84%E7%BA%BF%E6%80%A7-rmq-%E7%AE%97%E6%B3%95)
虽然说有限制 $\log_2 n\le64$，但明显不可能有题目会 $n\ge 2^{64}$，所以也可以直接认为是 $\mathcal O(n)-\mathcal O(1)$ rmq 了。大概做法就是 [由乃救爷爷](https://www.luogu.com.cn/problem/P3793) 的优化，其中散块内部的处理改成预处理块内单调栈，然后用一个整数存下当前时刻当前块内的单调栈中每个数是否存在的状态即可。

[挂一份实现，这个题因为是随机数据所以速度优势不明显](https://www.luogu.com.cn/record/262448990)。

### [P12962 [GCJ Farewell Round #4] Genetic Sequences](https://www.luogu.com.cn/problem/P12962)
使用 SA 转化成区间 min height 后，正常情况还要分讨两个端点的大小关系后将左端点 +1。这个题目的套路是直接建立笛卡尔树，因为 rmq 问题中区间 min 就是小根笛卡尔树上的 LCA。对于 height 左端点 +1，可以直接建出 $2n-1$ 个节点，其中 $2i-1$ 节点表示字符串的第 $i$ 个位置，权值为 $n+1$，第 $2i$ 个节点表示 $height_{i+1}$，权值为 $height_{i+1}$，这样 $LCP(s[i,n],s[j,n])=height_{LCA(2i-1,2j-1)}$。

### 对 $[1,n]$ 的所有数分解质因数可以直接线性筛预处理每个数的最小质因数，就可以做到 $\mathcal O(d(x))$ 分解 $x,x\in [1,n]$。

### [Command and Conquer: Red Alert 2](https://qoj.ac/contest/696/problem/1870)
[goj](http://goj.wiki/d/Union2024/record/699e98e493b6e64674d0c2b0)。

对于 $k$ 个限制 $a_{i,1}\le lim_1,\dots,a_{i,k}\le lim_k$，$lim_i$ 单调不降，可以对于每个 $i$ 设置 $k$ 个报警器，在 $lim_i$ 到达 $a_{x,i}$ 时将 $x$ 的满足数量 $+1$，当满足限制数 $=k$ 时就是满足了。复杂度为 $\mathcal O(nk)$。

### 神秘题
长度为 $n$ 的序列操作是每次左右增删一个数后求最大子段和，强制在线，要求 $\mathcal O(n)$。

如果用线段树会多一个 $\log$ 而且空间大。这里的技巧就是类似于二区间合并，取序列中点，对于 $i\le \frac n2$ 的维护 $[i,\frac n2]$ 的最大子段和 & 最大后缀和，对于 $i>\frac n2$ 的维护 $(\frac n2,i]$ 的最大子段和 & 最大前缀和，在中点做合并即可。但是当中点被删除时，直接暴力重构也能保证复杂度是线性的，因为至少会花费 $\frac n2+x$ 次删除才能重构，而重构一次序列长度为 $\frac n2+x$（$x$ 是在重构前往序列插入的次数），所以均摊 $\mathcal O(n)$。

主要的 trick 就是**二区间合并**和**过中点重构**保证线性。

### [P9340 [JOIST 2023] 旅行 / Tourism](https://www.luogu.com.cn/problem/P9340)
> 给定 $n$ 个区间和 $q$ 次询问，每次询问区间 $[l,r]$ 的并的集合大小。

先按 $r$ 扫描线，对每个点记录被覆盖的最后时间，则修改为将 $[L_r,R_r]$ 覆盖为 $r$，全局求 $\ge l$ 的个数。使用 odt 维护连续段，树状数组维护颜色出现次数，每次修改会将原本的连续段删除并在树状数组上修改，复杂度证明就是颜色段均摊，复杂度 $\mathcal O((n+q)\log n)$。

### [P11872 [威海市赛 2024] 异或盒子 1](https://www.luogu.com.cn/problem/P11872)
> 全局 +1，单点修改，求全局异或和

考虑使用 01 Trie，但是 +1 往往是影响低位，所以从低位到高位插入 01 Trie。手玩不难发现每次就是将两个儿子交换后进入新的 0 儿子（原本的 1 儿子），然后继续 +1。在第 $i$ 层交换一次会让 1 子树的值 $-2^i$，然后要在下一层 $+2^{i+1}$，所以是正确的。复杂度为 $\mathcal O((n+q)\log V)$。

### [2026 省选模拟赛 Day 17 #B. 追忆](https://newoj.daimayuan.top/p/4775?tid=69a5374fbff5d4356a21b04f)

卡空间方法详见讲题.md。

### [AT_abc459_f [ABC459F] -1, +1](https://www.luogu.com.cn/problem/AT_abc459_f)
序列 $a_i$ 严格递增等价于 $b_i=a_i-i$ 非严格递增。

### nflsoi 残缺的排列
首先有 $n$ 个点的完全图的生成树方案数为 $\mathcal n^{n-2}$ 种。拓展可得有 $k$ 个连通块，第 $i$ 个连通块内有 $a_i$ 个点，$n=\sum a_i$，则将这 $k$ 个连通块联通的方案数为 $n^{k-2}\prod a_i$。

注意：要使两个大小为 $x,y$ 的连通块联通可以有 $xy$ 种连边方式。拓展的证明在[这里](https://www.cnblogs.com/SigmaToT/p/20275424)。

### [CF1528F AmShZ Farm](https://www.luogu.com.cn/problem/CF1528F)
$a$ 满足每个数加上一个非负整数后可以成为 $[1,n]$ 的排列，可以使用一个模型转化成：有 $n+1$ 个椅子，每个人想坐在 $a_i$ 上，如果当前座位上有人，就移到下一个位置上。若 $n+1$ 的椅子上没有人就满足，否则就不满足。随后可以在 $n+1$ 与 $1$ 连一条边，然后形成一个环，依旧是当 $n+1$ 上没有人就满足。因为这个环上的每个位置都是本质相同的，所以有 $\frac 1n$ 的概率满足。

### [QOJ14973 Welcome to Math Kingdom!](https://qoj.ac/problem/14973)
对于限制极度宽松的构造题，可以手动增加一些好做的限制来寻找和发现更强的性质。这题中，带入 $a=c=1$ 和 $b^2-b+1=d^2-d+1$ 的限制会更加好做，最后可以再调整到正确的答案。

### [Pyh 的求和](https://loj.ac/p/6179)/[P4240 毒瘤之神的考验](https://www.luogu.com.cn/problem/P4240)
关于 $\mathcal O(\sum_{i=B}^n \frac{n^k}{i^k})$ 的复杂度。
$$
k=1:\quad \int_B^n \frac{n}{i}\,di = n\ln\frac{n}{B}\\

k=2:\quad \int_B^n \frac{n^2}{i^2}\,di = \frac{n^2}{B} - n\\

k=3:\quad \int_B^n \frac{n^3}{i^3}\,di = \frac{n^3}{2B^2} - \frac{n}{2}\\

k=4:\quad \int_B^n \frac{n^4}{i^4}\,di = \frac{n^4}{3B^3} - \frac{n}{3}\\
$$
常见的：
$$
\sum_{i=B}^n \frac ni=\mathcal O(n\ln n)\\
\sum_{i=1}^n \frac {n^2}{i^2}=\mathcal O(n^2)\\
\sum_{i=\sqrt n}^n \frac {n^2}{i^2}=\mathcal O(n\sqrt n)\\
$$
### [P16313 [ICPC 2023 Jinan R] 向未来说你好](https://www.luogu.com.cn/problem/P16313)

将数列分成任意段（可能有限制），计算任意贡献和的题目。令 $f_i$ 表示前 $i$ 个位置的答案，正常做需要想如何 $f_j \to f_i$，若 $j$ 不连续或难维护时不好做。考虑用 cdq 分治在 $[l,r]$ 讨论跨过 $mid$ 的区间 $[i,j]$ 的贡献，再拼上 $[1,i)$ 和 $(j,n]$ 的贡献。

省流：用 cdq 分治讨论 $mid$ 所在段的贡献。

### [P2143 [JSOI2010] 巨额奖金](https://www.luogu.com.cn/problem/P2143)

kruskal 的过程的另类解释：

1. 从 $i=1\to \max w$ 枚举边权长度。
2. 通过 $E_i$ 的边将图连成若干个森林。

其中在 $2$ 操作中遍历 $E_i$ 的顺序没有影响。

### [网格排列](https://zhengruioi.com/problem/3605?cid=2167)

给数列排列时可以考虑先对两部分确定内部顺序，然后使用归并合并，归并过程类似从 $(0,0)\to (n,n)$ 的路径，向上走表示取第一行，向下走表示去第二行。在有限制的位置对前面被限制的位置延后钦定。

### [P4770 [NOI2018] 你的名字](https://www.luogu.com.cn/problem/P4770)

一个字符串 $T$ 放入 $S$ 的 SAM 中匹配到的节点 $x$ 表示 $T$ 的长为 $len_x$ 的后缀是最长的匹配 $S$ 的子串的后缀。

可以认为，将一个匹配串放入模式串的 SAM 中匹配的结果就是放入模式串所有子串构成的 ACAM 中的结果，即 $S$ 构成的 SAM 可以认为是 $\forall S[l,r]$ 构成的 ACAM。

### ogf trick

$$
F(x)=(1+x^2+x^4+\dots)(1+x^3+x^6+\dots)(1+x^4+x^8+\dots)
$$

求 $[x^n]F(x)$。

不难列出
$$
F(x)=\frac{1}{(1-x^2)(1-x^3)(1-x^4)}=f_0+f_1x+f_2x^2+\dots
$$
求解的答案 $[x^n]F(x)=f_n$。令 $G(x)=(1-x^2)(1-x^3)(1-x^4)=g_0+g_1x+g_2x^2+\dots g_9x^9$，展开后的系数 $g_0,\dots g_9$ 不难算出。

因为有 $F(x)G(x)=1$，所以有
$$
f_0g_0=1\\
\forall i,\sum_{j=0}^i f_jg_{i-j}=0
$$
由于已知 $g$ 的前 $10$ 项值，所以可以直接求出 $f_0,\dots f_9$。因为有 $g_0=1$，所以有
$$
f_i=-\sum_{j=0}^{i-1}f_jg_{i-j}=\sum_{j=0}^9 g_jf_{i-j}
$$
只是一个固定系数的递推形式，可以使用矩阵快速幂做到 $\mathcal O(9^3\log n)$。
