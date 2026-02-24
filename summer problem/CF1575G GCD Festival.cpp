#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
using namespace __gnu_pbds;
const int maxn=1e5+10,V=1e5,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],mu[maxn];
bool ntpri[maxn];
vector<int> d[maxn],p;
cc_hash_table<int,int> f[maxn];
void seive(){
    const int N=1e5;
    mu[1]=1;
    for(int i=2;i<=N;i++){
        if(!ntpri[i])   p.eb(i),mu[i]=-1;
        for(int j:p){
            if(1ll*i*j>N)   break;
            ntpri[i*j]=true;
            if(i%j==0){mu[i*j]=0;break;}
            else mu[i*j]=-mu[i];
        }
    }
    for(int i=1;i<=N;i++)if(mu[i])for(int j=i;j<=N;j+=i)d[j].eb(i);
}
int main(){
    scanf("%d",&n);
    seive();
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int ans=0;
    for(int i=1;i<=n;i++)for(int x:d[i])for(int y:d[a[i]])f[x][y]++;
    for(int i=1;i<=n;i++)for(pii x:f[i]){
        int w=1ull*i*x.fi%mod*x.se%mod*x.se%mod;
        printf("%d %d : %d %d\n",i,x.fi,mu[i]*mu[x.fi],w);
        if(mu[i]*mu[x.fi]==1)   madd(ans,w);
        else mdel(ans,w);
    }
    printf("%lld\n",ans);
}