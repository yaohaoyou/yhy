//  P3384 【模板】重链剖分/树链剖分
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;
int n, m, q, r, mod;
int a[maxn];
namespace Graph
{
    int head[maxn];
    int cnt;
    struct edge
    {
        int nxt, to;
    } e[maxn << 1];
    void add(int u, int v)
    {
        e[++cnt] = {head[u], v};
        head[u] = cnt;
    }
}
using namespace Graph;

namespace BetaCutShit{
    namespace Dfs{
        int dfsn[maxn],rnk[maxn],son[maxn],dep[maxn],siz[maxn],f[maxn],tp[maxn],L[maxn],R[maxn];
        int tot;
        void dfs1(int u,int fa){
            f[u]=fa;dep[u]=dep[fa]+1;siz[u]=1;
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(t==fa)   continue;
                dfs1(t,u);
                siz[u]+=siz[t];
                if(!son[u]||siz[t]>siz[son[u]]) son[u]=t;
            }
        }
        void dfs2(int u){
            dfsn[u]=++tot;rnk[tot]=u;
            if(!son[u]) return;
            tp[son[u]]=tp[u];
            dfs2(son[u]);
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(t==son[u]||t==f[u])   continue;
                tp[t]=t;
                dfs2(t);
            }
        }
    }
    using namespace Dfs;
    namespace SegmentTree{
        #define ls p<<1
        #define rs p<<1|1
        #define lson ls,l,mid
        #define rson rs,mid+1,r
        int tr[maxn<<2],tag[maxn<<2];
        void pushup(int p){tr[p]=tr[ls]+tr[rs];tr[p]%=mod;}
        void pushdown(int p,int l,int r){
            tag[ls]+=tag[p];
            tag[ls]%=mod;
            tag[rs]+=tag[p];
            tag[rs]%=mod;
            int mid=(l+r)>>1;
            tr[ls]+=tag[p]*(mid-l+1);
            tr[ls]%=mod;
            tr[rs]+=tag[p]*(r-mid);
            tr[rs]%=mod;
            tag[p]=0;
        }
        void build(int p,int l,int r){
            if(l==r){
                // printf("%lld %lld\n",l,a[rnk[l]]);
                tr[p]=a[rnk[l]]%mod;
                return;
            }
            int mid=(l+r)>>1;
            build(lson);
            build(rson);
            pushup(p);
        }
        void update(int p,int l,int r,int pl,int pr,int s){
            if(pl<=l&&r<=pr){
                tr[p]+=s*(r-l+1);
                tr[p]%=mod;
                tag[p]+=s;
                tag[p]%=mod;
                return;
            }
            pushdown(p,l,r);
            int mid=(l+r)>>1;
            if(pl<=mid) update(lson,pl,pr,s);
            if(pr>mid)  update(rson,pl,pr,s);
            pushup(p);
        }
        int query(int p,int l,int r,int pl,int pr){
            if(pl<=l&&r<=pr){
                return tr[p];
            }
            pushdown(p,l,r);
            int mid=(l+r)>>1,res=0;
            if(pl<=mid) res+=query(lson,pl,pr);
            res%=mod;
            if(pr>mid)  res+=query(rson,pl,pr);
            pushup(p);
            return res%mod;
        }
    }
    using namespace SegmentTree;
}
using namespace BetaCutShit;
namespace Solve{
    void slv1(int x,int y,int z){
        z%=mod;
        while(tp[x]!=tp[y]){
            if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
            update(1,1,n,dfsn[tp[x]],dfsn[x],z);
            x=f[tp[x]];
        }
        if(dep[x]>dep[y])   swap(x,y);
        update(1,1,n,dfsn[x],dfsn[y],z);
    }
    int slv2(int x,int y){
        int res=0;
        while(tp[x]!=tp[y]){
            if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
            res+=query(1,1,n,dfsn[tp[x]],dfsn[x]);
            x=f[tp[x]];
        }
        if(dep[x]>dep[y])   swap(x,y);
        res+=query(1,1,n,dfsn[x],dfsn[y]);
        return res%mod;
    }
    void slv3(int x,int s){
        s%=mod;
        update(1,1,n,dfsn[x],dfsn[x]+siz[x]-1,s);
    }
    int slv4(int x){
        return query(1,1,n,dfsn[x],dfsn[x]+siz[x]-1);
    }
}
using namespace Solve;
signed main()
{
    scanf("%lld%lld%lld%lld", &n, &q, &r, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs1(r,r);
    tp[r]=r;
    dfs2(r);
    // for(int i=1;i<=n;i++)   printf("%d ",f[i]);
    // puts("");
    build(1,1,n);
    while(q--){
        int opt,x,y,z;
        scanf("%lld%lld",&opt,&x);
        if(opt==1){
            scanf("%lld%lld",&y,&z);
            slv1(x,y,z);
        }
        else if(opt==2){
            scanf("%lld",&y);
            printf("%lld\n",slv2(x,y));
        }
        else if(opt==3){
            scanf("%lld",&z);
            slv3(x,z);
        }
        else    printf("%lld\n",slv4(x));
    }
}