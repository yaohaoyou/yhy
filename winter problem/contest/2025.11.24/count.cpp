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
const int maxn=510,mod=998244353;
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
int b[maxn],c[maxn];
int a[maxn][maxn],f[maxn][maxn],g[maxn][maxn],h[2][maxn];
char d[maxn][maxn];
int ans;
bool mem2;
void DP(){
    for(int i=0;i<=m;i++)   f[m][i]=1;
    for(int i=m-1;~i;i--){
        for(int j=0;j<=i;j++)f[i][j]=0;
        if(!b[i+1]){
            for(int j=0;j<=i;j++)   madd(f[i][j],f[i+1][j+1]);
        }
        else{
            for(int j=0;j<=i;j++){
                madd(f[i][j],f[i+1][j]);
                if(j)   madd(f[i][j],immul(f[i+1][j-1],j));
            }
        }
    }
    g[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<=i;j++)g[i][j]=0;
        if(!b[i]){
            for(int j=1;j<=i;j++)   madd(g[i][j],g[i-1][j-1]);
        }
        else{
            for(int j=0;j<=i;j++){
                madd(g[i][j],g[i-1][j]);
                madd(g[i][j],immul(g[i-1][j+1],j+1));
            }
        }
    }
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    freopen("count.in","r",stdin);freopen("count.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",d[i]+1);
        for(int j=1;j<=n;j++){
            if(d[i][j]=='L')    d[i][j]='R';
            else if(d[i][j]=='R')   d[i][j]='L';
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    int pq=qpow(2,n*n-2);
    int ans=0,sum=1;
    for(int i=1;i<=n;i++){
        m=0;for(int j=1;j<=n;j++)if(d[i][j]=='L')b[++m]=0;else if(d[i][j]=='R')b[++m]=1;
        DP();
        for(int j=0;j<=m;j++)madd(h[0][i],g[m][j]);
        mmul(sum,h[0][i]);
        m=0;for(int j=1;j<=n;j++)if(d[j][i]=='D')b[++m]=0;else if(d[j][i]=='U')b[++m]=1;
        DP();
        for(int j=0;j<=m;j++)madd(h[1][i],g[m][j]);
        mmul(sum,h[1][i]);
    }
    // printf("%d\n",sum);
    for(int i=1;i<=n;i++){
        {
            m=0;for(int j=1;j<=n;j++)if(d[i][j]=='L')b[++m]=0,c[m]=j;else if(d[i][j]=='R')b[++m]=1,c[m]=j;
            DP();
            for(int j=1;j<=m;j++){
                if(!b[j]) continue;
                int w=h[0][i];
                for(int k=0;k<=j-1;k++)mdel(w,immul(g[j-1][k],f[j][k]));
                w=1ull*sum*qpow(h[0][i],mod-2)%mod*w%mod;
                madd(ans,immul(a[i][c[j]],w));
            }
        }
        {
            m=0;for(int j=n;j;j--)if(d[i][j]=='R')b[++m]=0,c[m]=j;else if(d[i][j]=='L')b[++m]=1,c[m]=j;
            DP();
            for(int j=1;j<=m;j++){
                if(!b[j]) continue;
                int w=h[0][i];
                for(int k=0;k<=j-1;k++)mdel(w,immul(g[j-1][k],f[j][k]));
                w=1ull*sum*qpow(h[0][i],mod-2)%mod*w%mod;
                madd(ans,immul(a[i][c[j]],w));
            }
        }
        {
            m=0;for(int j=1;j<=n;j++)if(d[j][i]=='D')b[++m]=0,c[m]=j;else if(d[j][i]=='U')b[++m]=1,c[m]=j;
            DP();
            for(int j=1;j<=m;j++){
                if(!b[j]) continue;
                int w=h[1][i];
                for(int k=0;k<=j-1;k++)mdel(w,immul(g[j-1][k],f[j][k]));
                w=1ull*sum*qpow(h[1][i],mod-2)%mod*w%mod;
                madd(ans,immul(a[c[j]][i],w));
            }
        }
        {
            m=0;for(int j=n;j;j--)if(d[j][i]=='U')b[++m]=0,c[m]=j;else if(d[j][i]=='D')b[++m]=1,c[m]=j;
            DP();
            for(int j=1;j<=m;j++){
                if(!b[j]) continue;
                int w=h[1][i];
                for(int k=0;k<=j-1;k++)mdel(w,immul(g[j-1][k],f[j][k]));
                w=1ull*sum*qpow(h[1][i],mod-2)%mod*w%mod;
                madd(ans,immul(a[c[j]][i],w));
            }
        }
    }
    printf("%d\n",ans);
}