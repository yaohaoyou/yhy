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
const int maxn=45;
int n,k;
ll to[maxn];
unordered_map<ll,int> mp;
ll dfs(ll s){
    if(!s)  return 0;
    if(mp.find(s)!=mp.end())    return mp[s];
    ll lb=s&-s;
    return mp[s]=max(dfs(s^lb),dfs(s&to[__lg(lb)+1])+1);
}
inline double sqr(double x){return x*x;}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){int x;scanf("%d",&x);if(x)to[i]|=1ll<<j-1;}
    }
    int x=dfs((1ll<<n)-1);
    printf("%.10lf\n",sqr(1.0*k/x)*x*(x-1)/2);
}