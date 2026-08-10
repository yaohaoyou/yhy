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
const int maxn=3e5+10;
const ll INF=1e18;
int n,m;
int a[maxn],mxd[maxn],son[maxn],dep[maxn],dd[maxn],tp[maxn];
struct node{int u,r,w;}b[maxn];
vector<pii> v[maxn];
// vector<ll> dp[maxn];  // dp[u][i] 表示 u 的子树内，从祖先有一个 [dep[u],dep[u]+i-1] 的限制的答案
inline int rev(int x,int y){return dd[y]-x;}
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) 1,0,dd[tp[x]]
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{ll mx,tag1,tag2,used;};
    vector<tree> tr;
    inline void pd(int p){
        if (tr[p].used){
            tr[ls].tag1=tr[rs].tag1=tr[p].tag1;
            tr[ls].tag2=tr[rs].tag2=tr[p].tag2;
            tr[ls].mx=tr[rs].mx=tr[p].tag1+tr[p].tag2;
            tr[ls].used=tr[rs].used=1;
        }
        else{
            tr[ls].tag2+=tr[p].tag2;tr[rs].tag2+=tr[p].tag2;
            tr[ls].mx+=tr[p].tag2;tr[rs].mx+=tr[p].tag2;
        }
        tr[p].tag1=INF;tr[p].tag2=0;tr[p].used=0;
    }
    inline void pu(int p){tr[p].mx=max(tr[ls].mx,tr[rs].mx);}

    void updass(setpos,int x,int y,ll s)
    {
        if (x<=l&&y>=r){tr[p].mx=s;tr[p].tag1=s;tr[p].tag2=0;tr[p].used=1;return;}
        pd(p);
        setmid;
        if (x<=mid)updass(lson,x,y,s);
        if (y>mid)updass(rson,x,y,s);
        pu(p);
    }
    void updadd(setpos,int x,int y,ll s)
    {
        if (x<=l&&y>=r){tr[p].mx += s;tr[p].tag2 += s;return;}
        pd(p);
        setmid;
        if (x<=mid)updadd(lson,x,y,s);
        if (y>mid)updadd(rson,x,y,s);
        pu(p);
    }
    inline ll query(setpos,int x){while(l^r){setmid;pd(p);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p].mx;}
    int binary(setpos,int pl,int pr,ll s){
        if(tr[p].mx<s)  return -1;
        if(l==r)    return l;
        pd(p);setmid;
        if(l>=pl&&r<=pr)   return (tr[ls].mx>=s)?binary(lson,pl,pr,s):binary(rson,pl,pr,s);
        if(pl<=mid&&tr[ls].mx>=s)   return binary(lson,pl,pr,s);
        if(pr>mid)  return binary(rson,pl,pr,s);
        return -1;
    }
    inline void build(int siz){tr.resize(siz<<2|1);}
}T[maxn];
inline void updadd(int u,int pl,int pr,ll s){if(pl<=pr)T[tp[u]].updadd(all(u),pl,pr,s);}
inline void updass(int u,int pl,int pr,ll s){if(pl<=pr)T[tp[u]].updass(all(u),pl,pr,s);}
inline ll query(int u,int x){return T[tp[u]].query(all(u),x);}
inline int binary(int u,int pl,int pr,ll s){return T[tp[u]].binary(all(u),pl,pr,s);}
void dfs1(int u,int ft){
    dep[u]=dep[ft]+1;
    mxd[u]=max(mxd[u],dep[u]);
    go(u,i){
        if(t==ft)   continue;
        dfs1(t,u);
        mxd[u]=max(mxd[u],mxd[t]);
        if(mxd[t]>mxd[son[u]])  son[u]=t;
    }
    dd[u]=mxd[u]-dep[u]+1;
}
void dfs2(int u,int ft){
    if(tp[u]==u)    T[tp[u]].build(dd[u]+2);
    if(son[u]){
        tp[son[u]]=tp[u];dfs2(son[u],u);
        updass(u,dd[u],dd[u],query(u,dd[u]-1));
    }
    go(u,i)if((t^ft)&&(t^son[u]))tp[t]=t,dfs2(t,u);
    go(u,i){
        if(t==ft||t==son[u])   continue;
        for(int j=0;j<=dd[t];j++)   updadd(u,rev(j+1,u),rev(j+1,u),query(t,rev(j,t)));
        updadd(u,rev(0,u),rev(0,u),query(t,rev(0,t)));
        updadd(u,0,dd[u]-dd[t]-2,query(t,rev(dd[t],t)));
    }
    updadd(u,rev(0,u),rev(0,u),a[u]);
    sort(v[u].begin(),v[u].end(),greater<pii>());
    for(pii x:v[u]){
        int r=x.fi,w=x.se;ll d=query(u,rev(r+1,u));
        int p=binary(u,dd[u]-min(r,dd[u]),dd[u],w+d);
        if(!~p) p=dd[u]+1;
        updadd(u,p,dd[u],-w);updass(u,dd[u]-min(r,dd[u]),p-1,d);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d%d%d",&b[i].u,&b[i].r,&b[i].w),v[b[i].u].eb(b[i].r,b[i].w);
    dfs1(1,0);tp[1]=1;dfs2(1,0);
    printf("%lld\n",query(1,rev(0,1)));
}