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
2.  $in_x\to out_x$ 容量为 $1$，费用为 $w_x$。
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

## [Pyh 的求和](https://loj.ac/p/6179)/[P4240 毒瘤之神的考验](https://www.luogu.com.cn/problem/P4240)

$$
ans=\sum_{i=1}^n\sum_{j=1}^m\varphi(ij)\\
=\sum_{i=1}^n\sum_{j=1}^m\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}\\
=\sum_{d=1}^{\min(n,m)}\frac{d}{\varphi(d)}\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} [\gcd(i,j)=1]\varphi(id)\varphi(jd) \\
=\sum_{d=1}^{\min(n,m)}\frac{d}{\varphi(d)}\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} \sum_{p|i,p|j}\mu(p)\varphi(id)\varphi(jd) \\
=\sum_{d=1}^{\min(n,m)}\frac{d}{\varphi(d)}\sum_{p=1}^{\min(n,m)}\mu(p)\sum_{i=1}^{n/dp}\sum_{j=1}^{m/dp} \varphi(idp)\varphi(jdp) \\
$$

预处理 $f_n=\sum_{ij=n}\frac{i}{\varphi(i)}\mu(j)$，预处理复杂度为 $\mathcal O(n\log n)$。
$$
ans=\sum_{x=1}^{\min(n,m)} f_x(\sum_{i=1}^{\lfloor\frac{n}{x}\rfloor}\varphi(ix))(\sum_{j=1}^{\lfloor\frac{m}{x}\rfloor}\varphi(jx))
$$
预处理 $g_{n,x}=\sum_{i=1}^{x}\varphi(in)$，复杂度还是 $\mathcal O(n\log n)$。
$$
ans=\sum_{x=1}^{\min(n,m)} f_xg_{x,\lfloor\frac nx\rfloor}g_{x,\lfloor\frac mx\rfloor}
$$
现在 $ans$ 的形式还是对于 $x\in[1,\min(n,m)]$ 进行对位乘后求和，不太能直接优化，考虑根号分治。

对于 $x\le B$ 时暴力跑上面的式子，复杂度 $\mathcal O(B)$。对于 $x>B$，预处理 $h_{n,i,j}=\sum_{x=1}^n f_xg_{x,i}g_{x,j}$，再对第一维做前缀和（即$h'_{n,i,j}=\sum_{k\le n} h_{k,i,j}$）。对 $n$ 和 $m$ 做整除分块，有序对 $(\lfloor\frac{n}{x}\rfloor,\lfloor\frac{m}{x}\rfloor)$ 只有 $\mathcal O(\sqrt n+\sqrt m)$ 种，复杂度为 $\mathcal O({\color{red}\frac{n^2}B}+T\sqrt n)$。总复杂度为 $\mathcal O(\frac{n^2} B+TB+T\sqrt n)$，平衡取 $B=\sqrt\frac{n^2}{T}$，视 $n,T$ 同阶时，做到 $\mathcal O(n\sqrt n)$。

解释一下上面红色的为什么是 $\frac{n^2}B$：
$$
\int_B^n \frac{n^2}{i^2}\,di=\frac{n^2}{B}-n
$$
空间复杂度也是 $\mathcal O(\frac{n^2}B)$ 的，再 LOJ 需要将 $B$ 稍微开大来卡空间。

## [P4213 【模板】杜教筛](https://www.luogu.com.cn/problem/P4213)

求 $sf(n)=\sum_{i=1}^n f(i)$，其中 $f$ 是积性函数。

构造积性函数 $g$，有
$$
\sum_{i=1}^n(f*g)(i)=\sum_{i=1}^n\sum_{d|i} f(d)g(\frac id) \\
=\sum_{d=1}^n g(d)\sum_{i=1}^{\lfloor\frac nd\rfloor}f(i)\\
=\sum_{d=1}^ng(d)sf(\lfloor\frac{n}d\rfloor)
$$
移项可以得到：
$$
g(1)sf(n)=\sum_{i=1}^n (f*g)(i)-\sum_{d=2}^n g(d)sf(\lfloor\frac nd\rfloor)
$$
若能快速求出 $f*g$ 和 $g$ 的前缀和，就可以使用整除分块加速求出 $sf(n)$。结论有，当能 $\mathcal O(1)$ 求出 $f*g$ 和 $g$ 的前缀和时，若提前使用线性筛算出前面的 $sf(n)$，可以做到 $\mathcal O(n^\frac 23)$，不预处理复杂度是 $\mathcal O(n^\frac 34)$。

当 $f=\varphi$ 时，有 $\varphi*1=id$，$g=1$ 和 $f*g=id$ 的前缀和都能快速求。

当 $f=\mu$ 时，有 $\mu*1=\epsilon$，$g=1$，$f*g=\epsilon$。

当 $f(i)=\varphi(i)i$，有 $h(i)=(f*id)(i)=\sum_{d|i}\varphi(d)d\frac{i}{d}=i\sum_{d|i}\varphi(d)=i^2$。$g=id$，$f*g=h$。

## [P4482 [BJWC2018] Border 的四种求法](P4482 [BJWC2018] Border 的四种求法)

