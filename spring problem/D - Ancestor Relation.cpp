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
const int maxn=410,mod=998244353;
int n;
int fac[maxn];
pair<bitset<maxn>,int> a[maxn];
bitset<maxn> bb[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
void init(){
    fac[0]=1;
    for(int i=1;i<=maxn-10;i++) fac[i]=immul(fac[i-1],i);
}
bool cmp(pair<bitset<maxn>,int> x,pair<bitset<maxn>,int> y){
    for(int i=1;i<=n;i++)
        if(x.fi[i]^y.fi[i])   return x.fi[i]<y.fi[i];
    return x.se<y.se;
}
bool no;
void divide(vector<int> v){
    // printf("v : ");for(int i:v)printf("%d ",i);puts("");
    if(v.empty())   return;
    bitset<maxn> vis;vis.reset();
    int m=v.size();
    for(int i:v){
        int tot=0;
        for(int j:v)tot+=bool(bb[i][j]);
        if(tot==m)   vis.set(i);
    }
    // printf("cnt = %d %d\n",vis.count(),vis.any());
    if(!vis.any())  return no=true,void();
    vector<int> path;
    for(int i:v){
        if(vis[i]) continue;
        path.clear();
        auto dfs=[&](auto& dfs,int u) -> void{
            vis.set(u);path.eb(u);
            for(int t:v)if(bb[u][t]&&!vis[t])dfs(dfs,t);
        };
        dfs(dfs,i);
        divide(path);
    }
}
int dep[maxn],ft[maxn];
bool check(){
    no=false;
    for(int i=1;i<=n;i++)
        if(!bb[1][i])    return false;
    vector<int> vec;vec.clear();
    for(int i=1;i<=n;i++)   vec.eb(i);
    divide(vec);
    return !no;
}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   a[i].fi.reset(),bb[i].reset();
    for(int i=1;i<=n;i++)   a[i].se=i;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){int x;scanf("%d",&x);a[i].fi[j]=x;bb[i][j]=x;}
    if(!check()) return puts("0"),void();
    int ans=1;
    sort(a+2,a+n+1,cmp);
    for(int i=2;i<=n;i++){
        int j=i;
        while(a[j].fi==a[i].fi)j++;
        j--;
        mmul(ans,fac[j-i+1]);
        i=j;
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}