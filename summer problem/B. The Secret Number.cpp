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
vector<ll> ans;
void matt(){
    ans.clear();
    scanf("%lld",&n);
    ll x=10;
    for (int k=1;k<=20;k++) {
        if (1+x>n)  break;
        if (n%(1+x)==0) ans.eb(n/(1 + x));
        x*=10;
    }
    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(ll i:ans)  printf("%lld ",i);
    puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}