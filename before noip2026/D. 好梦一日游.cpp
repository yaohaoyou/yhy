#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,q;
pii a[maxn];
ll b[maxn],c[maxn];
ll solve(){
    for(int i=1;i<=n;i++)   b[i]=max(100ll,a[i].fi),c[i]=a[i].se;
    sort(b+1,b+n+1);sort(c+1,c+n+1);
    ll ans=0;for(int i=1;i<=n;i++)ans+=max(b[i],c[i]);
    return ans;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].se);
    printf("%lld\n",solve());
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        a[x].fi+=y;
        // printf("%lld\n",solve());
    }
    printf("%lld\n",solve());
}