给定字符串 $s$，$q$ 次询问求 $s[l,r]$ 的 border 长度。

将 border 拆成前缀的后缀形式，答案就是最大的 $x$ 满足 $x\in [0,r-l],lcs(pre_{l+x-1},pre_r)\ge x$。建出后缀树后有性质 $lcs(pre_x,pre_y)=len_{LCA(en_x,en_y)}$，其中 $en_i$ 表示 SAM 中以 $i$ 结尾的节点。所以题目就是要求 $en_r$ 的祖先 $x$ 的子树中满足 $id_p\in[l,r),id_p-len_x+1\le l$（其中可能将 LCA 算得更高，但是一定不优，所以没问题），其中 $id_{en_{i}}=i$。这个不满足单调性，直接做不好做，考虑使用树剖将询问放到 $\log n$ 个重链后离线处理。

对于一条重链，需要处理下面两种询问：

1. 对于一个前缀 $i\in tp_u\leadsto fa_u$，求最大的 $x\in endpos_i$，$x\in [l,r)$，$x-len_i+1\le l$。
2. 对于一个后缀 $i\in u\leadsto lst_u$，求最大的 $x\in endpos_i$，$x\in[l,r)$，$x-len_u+1\le l$，即 $x\in[l,\min(l+len_u-1,r-1)]$。

其中 $endpos_i$ 表示 $i$ 子树中所有 $en_v$ 的集合，实际上可以只用枚举轻子树的，因为重子树会在下面算到。处理时直接遍历重链上 $i$ 的所有轻子树的总复杂度为 $\mathcal O(n\log n)$ 的$\Large{\color{red}\Diamond}$，证明考虑树剖复杂度证明。对于 2 询问直接用 set 存下 $endpos$ 后``lower_bound``即可。对于 1 操作需要建线段树，维护 $x-len_i+1$ 的区间最小值，询问时在 $[l,r)$ 线段树上二分$\Large{\color{red}\Diamond}$。总复杂度为 $\mathcal O(n\log^2n+q\log^2n)$。

## [P16958 [SCCPC 2026] 括号序列](https://www.luogu.com.cn/problem/P16958)

[ZROJ](https://zhengruioi.com/problem/3585?cid=2165)

什么脑电波推式子题？

不难想到枚举将哪一个``)``换成``(``后计算后面的方案数，根据路径相关计数方法，得到的答案（实际上还要加上前缀合法串的数量，简单这里不考虑）就是：
$$
ans=\sum_{s_i=)}\sum_{j=x_i+1}^{n/2}\binom{2j-i}{j-x_i-1}-\binom{2j-i}{j-x_i-2} \\
=\sum_{s_i=)}\sum_{j=0}^{n/2-x_i-1}\binom{2j+2x_i+2-i}{j}-\binom{2j+2x_i+2-i}{j-1} \\
$$
其中 $x_i$ 表示前 $i$ 个位置的``(``数量，令 $c_i=2x_i+2-i$。将组合数提取出来设成 $f$：
$$
f(a,b)=\sum_{i=0}^b \binom{2i+a}{i}\\
ans=\sum_{s_i=)}f(c_i,\frac n2-x_i-1)-f(c_i+2,\frac{n}2-x_i-2)
$$
通过对 $f$ 做差分，可以发现$\Large{\color{red}\Diamond}$：
$$
f(a,b)-f(a-1,b)=\sum_{i=0}^b\binom{2i+a}i-\binom{2i+a-1}{i}\\
=\sum_{i=0}^b\binom{2i+a-1}{i-1}\\
=\sum_{i=0}^{b-1}\binom{2i+a+1}{i}\\
=f(a+1,b-1)\\
\color{red}f(a,b)=f(a+1,b-1)+f(a-1,b)\\
f(a-1,b),f(a,b) \to f(a+1,b-1),f(a,b)\to f(a,b),f(a+1,b)
$$
最后一行表明了可以 $\mathcal O(1)$ 通过已知的 $f(x-1,y),f(x,y)$ 推导到 $x\gets x+1$，而最后要求解的式子中 $c_i+i$ 是单调递增的（$c_i-c_{i+1}\le 1$），第二维也是单调递减的。考虑使用类似莫队的指针维护 $f(a,b)\Large{\color{red}\Diamond}$。总复杂度为 $\mathcal O(n)$。

## [Good Night](https://qoj.ac/problem/18303/statement/zh_cn)

[ZROJ](https://zhengruioi.com/problem/3602?cid=2166)

将 $a_i$ 称为颜色。考虑对于线段树每个区间维护完全覆盖其的区间个数。具体地，先将 $n$ 个区间插入线段树，然后对于每个线段树节点记录它到根路径上经过的颜色种数 $tr_p$。实际上，只需要维护颜色种数为 $=0/=1/\ge 2$ 即可。对于一次区间删除操作，可以类似看作对开始时插入操作的撤销，因为有 $tr_p\le tr_{son}$，所以只需要检查儿子能否改变 $tr$，若能就继续递归检查，否则结束。因为所有点只会变化至多 $2$ 次，总复杂度为 $\mathcal O(n\log n)$。
