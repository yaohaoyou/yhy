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
const int maxn=510,maxm=1e6+10,mod=1e9+7;
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
int n,k;
int a[maxn];
int fac[maxm],inv[maxm];
void init(){
    const int N=1e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int calc(int x,int y,int k){return k>min(x,y)?0:1ull*C(x,k)*C(y,k)%mod*fac[k]%mod;}
int rt,ls[maxn],rs[maxn],fa[maxn],len[maxn],f[maxn][maxn],tmp[maxn];
int build(int l,int r){
    if(l>r)    return 0;
    int p=min_element(a+l,a+r+1)-a;
    len[p]=r-l+1;
    ls[p]=build(l,p-1);
    rs[p]=build(p+1,r);
    fa[ls[p]]=fa[rs[p]]=p;
    return p;
}
void dfs(int u){
    if(ls[u])   dfs(ls[u]);
    if(rs[u])   dfs(rs[u]);
    mems(tmp,0);
    for(int i=0;i<=k;i++)for(int j=0;i+j<=k;j++)if(f[ls[u]][i]&&f[rs[u]][j])madd(tmp[i+j],immul(f[ls[u]][i],f[rs[u]][j]));
    int h=a[u]-a[fa[u]],w=len[u];
    for(int i=0;i<=k&&i<=min(h,w);i++)for(int j=0;i+j<=k;j++)madd(f[u][i+j],immul(calc(h,w-j,i),tmp[j]));
}
int main(){
    init();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    rt=build(1,n);
    f[0][0]=1;dfs(rt);
    printf("%d\n",f[rt][k]);
}