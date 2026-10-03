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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
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
        pii tr[maxn<<2];
        ll sum[maxn<<2];
        int tag[maxn<<2];
        void pushup(int p){tr[p]=max(tr[ls],tr[rs]);sum[p]=sum[ls]+sum[rs];}
        void pushdown(int p,int l,int r){
            tag[ls]+=tag[p];
            tag[rs]+=tag[p];
            int mid=(l+r)>>1;
            sum[ls]+=1ll*(mid-l+1)*tag[p];
            tr[ls].fi+=tag[p];
            sum[rs]+=1ll*(r-mid)*tag[p];
            tr[rs].fi+=tag[p];
            tag[p]=0;
        }
        void build(int p,int l,int r){
            if(l==r){tr[p]=pii(0,l);return;}
            int mid=(l+r)>>1;
            build(lson);
            build(rson);
            pushup(p);
        }
        void update(int p,int l,int r,int pl,int pr,int s){
            if(pl<=l&&r<=pr){
                tr[p].fi+=s;
                tag[p]+=s;
                sum[p]+=1ll*s*(r-l+1);
                return;
            }
            pushdown(p,l,r);
            int mid=(l+r)>>1;
            if(pl<=mid) update(lson,pl,pr,s);
            if(pr>mid)  update(rson,pl,pr,s);
            pushup(p);
        }
        pii query(int p,int l,int r,int pl,int pr){
            if(pl<=l&&r<=pr)    return tr[p];
            pushdown(p,l,r);
            int mid=(l+r)>>1;pii res=pii(0,0);
            if(pl<=mid) res=query(lson,pl,pr);
            if(pr>mid)  res=max(res,query(rson,pl,pr));
            return res;
        }
    }
    using namespace SegmentTree;
}
using namespace BetaCutShit;
void slv1(int x,int y,int z){
    while(tp[x]!=tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        update(1,1,n,dfsn[tp[x]],dfsn[x],z);
        x=f[tp[x]];
    }
    if(dep[x]>dep[y])   swap(x,y);
    update(1,1,n,dfsn[x],dfsn[y],z);
}
vector<ll> ans;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    build(1,1,n);
    dfs1(1,0);tp[1]=1;dfs2(1);
    for(int i=1;i<=n;i++){
        if(siz[i]>1)update(1,1,n,dfsn[i]+1,dfsn[i]+siz[i]-1,1);
        if(i^1) slv1(1,f[i],1);
    }
    ll now=sum[1];
    for(int i=1;i<=n;i++){
        ans.eb(now>>1);
        int u=rnk[tr[1].se];
        now-=tr[1].fi<<1;
        // printf("%d %d\n",u,tr[1].fi);
        if(!tr[1].fi)   continue;
        //printf("u = %d\n",u);
        update(1,1,n,dfsn[u],dfsn[u],-tr[1].fi);
        if(siz[u]>1)update(1,1,n,dfsn[u]+1,dfsn[u]+siz[u]-1,-1);
        if(u^1) slv1(1,f[u],-1);
    }
    ans.eb(0);
    reverse(ans.begin(),ans.end());
    for(ll i:ans)   printf("%lld ",i);
}