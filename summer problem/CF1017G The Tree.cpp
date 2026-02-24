#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,inf=1e9;
int n,q;
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int tot;
int fa[maxn],dfsn[maxn],dep[maxn],siz[maxn],son[maxn],tp[maxn];
void dfs1(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;siz[u]=1;
    go(u,i){dfs1(t,u);siz[u]+=siz[t];if(siz[t]>siz[son[u]])son[u]=t;}
}
void dfs2(int u){
    dfsn[u]=++tot;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u]);
    go(u,i){
        if(t==son[u])   continue;
        tp[t]=t;
        dfs2(t);
    }
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define pos p,l,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{
        int sum,suf;
        inline tree operator+(tree y){return (tree){sum+y.sum,max(suf+y.sum,y.suf)};}
        inline void operator+=(tree y){*this=*this+y;}
    }tr[maxn<<2];
    bool tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(setpos){tr[p]={-(r-l+1),-1};tag[p]=true;}
    inline void pd(setpos){if(tag[p]){setmid;pt(lson);pt(rson);tag[p]=false;}}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){pd(pos);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p].sum-=s;tr[p].suf-=s;while(p>>=1)pu(p);}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(pos);pd(pos);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(pos);setmid;tree res={0,-inf};if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
}
using namespace SegmentTree;
inline tree qpath(int x){
    tree res={0,-inf};
    while(tp[x]^1){
        // res+=query(all,dfsn[tp[x]],dfsn[x]);
        res=query(all,dfsn[tp[x]],dfsn[x])+res;
        x=fa[tp[x]];
    }
    res=query(all,dfsn[tp[x]],dfsn[x])+res;
    return res;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);add(x,i);}
    dfs1(1,0);tp[1]=1;dfs2(1);
    upd(all,1,n);
    while(q--){
        int op,x;scanf("%d%d",&op,&x);
        if(op==1)   upd(dfsn[x],-1);
        if(op==2){if(son[x])upd(all,dfsn[x]+1,dfsn[x]+siz[x]-1);upd(dfsn[x],qpath(x).suf+1);}
        if(op==3)   puts(qpath(x).suf>=0?"black":"white");
        // for(int i=1;i<=n;i++)   printf("%d ",qpath(i).suf);puts("");
        // printf("%d\n",query(all,1,2).sum);
    }
}