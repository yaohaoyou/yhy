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
const int maxn=(1<<16)+10,m=16,M=(1<<16)-1,mod=998244353,inv2=(mod+1)>>1;
int n,k;
int f[maxn];
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
void FWT(){
    for(int i=0;i<m;i++)
        for(int j=0;j<=M;j++)
            if(!(j&(1<<i))){
                int x=f[j],y=f[j^(1<<i)];
                f[j]=imadd(x,y);f[j^(1<<i)]=imdel(x,y);
            }
}
void IFWT(){
    for(int i=0;i<m;i++)
        for(int j=0;j<=M;j++)
            if(!(j&(1<<i))){
                int x=f[j],y=f[j^(1<<i)];
                f[j]=immul(imadd(x,y),inv2),f[j^(1<<i)]=immul(imdel(x,y),inv2);
            }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++){int x;scanf("%d",&x);f[x]=1;}
    FWT();
    for(int i=0;i<=M;i++)
        if(f[i]==1) f[i]=n;
        else f[i]=1ll*imdel(qpow(f[i],n+1),f[i])*qpow(imdel(f[i],1),mod-2)%mod;
    IFWT();
    int ans=0;
    for(int i=1;i<=M;i++)   madd(ans,f[i]);
    printf("%d\n",ans);
}