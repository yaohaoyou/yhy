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
const int maxn=2e5+10;
int n,m,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
int tot;
int fa[20][maxn];ll dep[maxn];
int onlist[maxn];vector<int> lst;
ll L[maxn],R[maxn],b[maxn*3];int W[maxn];
pair<int,ll> rd[maxn];
void dfs(int u,int ft){
    fa[0][u]=ft;
    go(u,i){
        int t=e[i].to;if(t==ft) continue;
        dep[t]=dep[u]+e[i].w;
        dfs(t,u);
    }
}
void build(){
    for(int i=1;i<20;i++)
        for(int j=1;j<=n;j++)   fa[i][j]=fa[i-1][fa[i-1][j]];
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<4],tag[maxn<<4];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
}
using namespace SegmentTree;
inline void slv(int x,ll y,int s,int id){
    for(int i=19;~i;i--)
        if(fa[i][x]&&!onlist[fa[i][x]]) y-=dep[x]-dep[fa[i][x]],x=fa[i][x];
    if(!onlist[x])  y-=dep[x]-dep[fa[0][x]],x=fa[0][x];
    if(y<=0) return;
    L[id]=max(2ll,dep[x]-y+1);R[id]=min(dep[n],dep[x]+y);W[id]=s;
}
void discrete(){
    b[++m]=2;b[++m]=dep[n];
    for(int i=1;i<=q;i++)   if(L[i])b[++m]=L[i],b[++m]=R[i],b[++m]=min(dep[n],R[i]+1);
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=q;i++)   if(L[i])L[i]=lower_bound(b+1,b+m+1,L[i])-b,R[i]=lower_bound(b+1,b+m+1,R[i])-b;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    dep[1]=1;dfs(1,0);build();
    {
        int u=n;
        while(u){lst.eb(u);u=fa[0][u];}
        reverse(lst.begin(),lst.end());
        for(int i=0;i<lst.size();i++)   onlist[lst[i]]=i+1;
    }
    for(int o=1;o<=q;o++){
        int op,x;ll y;scanf("%d%d",&op,&x);
        if(op==1){
            scanf("%lld",&y);
            rd[o]=make_pair(x,y);
            slv(x,y,1,o);
        }
        else    slv(rd[x].fi,rd[x].se,-1,o);
    }
    discrete();
    for(int o=1;o<=q;o++){
        if(L[o])    upd(all,L[o],R[o],W[o]);
        puts(tr[1]?"YES":"NO");
    }
}