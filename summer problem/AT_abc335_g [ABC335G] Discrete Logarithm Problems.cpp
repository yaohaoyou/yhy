#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,maxd=1.2e5+10;
int n;
ll p;
ll a[maxn];
inline ll qpow(ll x,ll y){ll res=1;while(y){if(y&1)res=__int128(res)*x%p;x=__int128(x)*x%p;y>>=1;}return res;}
vector<ll> pri,fac;
vector<ll> v2;
unordered_map<ll,int> mp;
void makefactors(ll x){
    for(int i=1;1ll*i*i<=x;i++){
        if(x%i==0){
            fac.eb(i);
            if(1ll*i*i!=x)  v2.eb(x/i);
        }
    }
    reverse(v2.begin(),v2.end());for(ll i:v2)   fac.eb(i);
    for(int i=2;1ll*i*i<=x;i++){
        if(x%i==0){
            while(x%i==0)   x/=i;
            pri.eb(i);
        }
    }
    if(x^1) pri.eb(x);
}
inline ll ord(ll x){
    ll ret=p-1;
    for(ll i:pri)
        while(ret%i==0&&qpow(x,ret/i)==1)       ret/=i;
    return ret;
}
int main(){
    scanf("%d%lld",&n,&p);
    makefactors(p-1);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        mp[ord(a[i])]++;
    }
    ll ans=0;
    for(int i=0;i<fac.size();i++){
        ans+=1ll*mp[fac[i]]*mp[fac[i]];
        for(int j=0;j<i;j++)if(fac[i]%fac[j]==0)ans+=1ll*mp[fac[i]]*mp[fac[j]];
    }
    printf("%lld\n",ans);
}