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
int n,m;
ll a[maxn];
vector<ll> v;
int main(){
    scanf("%d%d",&n,&m);m--;
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++)   v.eb(a[i]-a[i-1]);
    sort(v.begin(),v.end(),greater<ll>());
    ll ans=a[n]-a[1];
    for(int i=0;i<m;i++)    ans-=v[i];
    printf("%lld\n",ans);
}