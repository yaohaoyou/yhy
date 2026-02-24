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
const int maxn=5e5+10;
int n,k,d;
int a[maxn];
bool dp[maxn];
int main(){
    scanf("%d%d%d",&n,&k,&d);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    dp[0]=true;
    for(int i=0,j=1;i<=n-k;i++){
        j=max(j,i+k);
        // printf("dp[%d] = %d\n",i,dp[i]);
        if(!dp[i])   continue;
        while(a[j]-a[i+1]<=d) dp[j++]=true;
    }
    puts(dp[n]?"YES":"NO");
}