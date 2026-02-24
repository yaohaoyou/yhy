// P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)
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
const int maxn=(1<<17)+5,mod=998244353;
int n,m;
int a[maxn],b[maxn],c[maxn],fwta[maxn],fwtb[maxn],fwtc[maxn];
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
const int inv2=qpow(2,mod-2);
inline void ORFMT(int *mp){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(j&(1<<i-1))  madd(mp[j],mp[j^(1<<i-1)]);
}
inline void RORFMT(int *mp){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(j&(1<<i-1))  mdel(mp[j],mp[j^(1<<i-1)]);
}
inline void ANDFMT(int *mp){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(j&(1<<i-1))  madd(mp[j^(1<<i-1)],mp[j]);
}
inline void RANDFMT(int *mp){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(j&(1<<i-1))  mdel(mp[j^(1<<i-1)],mp[j]);
}
inline void XORFWT(int *mp){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(!(j&(1<<i-1))){
                int x=imadd(mp[j],mp[j^(1<<i-1)]),y=imdel(mp[j],mp[j^(1<<i-1)]);
                mp[j]=x;mp[j^(1<<i-1)]=y;
            }
}
inline void RXORFWT(int *mp){
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(!(j&(1<<i-1))){
                int x=imadd(mp[j],mp[j^(1<<i-1)]),y=imdel(mp[j],mp[j^(1<<i-1)]);
                mp[j]=immul(x,inv2);mp[j^(1<<i-1)]=immul(y,inv2);
            }
}
int main(){
    scanf("%d",&n);m=1<<n;
    for(int i=0;i<m;i++){scanf("%d",&a[i]);fwta[i]=a[i];}
    for(int i=0;i<m;i++){scanf("%d",&b[i]);fwtb[i]=b[i];}
    ORFMT(fwta);ORFMT(fwtb);
    for(int i=0;i<m;i++)    fwtc[i]=immul(fwta[i],fwtb[i]);
    RORFMT(fwtc);
    for(int i=0;i<m;i++)    printf("%d ",fwtc[i]);puts("");

    for(int i=0;i<m;i++)    fwta[i]=a[i],fwtb[i]=b[i];
    ANDFMT(fwta);ANDFMT(fwtb);
    for(int i=0;i<m;i++)    fwtc[i]=immul(fwta[i],fwtb[i]);
    RANDFMT(fwtc);
    for(int i=0;i<m;i++)    printf("%d ",fwtc[i]);puts("");
    
    for(int i=0;i<m;i++)    fwta[i]=a[i],fwtb[i]=b[i];
    XORFWT(fwta);XORFWT(fwtb);
    for(int i=0;i<m;i++)    fwtc[i]=immul(fwta[i],fwtb[i]);
    RXORFWT(fwtc);
    for(int i=0;i<m;i++)    printf("%d ",fwtc[i]);puts("");
}