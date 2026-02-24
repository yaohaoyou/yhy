#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ef emplace_front
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n;
int dp[maxn];
deque<int> q;
int main(){
    scanf("%d",&n);
    mems(dp,0x3f);
    q.eb(1);dp[1]=1;
    while(!q.empty()){
        int u=q.front();q.pop_front();
        int t=(u+1)%n;
        if(dp[t]>dp[u]+1){dp[t]=dp[u]+1;q.eb(t);}
        t=(u*10)%n;
        if(dp[t]>dp[u]){dp[t]=dp[u];q.ef(t);}
    }
    printf("%d\n",dp[0]);
}