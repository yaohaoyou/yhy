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
const int maxn=8010;
int n,m,a,b;
char s[maxn],t[maxn];
ll dp[2][maxn],f[maxn][maxn];  // dp[i][j] 表示 t[i] 匹配到 s[j] 的最小答案
inline void getmn(ll &x,ll y){(x>y)&&(x=y);}
inline bool check(int l,int r){return ((r&1)^(l&1))&&(count(t+l,t+r+1,'A')==(r-l+1)/2);}
int main(){
    scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
    scanf("%d%d",&a,&b);
    if(a>=b){for(int i=1;i<=n;i++)s[i]=((s[i]-1)^1)+1;for(int i=1;i<=n;i++)t[i]=((t[i]-1)^1)+1;}
    mems(f,0x3f);mems(dp,0x3f);
    dp[0][0]=0;
    for(int i=1;i<=m+1;i++)   f[i][i-1]=0;
    for(int len=2;len<=m;len+=2){
        for(int i=1;i+len-1<=m;i++){
            int j=i+len-1;
            if(t[j-1]!=t[j]){
                if(t[j-1]=='A') getmn(f[i][j],f[i][j-2]+a);
                else    getmn(f[i][j],f[i][j-2]+b);
            }
            if(t[i]!=t[i+1]){
                if(t[i]=='A')   getmn(f[i][j],f[i+2][j]+a);
                else    getmn(f[i][j],f[i+2][j]+b);
            }
            if(t[i]!=t[j]){
                if(t[i]=='A')   getmn(f[i][j],f[i+1][j-1]+a);
                else    getmn(f[i][j],f[i+1][j-1]+b);
            }
        }
    }
    bool o=1;
    for(int j=1;j<=n;j++,o^=1){
        mems(dp[o],0x3f);
        for(int i=j;i<=m;i++){
            if(t[i]==s[j])  getmn(dp[o][i],dp[!o][i-1]);
            for(int k=i-1;k>0;k-=2)
                getmn(dp[o][i],dp[o][k-1]+f[k][i]);
        }
    }
    printf("%lld\n",dp[!o][m]==0x3f3f3f3f3f3f3f3f?-1:dp[!o][m]);
}