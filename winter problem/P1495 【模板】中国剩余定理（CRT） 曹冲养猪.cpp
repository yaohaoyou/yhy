#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=20;
int n;
int a[maxn],b[maxn];
ll lcm;
void exgcd(ll a,ll b,ll &x,ll &y){
    if(!b)  return x=1,y=0,void();
    exgcd(b,a%b,x,y);
    ll t=x;x=y;y=t-a/b*y;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        if(!lcm)    lcm=a[i];
        else lcm=lcm/__gcd(lcm,(ll)a[i])*a[i];
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll m=lcm/a[i],x,y;
        exgcd(m,a[i],x,y);
        (ans+=LL(m)*(x+lcm)%lcm*b[i]%lcm)%=lcm;
    }
    printf("%lld\n",ans);
}