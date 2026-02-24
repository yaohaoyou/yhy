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
const int maxn=2.5e5+10;
int n;
ll a[maxn];
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    ll ans=a[1]+a[2],now=0;
    while(a[1]){
        ll t=(a[2]-a[1])/a[1]+1;
        for(int i=2;i<=n;i++)   a[i]-=t*a[1];
        now+=t*a[1];
        sort(a+1,a+n+1);
        if(now>=ans) break;
    }
    printf("%lld\n",min(ans,now));
}
int main(){int T;scanf("%d",&T);while(T--)matt();}