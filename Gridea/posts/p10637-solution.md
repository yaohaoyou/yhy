---
title: 'P10637 BZOJ4262 Sum'
date: 2024-07-05 09:27:59
tags: [题解,线段树,单调性]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P10637)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p10637-solution/)

## 前言

我什么也不会，不知道为什么 \_maojun\_ 要感谢我。但是我要感谢 [\_maojun\_](https://www.luogu.com.cn/user/350297) 提供思路。

## 题意

给出**随机的**数列 $a$，求 $\sum_{l \in [l_1,r_1]} \sum_{r \in [l_2,r_2]} (\max_{i \in [l,r]} a_i-\min_{i\in [l,r]} a_i)$。

## 做法

做法肯定和[这篇题解](https://www.luogu.com.cn/article/3wka43ys)一样，但我尝试说的更详细一点。

### conclusion 1

我会盯式子！

因为 $\max -a_i = -\min a_i$，所以只要会求 $\sum_{l \in [l_1,r_1]} \sum_{r \in [l_2,r_2]} \max_{i \in [l,r]} a_i$，然后将 $a_i=-a_i$，再做一遍，两遍答案加起来就是要输出的结果。

### conclusion 2

我会前缀和差分！

 $\sum_{l \in [l_1,r_1]} \sum_{r \in [l_2,r_2]} \max_{i \in [l,r]} a_i=\sum_{l \in [l_1,r_1]} \sum_{r \in [1,r_2]} \max_{i \in [l,r]} a_i-\sum_{l \in [l_1,r_1]} \sum_{r \in [1,l_2-1]} \max_{i \in [l,r]} a_i$。

也就是说设 $s(l,r,x)=\sum_{i \in [l,r]}\sum_{j \in [1,x]} \max_{k\in [i,j]} a_k$，答案可以变成 $s(l1,r1,r2)-s(l1,r1,l2-1)$。

现在只需会求 $s(l,r,x)$ 即可。

### conclusion 3

我会扫描线！

这个做法在线做好像非常复杂了，所以可以尝试用离线下来做。

将所有的 $s(l,r,x)$ 的询问挂在 $x$ 上，设 $f(i,x)=\sum_{j\in [i,x]} \max_{k \in [i,j]} a_k$，则 $s(l,r,x)=\sum_{i\in [l,r]} f(i,x)$。

当 $x++$ 时，$f(i,x)+=\max_{j\in [i,x]}a_j$，也就是当前的后缀 $[i,x]$ 最大值。所以 $f(i,x)=\max[i,i]+\max[i,i+1]+...+\max[i,x]=\sum_{j=i}^xmax[i,j]$，也就是**以 $i$ 为左端点**的后缀最大值的历史版本和。 所以 $s(l,r,x)$  为区间 $[l,r]$ 的历史版本和之和。

### conclusion 4

我会 beats + 历史版本和（线段树 3）！

直接做就行了，使用 beats 进行区间取 max，维护后缀最大值，线段树维护历史版本和，求 $s(l,r,x)$ 时在线段树上区间修改，时间复杂度为 $O(n\times \log_2^2n)$，瓶颈在使用 beats 进行区间取 max。

### conclusion 5

我会单调栈！

后缀 $[i,x]$ 具有单调性，可以使用单调栈维护后缀最大值，来替换 beats。由于每个位置只会入栈一次，所以复杂度为**大常数**的 $O(n \times \log_2n)$，瓶颈在维护历史版本和与区间查询，维护历史版本和的常数较大。

这里放一份 [\_maojun\_ 的代码](https://www.luogu.com.cn/record/162817348)。

### conclusion 6

我会观察性质！

注意 a 数列是随机生成的。~~众所周知~~可以证明，在数据随机数列中，使用单调栈维护前缀/后缀 min/max 值，单调栈的大小期望为 $O(\log_2n)$。

那就可以不使用常数较大的常规方式维护历史版本和了。对于当前一段后缀 max 相同的区间，区间内每个数对答案的贡献在目前都是相同的，对于每段区间维护一个时间戳，记录它是什么时候进入单调栈的。当这个区间被弹出时，在线段树上将这个区间的历史版本和更新。

与传统的历史版本和不同的是，现在只有在当前点被弹出时才在线段树上维护历史版本和。依然在单调栈中的点可以 $O(1)$ 计算贡献，而这种点又只有 $O(\log_2n)$ 种。

所以就获得了一种只需要区间修改和区间查询的线段树的做法，**相比之下常数更小**，复杂度为 $O(n \times \log_2n)$。可以将线段树改成 zkw 或超级树状数组。\_maojun\_ 使用了超级树状数组获得了[最优解](https://www.luogu.com.cn/record/163151201)。

## AC Code

```c
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define mem(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
constexpr int maxn=1e5+10;
int n,q;
ll a[maxn];
struct node{int l,r,k,id;};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setpos int p,int l,int r
    #define setmid int mid=(l+r)>>1
    ll tr[maxn<<2],tag[maxn<<2];
    inline void pushup(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pushtag(setpos,ll s){tr[p]+=(r-l+1)*s;tag[p]+=s;}
    inline void pushdown(setpos){if(!tag[p])return;setmid;pushtag(lson,tag[p]);pushtag(rson,tag[p]);tag[p]=0;}
    void update(setpos,int pl,int pr,ll s){
        if(l>=pl&&r<=pr)    return pushtag(p,l,r,s);
        pushdown(p,l,r);
        setmid;
        if(pl<=mid) update(lson,pl,pr,s);
        if(pr>mid)  update(rson,pl,pr,s);
        pushup(p);
    }
    ll query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return tr[p];
        pushdown(p,l,r);
        setmid;ll res=0;
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res+=query(rson,pl,pr);
        return res;
    }
}
using namespace SegmentTree;
namespace DataMaker{
    const int mod = 1e9;
    long long fst = 1023, sec = 1025;
    void solve(){
        for (int i = 1; i <= 100000; i++) {
            a[i] = fst ^ sec;
            fst = fst * 1023 % mod;
            sec = sec * 1025 % mod;
        }
    }
}
vector<node> v[maxn];
ll ans[maxn];
int stk[maxn],tp;
void solve(){
    mem(tr,0);mem(tag,0);tp=0;
    for(int i=1;i<=n;i++){
        while(tp&&a[stk[tp]]<=a[i]){
            update(all,stk[tp-1]+1,stk[tp],1ll*(i-stk[tp])*a[stk[tp]]);
            tp--;
        }
        stk[++tp]=i;
        for(auto [l,r,k,id]:v[i]){
            ll res=query(all,l,r);
            for(int j=1;j<=tp;j++){
                int len=min(stk[j],r)-max(stk[j-1],l-1);
                if(len<=0)   continue;
                res+=1ll*len*(i-stk[j]+1)*a[stk[j]];
            }
            ans[id]+=(res*k);
        }
    }
}
signed main(){
    scanf("%d",&q);
    n=1e5;
    DataMaker::solve();
    for(int i=1,l1,r1,l2,r2;i<=q;i++){
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        v[r2].eb(l1,r1,1,i);
        v[l2-1].eb(l1,r1,-1,i);
    }
    solve();
    for(int i=1;i<=n;i++)   a[i]*=-1;
    solve();
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}
```

## 总结

基于数组随机可以获得小常数的 $O(n\times \log_2n)$，不基于数组随机可以获得历史版本和做法的 $O(n \times \log_2n)$。

感谢 \_maojun\_ 的帮助，同时大力推荐[他的题解](https://www.luogu.com.cn/article/3wka43ys)。

*文中部分引用了他人的代码和提交记录，如有侵权行为，请及时私信博主，我会依法进行更改或删除。