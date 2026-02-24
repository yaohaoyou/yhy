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
const int maxn=110;
int n;
set<ll> a;
vector<ll> ans;
inline ll LCM(ll x,ll y){return x/__gcd(x,y)*y;}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){ll x;scanf("%lld",&x);a.ep(x);}
    while(!a.empty()){
        bool flag=false;
        for(ll i:a){
            ll lcm=1;
            for(ll j:a)if(j^i)lcm=LCM(lcm,__gcd(i,j));
            if(lcm^i){flag=true;a.erase(i);ans.eb(i);break;}
        }
        if(!flag)   return puts("No"),0;
    }
    reverse(ans.begin(),ans.end());
    puts("Yes");
    for(ll i:ans)  printf("%lld ",i);
}