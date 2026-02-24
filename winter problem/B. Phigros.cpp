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
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
char s[maxn];
int a[maxn],b[maxn],c[maxn],d[maxn];
int f[2][maxn],g[2][maxn],pq[maxn],fac[maxn],inv[maxn];
void init(){
    const int N=2e5;
    pq[0]=1;for(int i=1;i<=N;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++){
            if(s[j]=='1')    a[i]++;
            else if(s[j]=='0')   b[j]++;
            else c[i]++,d[j]++;
        }
    }
    if(m>n){
        f[0][0]=1;
        for(int i=1;i<=m;i++){
            bool o=i&1;
            int x=pq[d[i]];
            for(int j=0;j<=i&&j<=n+1;j++){
                if(j==n+1)  madd(f[!o][n],f[!o][n+1]),madd(g[!o][n],g[!o][n+1]);
                if(b[i]){
                    f[o][j]=j?immul(f[!o][j-1],x):0;
                    g[o][j]=j?immul(imadd(g[!o][j-1],f[!o][j-1]),x):0;
                }
                else{
                    f[o][j]=imadd(f[!o][j],j?immul(f[!o][j-1],imdel(x,1)):0);
                    g[o][j]=imadd(g[!o][j],j?immul(imadd(g[!o][j-1],f[!o][j-1]),x-1):0);
                }
            }
        }
        int ans=g[m&1][n+1];
        for(int i=0;i<=n;i++)   madd(ans,immul(max(i,n),f[m&1][i]));
        printf("%d\n",ans);
    }
    else{
        f[0][0]=1;
        for(int i=1;i<=n;i++){
            bool o=i&1;
            int x=pq[c[i]];
            for(int j=0;j<=i&&j<=m+1;j++){
                if(j==m+1)  madd(f[!o][m],f[!o][m+1]),madd(g[!o][m],g[!o][m+1]);
                if(a[i]){
                    f[o][j]=j?immul(f[!o][j-1],x):0;
                    g[o][j]=j?immul(imadd(g[!o][j-1],f[!o][j-1]),x):0;
                }
                else{
                    f[o][j]=imadd(f[!o][j],j?immul(f[!o][j-1],imdel(x,1)):0);
                    g[o][j]=imadd(g[!o][j],j?immul(imadd(g[!o][j-1],f[!o][j-1]),x-1):0);
                }
            }
        }
        int ans=g[n&1][m+1];
        for(int i=0;i<=m;i++)   madd(ans,immul(max(i,m),f[n&1][i]));
        printf("%d\n",ans);
    }
}