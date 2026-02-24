#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10,logV=31,mod=10086;
int n;
int a[maxn];
int x,cnt=1;
int p[logV+10];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
inline void ins(int x){for(int i=logV;~i;i--){if(!(x&(1<<i)))continue;if(!p[i])return p[i]=x,void();x^=p[i];if(!x)return madd(cnt,cnt),void();}}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){scanf("%lld",&x);ins(x);}
    scanf("%lld",&x);
    int ans=0,tp=1;
    for(int i=0;i<=logV;i++){
        if(!p[i])   continue;
        if(x&(1ll<<i))    madd(ans,tp);
        tp<<=1;
    }
    printf("%lld\n",imadd(immul(ans,cnt),1));
}