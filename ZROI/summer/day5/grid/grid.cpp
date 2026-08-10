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
int f[2][maxn];
int nx[2][maxn],pr[2][maxn],dp[maxn][maxn];  // dp[i][j] 表示第一行取到 i，第二行取到 j 的方案数
vector<int> v[2];
int main(){
    // freopen("grid.in","r",stdin);freopen("grid.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);x--;
        v[x].eb(y);
    }
    v[0].eb(0);v[0].eb(n+1);v[1].eb(0);
    sort(v[0].begin(),v[0].end());sort(v[1].begin(),v[1].end());
    for(int i=0;i<v[0].size();i++)  f[0][v[0][i]]=i;
    for(int i=0;i<v[1].size();i++)  f[1][v[1][i]]=i;
    int res=1;
    for(int o:{0,1}){
        nx[o][n+1]=n+1;
        for(int i=n;i;i--)  nx[o][i]=f[o][i]?i:nx[o][i+1];
        for(int i=1;i<=n;i++)   pr[o][i]=f[o][i]?i:pr[o][i-1];
    }
    for(int i=1;i<=n;i++)if(!f[0][i]){
        if(nx[1][i]==n+1)mmul(res,nx[0][i]-i);
    }
    for(int i=1;i<=n;i++)if(!f[1][i]){
        if(!pr[0][i])   mmul(res,i-pr[1][i]);
    }
    dp[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(!dp[i][j])   continue;
            // printf("%d %d : %d\n",i,j,dp[i][j]);
            if(i^n){
                if(!f[0][i+1])  madd(dp[i+1][j],dp[i][j]);
                else if(j<=i+1){
                    int o=f[0][i+1],res=1;
                    for(int k=v[0][o];k<v[0][o+1];k++){
                        if(f[1][k])continue;
                        int w=k-max(pr[1][k],j);
                        if(w<=0){res=0;break;}
                        mmul(res,w);
                    }
                    if(res) madd(dp[i+1][j],immul(dp[i][j],res));
                }
            }
            if(j^n){
                if(!f[1][j+1])  madd(dp[i][j+1],dp[i][j]);
                else if(j+1<=i){
                    int o=f[1][j+1],res=1;
                    for(int k=v[1][o-1]+1;k<=j+1;k++){
                        if(f[0][k])continue;
                        int w=min(nx[0][k]-1,i)-k+1;
                        if(w<=0){res=0;break;}
                        mmul(res,w);
                    }
                    if(res) madd(dp[i][j+1],immul(dp[i][j],res));
                }
            }
        }
    }
    printf("%d\n",immul(res,dp[n][n]));
}