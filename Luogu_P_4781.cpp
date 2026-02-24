#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e3+10,mod=998244353;
int n,k;
int x[maxn],y[maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace MyMod;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d%d",&x[i],&y[i]);
    int ans=0;
    for(int i=1;i<=n;i++){
        int res=y[i];
        for(int j=1;j<=n;j++)
            if(i^j) mmul(res,immul(imdel(k,x[j]),qpow(imdel(x[i],x[j]),mod-2)));
        madd(ans,res);
    }
    printf("%d\n",ans);
}