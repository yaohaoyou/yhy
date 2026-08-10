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
const int N=2e5,V=1e6;
const int maxn=2e5+10,maxv=1e6+10,mod=1e9+7;
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
int n,k,q;
int a[maxn];
int fac[maxn],inv[maxn];
int cnt[maxv],phi[maxv];
vector<int> fact[maxv],pri;
void init(){
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    for(int i=1;i<=V;i++)for(int j=i;j<=V;j+=i)fact[j].eb(i);
    phi[1]=1;
    for(int i=2;i<=V;i++){
        if(!phi[i]) pri.eb(i),phi[i]=i-1;
        for(int j:pri){
            if(1ll*i*j>V)   break;
            if(i%j==0){phi[i*j]=phi[i]*j;break;}
            phi[i*j]=phi[i]*phi[j];
        }
    }
}
inline int C(int x,int y){return x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    init();
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        for(int j:fact[a[i]])   cnt[j]++;
    }
    int ans=0;
    for(int i=1;i<=V;i++)   madd(ans,immul(phi[i],C(cnt[i],k)));
    while(q--){
        int x;scanf("%d",&x);
        for(int i:fact[x]){
            mdel(ans,immul(phi[i],C(cnt[i],k)));
            cnt[i]++;
            madd(ans,immul(phi[i],C(cnt[i],k)));
        }
        printf("%d\n",ans);
    }
}