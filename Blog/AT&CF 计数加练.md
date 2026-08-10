## 计数加练

[jiangly 自己](https://www.luogu.com.cn/problem/list?tag=252,253,259&type=CF&difficulty=5&page=1)

[狠狠 jiangly 自己](https://www.luogu.com.cn/problem/list?tag=252,253,259&type=CF&difficulty=6&page=1)

> 菜就多练，希望这个系列会一直更新下去。

update on 2024.7.24：CF1761D Carry Bit

update on 2024.7.25：CF571A Lengthening Sticks

update on 2024.8.10：CF1591F Non-equal Neighbours

update on 2024.8.12：CF1906J Count BFS Graph

## [CF1761D Carry Bit](https://www.luogu.com.cn/problem/CF1761D)

#### CF 2100 

本题是对于组合数和推式子的熟练运用。

看上去像容斥但其实是分类讨论组合。

枚举进位段数为 $i$，先算出这 $i$ 段的方案数。

相当于将 $i-1$ 块挡板插入 $k-1$ 个空隙，所以这一段有 $\binom{k-1}{i-1}$ 种划分方式，每个段除了最后一个位置一定是 $(1,1)$ 以外，其他可以是 $(0,1),(1,0),(1,1)$ 三种，所以一段答案为 $3^{len-1}$，这一部分的方案数就是
$$
\binom{k-1}{i-1}\prod 3^{len-1}=\binom{k-1}{i-1}3^{\sum len-1}=\binom{k-1}{i-1}3^{k-i}
$$
接下来分析非进位段的方案数。

此时又可以认为进位段时一块挡板，将剩余位置分段。分开讨论非进位段的段数。

1. 非进位段数为 $i+1$：即首尾都有非进位段。划分相当于将 $n-k$ 个球放入 $i+1$ 个箱子，故方案数为 $\binom{n-k-1}{i}$。每一段除最后一位一定是 $(0,0)$ 以外，其他可以是 $(0,0)(0,1)(1,0)$ 三种，所以每一段答案为 $3^{len-1}$，注意特判最后一位没有受到进位影响，故最后答案还需多 $\times 3$。与上面类似的，方案数为 $\binom{n-k-1}{i}3^{n-k-(i+1)}\times 3=\binom{n-k-1}{i}3^{n-k-i}$ 。
2. 非进位段数为 $i$：分为开头有进位段或结尾有进位段，结尾的要多 $\times 3$。与 1 类似，开头有的方案数为 $\binom{n-k-1}{i-1}3^{n-k-i}$，结尾有的方案数为 $\binom{n-k-1}{i-1}3^{n-k-i+1}$。
3. 非进位段数为 $i-1$：两头都没有进位段，类似的，方案数为 $\binom{n-k-1}{i-2}3^{n-k-i+1}$。

由于乘法原理，将进位段数和**总非进位段数**的方案相乘就是进位段数为 $i$ 的答案，最后再将 $i \in [1,k]$ 的答案相加即可，注意特判边界。

## [CF571A Lengthening Sticks](https://www.luogu.com.cn/problem/CF571A)

#### CF2100

本题是对于正难则反的技巧运用。

其实直接做也可以，但是会需要许多分讨，写到一半还是开了题解，看到了第一句话。

> 这道题直接求比较难，所以我们可以用容斥原理，求出总方案 减去不合法的方案数

恍然大悟，然后就会了。

枚举一个 $i \in[0,l]$，分别讨论 $a+i,b+i,c+i$ 为三条边最大值时的答案，固定一条最大边后，剩下两个就不难求了。

## [CF296B  Yaroslav and Two Strings](https://www.luogu.com.cn/problem/CF296B)

#### CF2000

（自行完成）

本题是对于正难则反的技巧运用。zlt 的 dp 确实好像更显然也更好做。~~但我复杂度低~~

想到正难则反就差不多做完了。

不合法方案其实完全就是在 $\le$ 下的偏序，分讨一下，不难做到 $O(n)$。

## [CF1591F  Non-equal Neighbours](https://www.luogu.com.cn/problem/CF1591F)

#### CF2400

> 世纪好题

设 $F_i$ 表示钦定有 $i$ 对 $b_j=b_{j+1}$，则答案为 $\sum_{i=0}^n(-1)^iF_i$。

若有一段连续的相同的数，可以将其合并为一个数。所以钦定有 $i$ 对 $b_j=b_j+1$ 就是将原序列变为 $\le n-i$ 段。则可以设 $dp_{i,j}$ 表示前 $i$ 个数，至多有 $j$ 段的方案数，则 $F_i=dp_{n,n-i}$。
$$
dp_{i,j}=\sum_{k=0}^{i-1} (dp_{k,j-1}\times \min_{l=k+1}^ia_l) \\
ans=\sum_{j=0}^n(-1)^{n-j} dp_{n,j}
$$
不难发现其实转移和答案只和 $j$ 的奇偶性相关，于是可以将状态改变为 $dp_{i,0/1}$ 表示前 $i$ 个数，钦定有**奇/偶**个 $b_k=b_{k+1}$。
$$
dp_{i,j}=\sum_{k=0}^{i-1} (dp_{k,j \oplus 1} \times \min_{l=k+1}^ia_l),j\in\{0,1\} \\
ans=\begin{cases}
dp_{n,0}-dp_{n,1} & n \bmod 2=0 \\
dp_{n,1}-dp_{n,0} & n \bmod 2=1
\end{cases}
$$
现在空间已经变为线性了，目前时间复杂度为 $O(n^3)$，使用 st 表后就是 $O(n^2)$，只需优化时间。

直接维护不太可能，但是看到转移式中的 $\min$ 可以想到尝试单调栈。

设 $lst$ 为最大的满足 $a_{lst}<a_i$ 的数，若没有则 $lst=0$。
$$
dp_{i,j}=\sum_{k=0}^{i-1} (dp_{k,j \oplus 1} \times \min_{l=k+1}^ia_l) \tag{0}
$$

$$
dp_{i,j}=\sum_{k=0}^{lst-1}(dp_{k,j \oplus 1} \times \min_{l=k+1}^{lst}a_l)+\sum_{k=lst}^{i-1} (dp_{k,j \oplus 1}) \times a_i \tag{1}
$$

$$
dp_{i,j}=dp_{lst,j}+\sum_{k=lst}^{i-1}(dp_{k,j\oplus1})\times a_i \tag{2}
$$

$(0)$ 是原式，$(1)$ 就是将 $(0)$ 中的 $k\in[0,i-1]$ 拆分成 $k\in[0,lst-1]\cup[lst,i-1]$，又因为 $a_{lst}<a_i$ 而进一步精准 $\min$ 的范围。

根据 $(0)$，$(2)$ 是将 $(1)$ 中的前半部分代换成 $dp_{lst,j}$。

现在只需算出 $(2)$ 即可，可以使用单调栈维护 $lst$，后半部分可以使用前缀和优化。

时间复杂度为 $O(n)$。

后记：真不能再咕了，真得好好写计数。

## [CF1906J Count BFS Graph](https://www.luogu.com.cn/problem/CF1906J)

#### CF2100

模拟赛不会做计数，wtcl！

这题是真的蠢，难点在 dp 状态定义。

$dp_{i,j}$ 表示目前 $u=i$，数列的前 $j$ 个数已经在队列中的方案数。

枚举可以从 $i$ 从 $j$ 拓展到 $k$ ，$k$ 可以和 $a_i$ 到 $a_j$ 选择是否连边，所以 $dp_{i+1,k}+=2^{j-i-1}dp_{i,j}(k \in[j,nxt_{j+1}])$ 。

区间加可以使用差分维护。$O(n^2)$。