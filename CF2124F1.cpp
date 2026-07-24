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
const int maxn=5010,mod=998244353;
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
int n,m;
int f[maxn<<1][maxn],sf[maxn],g[maxn<<1][maxn];  // f[i][j][k] 表示 a[i]=j，以 k 开头的方案数
bool ban[maxn][maxn];vector<int> v[maxn];
void matt(int _cases){
    for(int i=1;i<=n;i++)   v[i].clear();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ban[i][j]=0;
    for(int i=0;i<=n+n;i++)for(int j=0;j<=n;j++)f[i][j]=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int x,y;scanf("%d%d",&x,&y);ban[x][y]=true;v[x].eb(y);}
    int del=-n;
    for(int i=1;i<=n;i++)   f[i-del][i]=!ban[1][i];
    mems(sf,0);
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)madd(sf[i],f[j-del][i]);
    for(int i=2;i<=n;i++){
        del++;
        auto cpy=[&](int x,int y){g[x][y]=f[x][y];};
        for(int l=1;l<=n;l++)   cpy(l-del,l),cpy(l-del+1,1),cpy(l-del+1,l+1),cpy(l-del,1);
        // f[i][j][k]=f[i-1][j-1][k],f[j-del][k]=f[i][j][k]
        // f[i-1][j][k]=f[j-del+1][k]
        if(!ban[i][1]){
            f[1-del][1]=0;
            for(int l=2;l<=n;l++)   madd(f[1-del][1],g[l-del][l]);
            for(int l=1;l<=n;l++)   madd(f[1-del][1],g[l-del+1][1]);
            
            for(int k=2;k<=n;k++){
                f[1-del][k]=sf[k];
                // for(int l=k;l<=n;l++)   madd(f[1-del][k],g[l-del+1][k]);
            }
        }
        {
            int res=0;
            for(int l=1;l<n;l++)    madd(res,g[l-del+1][l+1]);
            for(int l=1;l<=n;l++)   madd(res,g[l-del+1][1]);
            for(int j=2;j<=n;j++)if(!ban[i][j])f[j-del][j]=imdel(res,g[j-del][1]);
        }
        for(int j:v[i])for(int k=1;k<=n;k++){
            if(j>k)    mdel(sf[k],f[j-del][k]);
            f[j-del][k]=0;
        }
        for(int j=1;j<=n;j++)   madd(sf[j],f[j-del][j]);
        // for(int k=1;k<=n;k++){sf[k]=0;for(int j=k;j<=n;j++)madd(sf[k],f[j-del][k]);}
    }
    int ans=0;
    for(int i=1;i<=n;i++)madd(ans,f[i-1-del][i]),madd(ans,f[i-del][1]);
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}