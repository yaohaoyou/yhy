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
const int maxn=2e5+10;
int n;
int a[maxn];
int main(){
    scanf("%d",&n);
    ll ans=0;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        ans+=a[i]/3;a[i]%=3;
        if(a[i]+a[i+1]>=3)  a[i+1]-=3-a[i],ans++;
    }
    printf("%lld\n",ans);
}