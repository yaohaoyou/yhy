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
const int maxn=12;
int n;
void exgcd(ll a,ll b,ll &x,ll &y){
    if(!b)  return x=1,y=0,void();
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}
int a[maxn],b[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    ll ans=0,LCM=1;
    for(int i=1;i<=n;i++)   LCM=LCM/__gcd(LCM,(ll)b[i])*b[i];
    for(int i=1;i<=n;i++){
        ll lcm=1;
        for(int j=1;j<=n;j++)
            if(i^j) lcm=lcm/__gcd(lcm,(ll)b[j])*b[j];

        //! x*lcm=1 (mod b[i])
        //! x*lcm+y*b[i]=1
        ll x,y;exgcd(lcm,b[i],x,y);
        ll c=__int128(x)*lcm%LCM;
        (ans+=(__int128(c)*a[i]%LCM)+LCM)%=LCM;
    }
    printf("%lld\n",ans);
}