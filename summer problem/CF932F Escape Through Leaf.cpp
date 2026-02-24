#include<bits/stdc++.h>
#define db double
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
const int maxn=1e5+10,V=2e5+10;
int n;
int a[maxn],b[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
struct line{int k;ll b;}l[maxn];
inline int cmp(line x,line y,int point){ll xx=1ll*x.k*point+x.b,yy=1ll*y.k*point+y.b;return xx<yy?-1:1;}
inline bool cmp(int x,int y,int p){int rt=cmp(l[x],l[y],p);return rt<0;}
namespace SegmentTree{
    const int L=-1e5,R=1e5;
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,L,R
    #define pos p,l,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int clr[V<<2],ccnt;
    int tr[V<<2];
    void upd(setpos,int u){
        clr[++ccnt]=p;
        setmid,&v=tr[p];
        if(cmp(u,v,mid)) swap(u,v);
        if(cmp(u,v,l))   upd(lson,u);
        if(cmp(u,v,r))   upd(rson,u);
    }
    void update(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return upd(pos,s);setmid;if(pl<=mid)update(lson,pl,pr,s);if(pr>mid)update(rson,pl,pr,s);}
    inline int query(int x){int p=1,l=L,r=R,ret=0;while(l^r){if(cmp(tr[p],ret,x))ret=tr[p];setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}if(cmp(tr[p],ret,x))ret=tr[p];return ret;}
}
using namespace SegmentTree;
int c;
inline void ins(int k,ll b){l[++c]={k,b};update(all,L,R,c);}
inline void clear(){for(int i=1;i<=ccnt;i++)tr[clr[i]]=0;c=ccnt=0;}
int son[maxn],siz[maxn];
ll dp[maxn];
void dfs1(int u,int ft){
    siz[u]=1;
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs1(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])   son[u]=t;
    }
}
void dfs3(int u,int ft){
    ins(b[u],dp[u]);
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs3(t,u);
    }
}
void dfs2(int u,int ft,bool keep){
    if(!son[u]){
        dp[u]=0;
        if(keep)    ins(b[u],dp[u]);
        return;
    }
    go(u,i){
        int t=e[i].to;
        if(t==ft||t==son[u])    continue;
        dfs2(t,u,false);
    }
    if(son[u])  dfs2(son[u],u,true);
    go(u,i){
        int t=e[i].to;
        if(t==ft||t==son[u])    continue;
        dfs3(t,u);
    }
    int x=query(a[u]);
    dp[u]=1ll*l[x].k*a[u]+l[x].b;
    if(!keep)   clear();
    else    ins(b[u],dp[u]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    l[0]={(int)1e9,(ll)1e18};
    dfs1(1,0);dfs2(1,0,false);
    for(int i=1;i<=n;i++)   printf("%lld ",dp[i]);
}