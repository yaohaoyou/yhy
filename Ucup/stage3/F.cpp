#include<bits/stdc++.h>
#define db double
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
const int maxn=1e3+10;
int n,m;
db dp[maxn][maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=n;~i;i--){
        for(int j=m;~j;j--){
            // dp[i][j]=max(dp[i][j],1.0*i/(i+j)+dp[i+1][j]);
            dp[i-1][j]
        }
    }
}