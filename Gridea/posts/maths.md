---
title: '数学学习笔记'
date: 2024-07-10 21:53:28
tags: [算法]
published: true
hideInList: false
feature: 
isTop: false
---
## 狄利克雷卷积 Dirichlet

### 定义：

其本质是一种运算，可以用 $*$  表示。
$$
h(x)=f(x)*g(x)=\sum_{d|x}f(d)g(\frac{x}{d})=\sum_{ab=x}f(a)g(b)
$$


积性函数 $f(x)$ 满足 $\forall (a,b)=1,f(ab)=f(a)f(b)$。

完全积性函数 $f(x)$ 满足 $f(ab)=f(a)f(b)$。

可以使用线性筛算出积性函数。

### 性质：

交换律：$f*g=g*f$。

结合律：$(f*g)*h=f*(g*h)$。

**分配律**：$(f+g)*h=f*h+g*h$。

若 $f$ 和 $g$ 是积性函数，则 $f*g$ 也是积性函数。

若 $f$ 是积性函数，则 $f$ 的逆元也是积性函数。

### 逆元：

单位函数 $\varepsilon$，$f*\varepsilon =f$。

若 $g$ 满足 $f*g=\varepsilon$，则称 $g(x)$ 是 $f(x)$ 的逆元。逆元唯一。

ps：目前还不太懂这是什么，但好像可以理解为 $\varepsilon(n)=\begin{cases}1&n=1\\0&n\not=1\end{cases}$。
$$
g(x)=
\dfrac{\varepsilon(x)-\sum_{d|x,d\not=1} f(d)f(\dfrac{x}{d})}{1}
$$

## 莫比乌斯函数 Möbius

### 定义式：

$$
n=p_1^{a_1}p_2^{a_2}...p_k^{a_k}\\
\mu(n)=\begin{cases}
1 &n=1 \\
0 & \exist i \le k,a_i>1 \\
(-1)^k& else
\end{cases}
$$

### 性质：

$\mu(x)$ 是积性函数。
$$
\sum_{d|n}\mu(d)=\begin{cases}1&n=1\\0&n\not=1\end{cases}
$$
即 $\sum_{d|n}\mu(d)=\varepsilon(n),\mu*1=\varepsilon$。在狄利克雷卷积中，莫比乌斯函数是常数函数 $1$ 的逆元。

#### 证明

$$
n=p_1^{a_1}p_2^{a_2}...p_k^{a_k},n'=p_1p_2...p_k\\
\because \mu(k \times a^2)=0 \\
\therefore \sum_{d|n}\mu(d)=\sum_{d|n'}\mu(d)
$$

则现在就是尝试在 $k$ 个互异质数中选择一个集合，若集合大小为奇数，答案 -1，否则答案 +1。$k>1$ 时，$\sum_{d|n'}\mu(d)=\sum_{i=0}^k\binom{k}{i}\times(-1)^i$。二项式定理是 $(a+b)^n=\sum_{i=0}^n\binom{n}{i}a^ib^{n-i}$，将 $a=-1,b=1$ 带入则是 $(1+(-1))^n=\sum_{i=0}^n\binom{n}{i}\times(-1)^i=0$。故 $k>1$ 时，$\sum_{d|n}\mu(d)=0$。剩下情况不难自证。

ps：以上证明只是本人在初学时的结论，不保证正确，等待未来的我修改或确认。

### 反演结论：

$$
[\gcd(i,j)=1]=\sum_{d|\gcd(i,j)}\mu(d)
$$

还不会用。。。

##  阶

### 定义

由欧拉定理可知，$(a,m)=1$，$a^{\varphi(m)} \equiv 1(\bmod m)$。故存在最小正整数满足 $a^n \equiv 1(\bmod m)$，称 $n$ 为 $a$ 模 $m$ 的阶，记作 $\operatorname{ord}_m(a)$。

### 性质

$a,a^2...a^{\operatorname{ord}_m(a)}$ 模 $m$ 两两不同余。

若 $a^p \equiv a^q(\bmod m)$，则 $p\equiv q(\bmod \operatorname{ord}_m(a))$。
$$
(a,m)=(b,m)=1 \\
\operatorname{ord}_m(ab)=\operatorname{ord}_m(a)\operatorname{ord}_m(b) \Leftrightarrow gcd(\operatorname{ord}_m(a),\operatorname{ord}_m(b))=1
$$

## 原根 primitive-root

### 定义

若 $(g,m)=1$，且 $\operatorname{ord}_m(g)=\varphi(m)$，则称 $g$ 为模 $m$ 的原根。

### 性质

对于 $m \ge 3,(g,m)=1$，则 $g$ 是模 $m$ 的原根 $\Leftrightarrow$ 对于 $\varphi(m)$ 的每个质因子 $p$，都有 $g^{\frac{\varphi(m)}{p}} \not\equiv 1(\bmod m)$。

若 $m$ 有原根，则原根个数为 $\varphi(\varphi(m))$。

原根存在定理：一个数 $m$ 存在原根当且仅当 $m=2,4,p^a,2p^a$，$p$ 为奇质数。

$a$ 的最小原根大约在 $a^{\frac{1}{4}}$。