#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=120+10;
ll dp[maxn][maxn];
ll DP(ll t,int x,int y){
    t-=(x+y);
    if(t<0) return 0;
    dp[0][0]=t+1;
    for(int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            if(i||j)    dp[i][j]=0;
            if(i)   dp[i][j]=dp[i-1][j]/2;
            if(j)   dp[i][j]+=(dp[i][j-1]+1)/2;
        }
    }
    return dp[x][y];
}
void solve(){
    ll t;
    int x,y;
    scanf("%lld%d%d",&t,&x,&y);
    if(!t)  puts(!x&&!y?"YES":"NO");
    else if(t-x-y<0)   puts("NO");
    else puts(DP(t,x,y)==DP(t-1,x,y)?"NO":"YES");
}
int main(){int t;scanf("%d",&t);while(t--)solve();}