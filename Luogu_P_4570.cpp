#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int maxn=1010,logV=61;
int n;
pii a[maxn];
int p[logV];
inline bool insert(int x){
    for(int i=logV-1;~i;i--){
        if(!(x&(1ll<<i)))    continue;
        if(!p[i]){p[i]=x;return true;}
        x^=p[i];
        if(!x)   return false;
    }
    return false;
}
int ans;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)   scanf("%lld%lld",&a[i].first,&a[i].second);
    sort(a+1,a+n+1,[&](pii x,pii y){return x.second>y.second;});
    for(int i=1;i<=n;i++)   ans+=insert(a[i].first)*a[i].second;
    printf("%lld\n",ans);
}