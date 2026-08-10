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
const int maxn=3010,maxv=210*5000;
int n,sum;
int a[maxn],ss[maxn];
bitset<maxv> dp;
void dfs(int x,int s1,int s2,int k){
    if(s1==s2&&s1)  exit(printf("%d\n",(sum-s1*2==0)?-1:(sum-s1*2))&0);
    if(x>n) return;
    if(s1+s2+sum-ss[x-1]<k*2) return;
    if(s1+a[x]<=k&&dp[k-s1-a[x]])  dfs(x+1,s1+a[x],s2,k);
    if(s2+a[x]<=k&&dp[k-s2-a[x]]) dfs(x+1,s1,s2+a[x],k);
    dfs(x+1,s1,s2,k);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),sum+=a[i];
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;i++)   ss[i]=ss[i-1]+a[i];
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    for(int i=n;i;i--)if(a[i]==a[i-1])exit(printf("%d\n",sum-a[i]*2)&0);
    int v=sum/2;
    dp[0]=1;
    for(int i=1;i<=n;i++){
        dp=dp|(dp<<a[i]);
        // for(int j=v;j>=a[i];j--)   dp[j]=dp[j]|dp[j-a[i]];
    }
    
    for(int i=dp._Find_next(0);i<=v;i=dp._Find_next(i)){
        // printf("i = %d,sum = %d\n",i,sum);
        if(dp[i<<1])   dfs(1,0,0,i);
    }
    puts("-1");
}