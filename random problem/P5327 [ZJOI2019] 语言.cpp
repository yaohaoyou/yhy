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
const int maxn=1e5+10;
int n,m;
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
int tot;
int ft[maxn],dep[maxn],dfsn[maxn],rnk[maxn];
void dfs(int u,int fa){
    dfsn[u]=++tot;rnk[tot]=u;
    dep[u]=dep[ft[u]=fa]+1;
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u);
    }
}
namespace lca_build{
    const int lgN=18;
    int st[lgN+1][maxn],Log[maxn];
    inline int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][dfsn[i]]=ft[i];
        for(int i=1;i<=lgN;i++)
            for(int j=1;j<=n;j++)   st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(!x||!y)return 0;if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using lca_build::LCA;
int root[maxn];
vector<int> v[maxn];
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    int cur;
    int L[maxn<<6],R[maxn<<6],lc[maxn<<6],rc[maxn<<6],a[maxn<<6];
    ll tr[maxn<<6];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs]-dep[LCA(R[ls],L[rs])];L[p]=L[ls]?L[ls]:L[rs];R[p]=R[rs]?R[rs]:R[ls];}
    void update(int &p,int l,int r,int x,int s){
        if(!p)p=++cur;
        if(l==r){
            x=rnk[x];
            a[p]+=s;
            if(a[p])    L[p]=R[p]=x,tr[p]=dep[x];
            else    L[p]=R[p]=tr[p]=0;
            return;
        }
        setmid;(x<=mid)?update(lson,x,s):update(rson,x,s);pu(p);
    }
    void merge(int &p,int q,int l,int r){
        if(!p||!q)  return p|=q,void();
        if(l==r){
            a[p]+=a[q];
            if(a[p])    L[p]=R[p]=rnk[l],tr[p]=dep[rnk[l]];
            else    L[p]=R[p]=tr[p]=0;
            return;
        }
        setmid;
        merge(ls,lc[q],l,mid);merge(rs,rc[q],mid+1,r);pu(p);
    }
    inline ll query(int p){return tr[p]-dep[LCA(L[p],R[p])];}
}
using namespace SegmentTree;
ll ans;
void dfs2(int u,int fa){
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs2(t,u);
    }
    for(int i:v[u]) update(root[u],1,n,dfsn[i],-1);
    // printf("%d %d\n",u,query(root[u]));
    ans+=query(root[u]);
    if(fa)  merge(root[fa],root[u],1,n);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);lca_build::build();
    while(m--){
        int x,y;scanf("%d%d",&x,&y);
        update(root[x],1,n,dfsn[x],1);update(root[x],1,n,dfsn[y],1);
        update(root[y],1,n,dfsn[x],1);update(root[y],1,n,dfsn[y],1);
        int l=LCA(x,y);
        v[l].eb(x);v[l].eb(y);v[ft[l]].eb(x);v[ft[l]].eb(y);
    }
    dfs2(1,0);
    printf("%lld\n",ans>>1);
}