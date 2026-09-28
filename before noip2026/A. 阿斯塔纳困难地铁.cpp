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
bool mem1;
const int maxn=410,mod=998244353;
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
int p[maxn],son[maxn];
int f[maxn][maxn][maxn];  // f[i][j][k] 表示确定了前 i 个点的父亲，有 j 个点已经选了儿子，有 k 个点钦定是叶子的方案数
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)   scanf("%d",&p[i]),son[p[i]]++;
    f[0][0][0]=1;
    for(int i=1;i<=n+m;i++){
        for(int j=0;j<i;j++){
            for(int k=0;j+k<i;k++)if(f[i-1][j][k]){
                if(i<=n){
                    if(!son[i]) madd(f[i][j][k+1],f[i-1][j][k]);
                    else    madd(f[i][j+1][k],immul(f[i-1][j][k],son[i]));
                    madd(f[i][j][k],f[i-1][j][k]);
                }
                else{
                    madd(f[i][j][k+1],immul(f[i-1][j][k],i-1-k));
                    madd(f[i][j+1][k+1],immul(f[i-1][j][k],i-1-j-k));
                    madd(f[i][j+1][k],immul(f[i-1][j][k],i-1-j-k));
                    madd(f[i][j][k],immul(f[i-1][j][k],i-1-k));
                }
            }
        }
        // for(int j=0;j<=i;j++)for(int k=0;j+k<=i;k++)if(f[i][j][k])printf("%d %d %d : %d\n",i,j,k,f[i][j][k]);
    }
    int ans=0;for(int i=1;i<=n+m;i++)madd(ans,immul(f[n+m][i][n+m-i],qpow(n+m-i,mod-2)));
    for(int i=1;i<=m;i++)   mmul(ans,qpow(n+i-1,mod-2));
    printf("%d\n",ans);
}