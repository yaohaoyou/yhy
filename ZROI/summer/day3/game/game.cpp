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
int pr[maxn],nx[maxn];
int f[maxn][2],fa[maxn],dep[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=dep[i]=deg[i]=0;cnt=1;}
}
using namespace Graph;
inline void era(int x){int pre=pr[x],nxt=nx[x];pr[nxt]=pre;nx[pre]=nxt;}
struct tree{
    int a[2][2];bool die;
    inline int* operator[](int x){return a[x];}
    tree operator+(tree y){
        if(die) return y;
        if(y.die)   return *this;
        tree res;res.die=false;
        for(int i:{0,1})for(int j:{0,1})res[i][j]=min(a[i][0]+y[0][j],a[i][1]+y[1][j]);
        return res;
    }
}a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    tree tr[maxn<<2];int pos[maxn];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    void build(setpos){if(l==r)return pos[l]=p,tr[p]=a[l],void();setmid;build(lson);build(rson);pu(p);}
    inline void upd(int x){int p=pos[x];tr[p]=a[x];while(p>>=1)pu(p);}
}
using namespace SegmentTree;
void matt(int _cases){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   pr[i]=i-1,nx[i]=i+1;
    pr[1]=n;nx[n]=1;
    for(int i=1;i<=n;i++){for(int j:{0,1})for(int k:{0,1})a[i][j][k]=j+k;a[i].die=false;}
    build(all);
    for(int i=1;i<=n-3;i++){
        int x;scanf("%d",&x);
        era(x);
        a[pr[x]]=a[pr[x]]+a[x];
        a[x].die=true;
        a[pr[x]][0][0]=1e9;
        upd(x);upd(pr[x]);
        printf("%d ",min(tr[1][0][0],tr[1][1][1])>>1);
    }
    puts("");
}
int main(){freopen("game.in","r",stdin);freopen("game.out","w",stdout);int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}