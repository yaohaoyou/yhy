#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2010,maxk=12,mod=998244353;
int n,k;
int a[maxk];
int dp[maxn][1<<maxk][2];
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
int C[maxn][maxn];
void init(){
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)    C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);
    }
}
int main(){
    scanf("%d%d",&k,&n);int S=1<<k;
    for(int i=1;i<=k;i++){scanf("%d",&a[i]);a[i]++;}
    sort(a+1,a+k+1);
    init();
    dp[0][0][0]=1;
    for(int i=1;i<=n+a[k];i++){
        for(int j=0;j<S;j++){
            for(bool o:{0,1}){
                madd(dp[i][j][o],dp[i-1][j][o]);
                for(int l=1;l<=k;l++){
                    if(i<a[l])continue;if(j&(1<<l-1))continue;
                    madd(dp[i][j^(1<<l-1)][o^(__builtin_popcount((S-(1<<l))&j)&1)],1ll*dp[i-1][j][o]*C[n][i-a[l]]%mod);
                }
            }
        }
    }
    printf("%d\n",immul(imdel(dp[n+a[k]][S-1][0],dp[n+a[k]][S-1][1]),qpow(qpow(2,n*k),mod-2)));
}