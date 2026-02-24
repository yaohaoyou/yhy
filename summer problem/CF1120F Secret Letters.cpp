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
const int maxn=1e5+10;
int n,c,d;
int a[maxn];char s[maxn];
int main(){
    scanf("%d%d%d",&n,&c,&d);
    for(int i=1;i<=n;i++)   scanf("%d %c",&a[i],&s[i]);
    scanf("%d",&a[n+1]);
    ll ans=1ll*n*d,sum=0;int lst=a[n+1];
    for(int i=n;i;i--){
        if(s[i]==s[i+1])    sum+=min(1ll*d,1ll*(lst-a[i+1])*c);
        else    lst=a[i+1];
        ans=min(ans,sum+1ll*(a[n+1]-a[i])*c+1ll*(i-1)*d);
    }
    printf("%lld\n",ans);
}