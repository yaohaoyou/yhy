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
const int maxn=2010;
int n;
char s[maxn],t[maxn];
int buc[30],pre[2][maxn][30];
int dp[maxn][maxn];  // dp[i][j] 表示 s[1~i] 插入了后面的若干个字符后等于 g[1~j] 的最小答案
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
void matt(int _cases){
    scanf("%d%s%s",&n,s+1,t+1);
    for(int i=1;i<=n;i++)   buc[s[i]-'a']++;
    for(int i=1;i<=n;i++)   buc[t[i]-'a']--;
    for(int i=1;i<=n;i++){
        memc(pre[0][i],pre[0][i-1]);
        pre[0][i][s[i]-'a']++;
        memc(pre[1][i],pre[1][i-1]);
        pre[1][i][t[i]-'a']++;
    }
    if(count_if(buc,buc+26,[&](int x){return bool(x);})){mems(buc,0);return puts("-1"),void();}
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j]=n+1;
    for(int i=0;i<=n;i++)dp[0][i]=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(s[i]==t[j])  gmn(dp[i][j],dp[i-1][j-1]);
            if(pre[1][j][s[i]-'a'])  gmn(dp[i][j],dp[i-1][j]+1);
            if(pre[0][i][t[j]-'a']<pre[1][j][t[j]-'a'])  gmn(dp[i][j],dp[i][j-1]);
        }
    }
    printf("%d\n",dp[n][n]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}