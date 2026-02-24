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
const int maxn=5e4+10,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,k;
int a[maxn];
pii G[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int tot;
int fa[maxn],dfsn[maxn],dep[maxn],dd[maxn],rnk[maxn],siz[maxn],son[maxn],top[maxn];
void dfs1(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;
    dd[u]=imdel(qpow(dep[u],k),qpow(dep[u]-1,k));
    siz[u]=1;
    go(u,i){
        if (t==ft)    continue;
        dfs1(t,u);
        siz[u]+=siz[t];
        if (!son[u]||siz[son[u]]<=siz[t])   son[u]=t;
    }
}
void dfs2(int u,int tp){
    dfsn[u]=++tot;rnk[tot]=u;top[u]=tp;
    if (son[u])dfs2(son[u],tp);
    go(u,i)if(t!=fa[u]&&t!=son[u]){
        top[t]=t;
        dfs2(t,t);
    }
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],sum[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=imadd(tr[ls],tr[rs]);}
    inline void pt(int p,int s){madd(tr[p],immul(sum[p],s));madd(tag[p],s);}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){if(l==r)return sum[p]=dd[rnk[l]],void();setmid;build(lson);build(rson);sum[p]=imadd(sum[ls],sum[rs]);pu(p);}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p,1);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)madd(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
struct ques{int pos,x,id;}q[maxn<<1];
int ans[maxn];
void upd(int u,int v){
    while (top[u]!=top[v]){
        if (dep[top[u]]<dep[top[v]])swap(u,v);
        upd(all,dfsn[top[u]],dfsn[u]);
        u=fa[top[u]];
    }
    if (dep[u]>dep[v])    swap(u,v);
    upd(all,dfsn[u],dfsn[v]);
}
int qpath(int u,int v){
    int ans=0;
    while (top[u]!=top[v]){
        if (dep[top[u]]<dep[top[v]])swap(u,v);
        madd(ans,query(all,dfsn[top[u]],dfsn[u]));
        u=fa[top[u]];
    }
    if (dep[u]>dep[v])  swap(u,v);
    madd(ans,query(all,dfsn[u],dfsn[v]));
    return ans;
}
signed main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    dfs1(1,0);dfs2(1,1);build(all);
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        q[i]={x,y,i};
    }
    sort(q+1,q+m+1,[&](ques x,ques y){return x.pos<y.pos;});
    for (int i=1,now=0;i<=m;i++){
        while(now<q[i].pos) upd(1,++now);
        ans[q[i].id]=qpath(1,q[i].x);
    }
    for(int i=1;i<=m;i++)   printf("%d\n",ans[i]);
}
   