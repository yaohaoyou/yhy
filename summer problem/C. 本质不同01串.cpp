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
const int maxn=1e6+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ull*res*x%mod;x=1ull*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int fac[maxn],inv[maxn];
inline int C(int x,int y){return x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int n,a,b;
int s[maxn];
namespace Sub1{
    bool check(){return !a;}
    void solve(){
        int cnt=1;for(int i=2;i<=n;i++) cnt+=(s[i]!=s[i-1]);
        printf("%d\n",C(cnt+b-1,cnt-1));
    }
}
namespace Sub2{
    bool check(){return !b;}
    void solve(){
        int cnt=0;for(int i=2;i<=n;i++) cnt+=(s[i]==s[i-1]);
        printf("%d\n",C(cnt,a));
    }
}
namespace Sub3{
    bool check(){return a==1&&b==1;}
    void solve(){
        int ans=0;
        int cnt=1,c1=0;for(int i=2;i<=n;i++) cnt+=(s[i]!=s[i-1]);
        for(int i=2;i<=n;i++)   c1+=(s[i]==s[i-1]);
        madd(ans,immul(c1,cnt+1));madd(ans,ans);mdel(ans,c1);
        printf("%d\n",ans);
    }
}
void matt(){
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++)   scanf("%1d",&s[i]);
    if(Sub1::check())   return Sub1::solve();
    if(Sub2::check())   return Sub2::solve();
    if(Sub3::check())   return Sub3::solve();
}
void init(){
    const int N=1e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}