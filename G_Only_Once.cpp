#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
int n,mod;
int ans,s=1;
namespace MyMod{
    inline void madd(int &x,int y){(x+=y)%=mod;}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace MyMod;
int main(){
    scanf("%d%d",&n,&mod);
    for(int i=1;i<=n;i++){
        madd(ans,immul(immul(s,qpow(n,n-i)),(1ll*i*(i-1)/2)%mod));
        mmul(s,n-i);
    }
    mmul(ans,n);
    printf("%d\n",ans);
}