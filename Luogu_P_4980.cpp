#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int mod=1e9+7;
int n,ans;
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
inline int phi(int x){
    int ret=x;
    for(int i=2;i*i<=x;i++){
        if(x%i)  continue;
        ret=ret/i*(i-1);
        while(x%i==0)x/=i;
    }
    if(x^1) ret=ret/x*(x-1);
    return ret;
}
void MakeFactors(){
    for(int i=1;i*i<=n;i++){
        if(n%i!=0)  continue;
        madd(ans,immul(qpow(n,i),phi(n/i)));
        if(i*i!=n)  madd(ans,immul(qpow(n,n/i),phi(i)));
    }
}
void solve(){
    ans=0;
    scanf("%d",&n);
    MakeFactors();mmul(ans,qpow(n,mod-2));
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)solve();}