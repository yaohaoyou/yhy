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
int a[maxn],c[maxn];
int dp[maxn];
int calc(int l,int r){
    for(int i=l;i<=r;i++){
        dp[i]=1e9;
        if(i-c[i]<l)    dp[i]=1;
        else{
            for(int j=i-c[i];j<i;j++)   dp[i]=min(dp[i],dp[j]+1);
        }
    }
    return dp[r];
}
int main(){
    scanf("%d",&n);n--;
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    a[0]=1;
    int ans=0;
    for(int i=n;i;i--){
        if(!a[i])   continue;
        if(i<=c[i]){ans++;continue;}
        bool flag=0;
        for(int j=i-c[i];j<i;j++)   flag|=a[j];
        if(!flag){
            int lst=i-c[i];
            while(!a[lst])   lst--;
            // printf("lst = %d\n",lst);
            ans+=calc(lst+1,i);
        }
        else    ans++;
    }
    printf("%d\n",ans);
}