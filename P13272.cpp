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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=5010,inf=1e9,mod=1e9+7;
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
bool mem1;
int n;
int a[maxn],b[maxn],c[maxn],pl[maxn],pr[maxn];
int mn[maxn][maxn][2];
ll s[maxn][2],sb[maxn],f[maxn];
int sc[maxn][2],mc[maxn],imc[maxn],g[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),sb[i]=sb[i-1]+b[i];
    mc[0]=imc[0]=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&c[i]);
        memc(sc[i],sc[i-1]);
        madd(sc[i][i&1],qpow(c[i],mod-2));
        mc[i]=immul(mc[i-1],c[i]);
        imc[i]=qpow(mc[i],mod-2);
    }
    for(int i=1;i<=n;i++){
        mn[i][i][i&1]=b[i];mn[i][i][!(i&1)]=inf;
        for(int j=i+1;j<=n;j++){
            memc(mn[i][j],mn[i][j-1]);
            gmn(mn[i][j][j&1],b[j]);
        }
    }
    for(int i=1;i<=n;i++){
        memc(s[i],s[i-1]);
        s[i][i&1]+=a[i];
    }
    for(int i=1;i<=n;i++){
        int x=a[i];pl[i]=i;
        for(int j=i+1;j<=n;j++){
            if(x<=a[j]){
                x=a[j]-x;pl[i]=j;
                if(!x)  break;

            }
            else    break;
        }
    }
    for(int i=n;i;i--){
        int x=a[i];pr[i]=i;
        for(int j=i-1;j;j--){
            if(x<=a[j]){
                x=a[j]-x;pr[i]=j;
                if(!x)  break;
            }
            else break;
        }
    }
    mems(f,0);mems(g,0);g[0]=1;
    for(int i=1;i<=n;i++){
        gmx(f[i],f[i-1]);madd(g[i],g[i-1]);
        for(int j=i+1;j<=n;j++){
            int l=max(i,pr[j]),r=min(j,pl[i]);
            if(l>r) continue;
            ll s0=s[j][0]-s[i-1][0],s1=s[j][1]-s[i-1][1];
            int smc=immul(mc[j],imc[i-1]);
            if(s0==s1)  gmx(f[j],f[i-1]+sb[j]-sb[i-1]),madd(g[j],immul(g[i-1],smc));
            else if(s0>s1&&(l!=r||l%2==0))  gmx(f[j],f[i-1]+sb[j]-sb[i-1]-mn[l][r][0]),madd(g[j],immul(g[i-1],immul(smc,imdel(sc[r][0],sc[l-1][0]))));
            else if(s0<s1&&(l!=r||l%2==1))  gmx(f[j],f[i-1]+sb[j]-sb[i-1]-mn[l][r][1]),madd(g[j],immul(g[i-1],immul(smc,imdel(sc[r][1],sc[l-1][1]))));
        }
        // printf("g[%d] = %d\n",i,g[i]);
    }
    printf("%lld %d\n",f[n],g[n]);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}