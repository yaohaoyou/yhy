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
const int maxn=4e5+10;
int n;
int a[maxn],nx[maxn],dp[maxn];
stack<int> stk;
void matt(){
    while(!stk.empty())stk.pop();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    ll ans=1ll*n*(n+1)/2;
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]<=a[i]) stk.pop();
        nx[i]=stk.empty()?-1:stk.top();
        stk.ep(i);
    }
    for(int i=1;i<=n+1;i++)   dp[i]=0;
    for(int i=1;i<=n;i++){
        dp[i]++;
        if(~nx[i]){
            dp[nx[i]]+=dp[i];
            ans+=1ll*dp[i]*(n-nx[i]+1);
        }
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}