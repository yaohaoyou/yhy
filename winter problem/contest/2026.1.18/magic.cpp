#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
int n,c;
int a[maxn];
ll b[maxn];
int main(){
    freopen("magic.in","r",stdin);freopen("magic.out","w",stdout);
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[i]=a[i]-1ll*i*c;
    sort(b+1,b+n+1,greater<ll>());
    ll sum=0;
    for(int i=1;i<=n;i++)   sum+=b[i],printf("%lld ",sum+1ll*i*(i+1)/2*c);
    puts("");
}