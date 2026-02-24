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
const int maxn=1e6+10;
int n,q;
int a[maxn],dp[maxn];
deque<int> que;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    scanf("%d",&q);
    while(q--){
        int k;scanf("%d",&k);
        dp[1]=0;que.eb(1);
        for(int i=2;i<=n;i++){
            while(!que.empty()&&que.front()+k<i) que.pop_front();
            dp[i]=que.empty()?dp[i-1]+1:dp[que.front()]+(a[que.front()]<=a[i]);
            while(!que.empty()&&(dp[que.back()]>dp[i]||(dp[que.back()]==dp[i]&&a[que.back()]<=a[i])))    que.pop_back();
            que.eb(i);
        }
        printf("%d\n",dp[n]);
        que.clear();
    }
}