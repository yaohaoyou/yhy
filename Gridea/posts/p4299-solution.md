---
title: 'P4299 首都 题解'
date: 2025-11-19 07:39:45
tags: [题解,树上问题]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P4299)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p4299-solution)

## 前言

怎么清一色 LCT 做法，还有一个看上去很麻烦的树剖+线段树合并，下面给一种好写好想的树上倍增双 $\log$ 做法。

## 题意

动态加边维护树的重心。

## 做法

根据经典结论，合并两棵树后新的重心会在原本两棵树的重心的路径上，所以可以考虑使用倍增或二分求出新的重心。具体地，将询问离线下来把树建出来，每次连接一条新边 $(u,v)\mid dep_u\le dep_v$ 时就是将 $v$ 的树以 $v$ 为根并到 $u$ 上，这里令当前 $u$ 所在的树的根为 $rt$，首先动态维护 $siz$，直接做是链加单点查，但是经典方法是将其差分后改为用树状数组维护单点加子树查。

接下来令 $u$ 所在树原本的重心为 $wc_u$，$v$ 的为 $wc_v$，$lca\gets \operatorname{LCA}(wc_u,wc_v)$，首先特判掉 $wc_u=lca \vee wc_v=lca$ 的情况，然后令 $tu$ 为 $lca$ 在 $wc_u$ 方向上的儿子，$tv$ 同理，易得 $siz_{tu}+siz_{tv}+1=siz_{rt}$，所以 $\min(siz_{tu},siz_{tv})<\frac{siz_u}{2}$，而又有重心的判定 $siz_{wc}\ge \frac{siz_u}2$，所以可以直接判断出新的重心在 $tu$ 的子树内还是 $tv$ 的子树内，并可以判断出在哪一条链上，若 $wc_u=lca\vee wc_v =lca$ 就肯定在 $wc_u\leadsto wc_t$ 的路径上。

知道了新的重心在哪一条路径上就可以直接倍增了，找到深度最大的满足 $2siz_u\ge siz_{rt}$ 的 $u$ 即为重心，注意特判两个重心的情况，即若 $2siz_u=siz_{rt}$ 则 $u$ 的父亲也是重心。两种询问使用并查集在修改时维护即可。

时间复杂度为 $\mathcal O(n\log n+m\log^2n)$，瓶颈在倍增时的树状数组查询，空间树上倍增数组需要 $\mathcal O(n\log n)$。

[Code](https://www.luogu.com.cn/paste/c1xbjf7g)