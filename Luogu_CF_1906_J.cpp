#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define pui pair<ull,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5010,mod=998244353;
int n;
int a[maxn],dp[maxn][maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){
        int res=1;
        while(y){
            if(y&1) mmul(res,x);
            mmul(x,x);
            y>>=1;
        }
        return res;
    }
}
using namespace MyMod;
int c[maxn];
int nxt[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int j=i+1;
        while(j<=n&&a[j]>a[j-1])j++;
        j--;
        nxt[i]=j;
    }
    nxt[n+1]=n;
    dp[0][1]=1;dp[0][2]=-1;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<=n;j++)   madd(dp[i][j],dp[i][j-1]);
        mems(c,0);
        for(int j=i+1;j<=n;j++){
            int res=immul(qpow(2,j-i-1),dp[i][j]);
            madd(dp[i+1][j],res);
            mdel(dp[i+1][nxt[j+1]+1],res);
            // for(int k=j;k<=nxt[j+1];k++)    madd(dp[i+1][k],immul(qpow(2,j-i-1),dp[i][j]));
        }
    }
    printf("%d\n",dp[n][n]);
}