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
const int maxn=1e6+10,mod=1000003;
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
int n;
int cnt[30];
int fac[maxn],inv[maxn];
int dp[30][110];
char s[maxn];
void init(){
    const int N=1e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void matt(int _cases){
    mems(cnt,0);mems(dp,0);dp[0][0]=1;
    scanf("%s",s+1);n=strlen(s+1);
    int m=0;
    for(int i=1;i<=n;i++)   cnt[s[i]-'a'+1]++,m+=(s[i]!=s[i-1]);
    int now=0;
    for(int i=1;i<=26;i++){
        if(!cnt[i]){memc(dp[i],dp[i-1]);continue;}
        for(int j=1;j<=m;j++){
            for(int k=0;k<j;k++){
                for(int p=0;p+p<=j-k;p++){
                    int q=j-k-p-p;
                    if(q>k+1||cnt[i]<p+q)   continue;
                    madd(dp[i][j],immul(dp[i-1][k],1ull*C(now-k,p)*C(k+1,q)%mod*C(cnt[i]-1,p+q-1)%mod));
                }
            }
        }
        now+=cnt[i];
    }
    printf("Case #%d: %d\n",_cases,dp[26][m]);
}
int main(){init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}