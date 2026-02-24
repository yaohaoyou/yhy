#include<bits/stdc++.h>
using namespace std;
const int maxn=220,maxa=4e4+10;
int n,m,k;
int a[maxn],s[maxn];
int dp[maxn][maxa][2];
inline void getmn(int &x,int y){(x>y)&&(x=y);}
int ans;bool __=true;
inline void getans(int x){if(__)ans=x;else getmn(ans,x);__=false;}
int main(){
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];
    }
    memset(dp,0x3f,sizeof(dp));
    if(a[1]<=m) dp[1][a[1]][0]=0;
    if(a[1]<=k) dp[1][0][1]=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<=m&&j<=s[i];j++){
            if(j+a[i+1]<=m)  getmn(dp[i+1][j+a[i+1]][0],min(dp[i][j][0],dp[i][j][1]+min(a[i],a[i+1])));
            if(s[i+1]-j<=k) getmn(dp[i+1][j][1],min(dp[i][j][1],dp[i][j][0]+min(a[i],a[i+1])));
            // printf("%d %d : %d %d\n",i,j,dp[i][j][0],dp[i][j][1]);
        }
    }
    for(int i=0;i<=m;i++)    getans(min(dp[n][i][0],dp[n][i][1]));
    if(ans!=dp[0][0][0])    printf("%d\n",ans);
    else    puts("-1");
}