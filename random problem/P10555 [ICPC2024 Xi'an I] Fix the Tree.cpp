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
const int maxn=1e6+10;
int n;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int tot;
int dfsn[maxn],rnk[maxn],siz[maxn],f[maxn];
void dfs(int u,int fa){
    dfsn[u]=++tot;rnk[dfsn[u]]=u;f[u]=fa;siz[u]=1;
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
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
    pii tr[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    void build(setpos){if(l==r)return tr[p]=pii(a[rnk[l]],l),void();setmid;build(lson);build(rson);pu(p);}
    void update(setpos,int x,int s){if(l==r)return tr[p].fi+=s,void();setmid;(x<=mid)?update(lson,x,s):update(rson,x,s);pu(p);}
    pii query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;pii res=pii(1e9,0);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=min(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);build(all);
    for(int u=1;u<=n;u++){
        if(deg[u]==1){printf("0 ");continue;}
        ll ans=0;
        update(all,dfsn[u],1e9);
        vector<int> init;
        go(u,i){
            int t=e[i].to;
            pii x=pii(1e9,1e9);
            if(t==f[u]){
                if(dfsn[u]>1) x=query(all,1,dfsn[u]-1);
                if(dfsn[u]+siz[u]<=n)   x=min(x,query(all,dfsn[u]+siz[u],n));
            }
            else    x=query(all,dfsn[t],dfsn[t]+siz[t]-1);
            ans+=x.fi;update(all,x.se,1);init.eb(x.se);
        }
        for(int i=1;i<=deg[u]-2;i++){
            pii x=tr[1];
            ans+=x.fi;update(all,x.se,1);init.eb(x.se);
        }
        update(all,dfsn[u],-1e9);
        for(int i:init) update(all,i,-1);
        printf("%lld ",ans);
    }
}