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
const int maxn=2e5+10,maxm=2e6+10,mod=1e9+7;
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
int n,m;
int deg[maxn],buc[maxm];
int a[maxm],len;
inline int f(int x,int y){return immul(x^y,immul(x&y,x|y));}
int main(){
    freopen("gen.in","r",stdin);freopen("gen.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);deg[u]++;deg[v]++;}
    for(int i=1;i<=n;i++)   buc[deg[i]]++;
    for(int i=1;i<=m;i++)if(buc[i])a[++len]=i;
    assert(1ll*len*len<=m*4);
    int ans=0;
    for(int i=1;i<=len;i++){
        for(int j=i+1;j<=len;j++){
            madd(ans,1ull*f(a[i],a[j])*buc[a[i]]%mod*buc[a[j]]%mod);
        }
    }
    printf("%d\n",ans);
}