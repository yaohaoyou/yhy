#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int p1=350000381,p2=350000383;
void exgcd(int a, int b, ll &x, ll &y) {
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, x, y);
  ll t = x;
  x = y;
  y = t - 1ll*(a/b)*y;
  return;
}
void solve(){
    int r1,r2;
    cout<<"? "<<p1<<endl;
    cin>>r1;
    cout<<"? "<<p2<<endl;
    cin>>r2;
    ll x,y;
    exgcd(p1,p2,x,y);
    ll y1=1ll*x*(r2-r1);
    // printf("%lld %lld\n",x,y);
    __int128 ans=__int128(y1)*p1+r1;ll mod=1ll*p1*p2;
    ans%=mod;ans=(ans+mod)%mod;
    
    ll out=ans;
    cout<<"! "<<out<<endl;
}
int main(){int T;cin>>T;while(T--)solve();}