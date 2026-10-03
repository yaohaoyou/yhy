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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=410,B=220,mod=1e9+7;
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
int n,m;
int a[maxn];
int L[maxn],R[maxn],fac[maxn],inv[maxn];
int f[maxn][2][2][2];  // f[i][0/1][0/1][0/1] 表示第 i 个数是否 >=x，上一个数是否 >=x，是否能达到答案 x 的方案数
int g[maxn],pr[maxn],sf[maxn];
int solve(int k){
    f[0][0][0][0]=1;
    for(int i=1;i<=n;i++){
        mems(f[i],0);
        for(int x:{0,1})for(int y:{0,1})for(int o:{0,1})if(f[i-1][x][y][o]){
            if(L[i]<k)  madd(f[i][y][0][o],immul(f[i-1][x][y][o],min(R[i]+1,k)-L[i]));
            if(R[i]>=k) madd(f[i][y][1][o||x||y],immul(f[i-1][x][y][o],R[i]-max(L[i],k)+1));
        }
    }
    int res=0;
    for(int i:{0,1})for(int j:{0,1})madd(res,f[n][i][j][1]);
    return res;
}
void init(){
    fac[0]=1;for(int i=1;i<=B;i++)fac[i]=immul(fac[i-1],i);
    inv[B]=qpow(fac[B],mod-2);for(int i=B-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);m=0;
    for(int i=1;i<=n;i++)   scanf("%d",&L[i]),a[++m]=max(1,L[i]-1);
    for(int i=1;i<=n;i++)   scanf("%d",&R[i]),a[++m]=R[i];
    a[++m]=1;
    sort(a+1,a+m+1);m=unique(a+1,a+m+1)-a-1;
    a[m+1]=a[m]+1;
    int ans=0;
    // for(int i=1;i<=a[m];i++)   madd(ans,solve(i));
    for(int i=1;i<=m;i++){
        if(a[i+1]-a[i]<=B){
            for(int j=a[i];j<a[i+1];j++)    madd(ans,solve(j));
        }
        else{
            int k=a[i],x=a[i+1]-a[i];
            for(int j=k;j<=k+B-1;j++)   g[j-k+1]=imadd(g[j-k],solve(j));
            pr[0]=1;for(int j=1;j<=B;j++)pr[j]=immul(pr[j-1],imdel(x,j));
            sf[B+1]=1;for(int j=B;j;j--)sf[j]=immul(sf[j+1],imdel(x,j));
            for(int j=1;j<=B;j++){
                int res=1ull*pr[j-1]*sf[j+1]%mod*inv[j-1]%mod*inv[B-j]%mod;
                if((B-j)&1) res=mod-res;
                // for(int k=1;k<=B;k++)if(j^k)mmul(res,immul(imdel(x,k),qpow(imdel(j,k),mod-2)));
                madd(ans,immul(res,g[j]));
            }
        }
    }
    printf("%d\n",ans);
}
int main(){freopen("game.in","r",stdin);freopen("game.out","w",stdout);init();debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}