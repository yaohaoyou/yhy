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
const int maxn=110,mod=998244353;
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
int n,m,k,ans,fac=1;
vector<pii> v;
void makefactors(int x){
    for(int i=2;1ll*i*i<=x;i++){
        if(x%i==0){
            int c=0;
            while(x%i==0)   x/=i,c++;
            v.eb(i,c);
            mmul(fac,c+1);
        }
    }
    if(x^1) v.eb(x,1),mmul(fac,2);
}
int dp[210][4000],sum[210][4000];
int main(){
    scanf("%d%d",&n,&m);
    makefactors(n);
    ans=1;
    for(auto [i,j]:v){
        int res=0;
        mems(dp,0);mems(sum,0);
        dp[0][0]=sum[0][0]=1;
        for(int k=1;k<=m+m;k++){
            for(int l=0;l<=j*k&&l<=m*j;l++){
                dp[k][l]=imdel(sum[k-1][l],l-j-1>=0?sum[k-1][l-j-1]:0);
                sum[k][l]=imadd(sum[k][l-1],dp[k][l]);
            }
        }
        mmul(ans,sum[m+m][m*j]);
    }
    ans=imadd(qpow(fac,2*m),ans);
    mmul(ans,qpow(2,mod-2));
    printf("%d\n",ans);
}