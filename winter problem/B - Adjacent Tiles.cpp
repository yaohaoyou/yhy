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
ll n;
void matt(int _cases){
    scanf("%lld",&n);
    ll x=sqrt(n);
    ll ans=x*(x-1)*2;n-=x*x;
    // while(n){
    //     ll x=sqrt(n);
    //     ans+=x+x*(x-1)*2;
    //     n-=x*x;
    // }
    // printf("%lld\n",ans);
    if(!n)  return printf("%lld\n",ans),void();
    n--;ans++;
    ll d=min(x-1,n);
    n-=d;ans+=d*2;
    if(!n)  return printf("%lld\n",ans),void();
    n--;ans++;
    d=min(x,n);
    n-=d;ans+=d*2;
    if(!n)  return printf("%lld\n",ans),void();
    n--;ans++;
    d=min(x,n);
    n-=d;ans+=d*2;
    if(!n)  return printf("%lld\n",ans),void();
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}

// x*x : x+x*(x-1)*2