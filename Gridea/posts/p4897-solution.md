---
title: 'P4897 【模板】最小割树（Gomory-Hu Tree） '
date: 2024-07-03 19:16:27
tags: [题解,算法,网络流]
published: true
hideInList: false
feature: 
isTop: false
---
### [题目传送器](https://www.luogu.com.cn/problem/P4897)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/p4897-solution)

## 题意

给一个无向连通图，询问两点之间需要割掉多少边权能使两点不连通。

## 做法

因为连通性是可传递的，所以可以使用分治。

由于无向图两点间最小割 $=$ 最大流，所以使用网络最大流求最小割。

对于当前处理需要处理的点集 $s$，随意选两个点 $u$ 和 $v$ 跑一次网络最大流，设最大流为 $maxflow$，则在最小割树上建一条 $(u,v,maxflow)$ 边。设割掉满流的边后 $u$ 能遍历到的点集为 $s1$，剩下的点集 $s2=\complement_s s1$。往下递归处理 $s1$ 和 $s2$ 即可。求 $s1$ 可以找最后一次 dinic 的 bfs 遍历到的点。

现在已经建出了最小割树，考虑如何使用。当断掉一条边后，会花费当前边权的代价，将原树树断成两颗新树，这两棵新树上的点两两互相不连通。那对于求 $(u,v)$ 的最小割，只要断掉树上 $(u,lca(u,v))$ 和 $(lca(u,v),v)$ 这两条链中最小的一条边即可。可以使用倍增维护边权最小值。

## AC Code

```c
#include<bits/stdc++.h>
#define pii pair<int,int>
#define piii pair<int,pii>
#define eb emplace_back
using namespace std;
const int maxn=1e5+10;
const int maxm=maxn*100;
int n,m;
struct Tree{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}Tr;
namespace Graph{
    piii g[maxn];
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void rebuild(){cnt=1;memset(head,0,sizeof(head));for(int i=1;i<=m;i++){add(g[i].first,g[i].second.first,g[i].second.second);add(g[i].second.first,g[i].first,g[i].second.second);}}
}
using namespace Graph;
int S,T;
namespace DINIC{
    const int inf=0x3f3f3f3f;
    int d[maxn],now[maxn];
    queue<int> q;
    inline bool bfs(){
        while(!q.empty())   q.pop();
        memset(d,0x3f,sizeof(d));
        memcpy(now,head,sizeof(head));
        d[S]=0;
        q.push(S);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(d[t]!=inf||!e[i].w)  continue;
                d[t]=d[u]+1;
                q.push(t);
                if(t==T)    return true;
            }
        }
        return false;
    }
    int dfs(int u,int flw){
        if(u==T)    return flw;
        int res=0;
        for(int i=now[u];i&&flw;i=e[i].nxt){
            now[u]=i;
            int t=e[i].to;
            if(d[t]!=d[u]+1||!e[i].w)    continue;
            int k=dfs(t,min(e[i].w,flw));
            if(!k)  d[t]=inf;
            e[i].w-=k;e[i^1].w+=k;
            res+=k;flw-=k;
        }
        return res;
    }
    inline int dinic(){
        rebuild();
        int res=0;
        while(bfs())    res+=dfs(S,inf);
        return res;
    }
}
using namespace DINIC;
namespace DFS{
    int w[20][maxn],f[20][maxn],dep[maxn];
    void dfs(int u,int fa){
        dep[u]=dep[f[0][u]=fa]+1;w[0][u]=inf;
        for(int i=Tr.head[u];i;i=Tr.e[i].nxt){
            int t=Tr.e[i].to;
            if(t==fa)   continue;
            dfs(t,u);
            w[0][t]=Tr.e[i].w;
        }
    }
    inline void init_LCA(){for(int i=1;i<=19;i++)for(int j=1;j<=n;j++){w[i][j]=min(w[i-1][j],w[i-1][f[i-1][j]]);f[i][j]=f[i-1][f[i-1][j]];}}
    inline int LCA(int x,int y){  // O(nlogn) - O(logn) 倍增
        int res=inf;
        if(dep[x]<dep[y])   swap(x,y);
        for(int i=19;~i;i--){
            if(dep[f[i][x]]>=dep[y]){
                res=min(res,w[i][x]);
                x=f[i][x];
            }
        }
        if(x==y)    return res;
        for(int i=19;~i;i--){
            if(f[i][x]^f[i][y]){
                res=min(res,w[i][x]);res=min(res,w[i][y]);
                x=f[i][x];y=f[i][y];
            }
        }
        res=min(res,w[0][x]);res=min(res,w[0][y]);
        return res;
    }
}
vector<int> v,v1,v2;
void divide(int l,int r){
    v1.clear();v2.clear();
    if(l>=r)    return;
    S=v[l];T=v[l+1];
    int res=dinic();
    Tr.add(S,T,res);Tr.add(T,S,res);
    for(int i=l;i<=r;i++){
        if(d[v[i]]!=inf)   v1.eb(v[i]);
        else    v2.eb(v[i]);
    }
    for(int i=0;i<v1.size();i++)    v[i+l]=v1[i];
    for(int i=0;i<v2.size();i++)    v[i+l+v1.size()]=v2[i];
    int siz=v1.size();
    divide(l,l+siz-1);divide(l+siz,r);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d%d",&g[i].first,&g[i].second.first,&g[i].second.second);
    }
    for(int i=0;i<=n;i++)   v.eb(i);
    divide(0,n);
    DFS::dfs(1,0);
    DFS::init_LCA();
    int q;scanf("%d",&q);
    while(q--){
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%d\n",DFS::LCA(u,v));
    }
}
```



## 总结 

时间复杂度为 $O(n \times D)$，$O(D)$ 是 dinic 的时间复杂度，理论是 $O(n^2\times m)$，但实际上小很多。