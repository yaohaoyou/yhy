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
bool mem1;
const int maxn=2e5+10;
int n;
ll a[maxn],pre[maxn],suf[maxn];
bool check(ll x){
    vector<ll> fac;
    for(ll i=2;i*i<=x;i++){
        if(x%i==0){
            fac.eb(i);
            while(x%i==0)x/=i;
        }
    }
    if(x^1) fac.eb(x);
    for(ll d:fac){
        vector<ll> v;
        for(int i=1;i<=n;i++)if(a[i]%d)v.eb(a[i]);
        assert(!v.empty());
        if(v.size()<=2) return true;
        pre[0]=v[0];suf[v.size()-1]=v.back();
        for(int i=1;i<v.size();i++)pre[i]=__gcd(pre[i-1],v[i]);
        for(int i=v.size()-2;~i;i--)suf[i]=__gcd(suf[i+1],v[i]);
        for(int i=0;i<v.size();i++){
            if(!i&&suf[i+1]>1)  return true;
            else if(i==v.size()-1&&pre[i-1]>1)  return true;
            else if(i&&i+1<v.size()&&__gcd(pre[i-1],suf[i+1])>1)    return true;
        }
    }
    return false;
}
void matt(int _cases){
    scanf("%d",&n);
    ll g=0;
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]),g=__gcd(g,a[i]);
    for(int i=1;i<=n;i++)   a[i]/=g;
    if(count(a+1,a+n+1,1)>1)    return puts("NO"),void();
    if(check(a[1])) puts("YES");
    else if(check(a[2]))    puts("YES");
    else    puts("NO");
}
bool mem2;
int main(){debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}