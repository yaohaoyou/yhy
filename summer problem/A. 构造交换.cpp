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
const int maxn=2e5+10;
int n,m;
int a[maxn];
pii p[maxn];
namespace Sub2{
    bool check(){for(int i=1;i<=n;i++)if((a[i]^i)||(a[i+n]^i))return false;return true;}
    void solve(){debug("sub 2\n");printf("%lld\n",1ll*n*(n-1)/2);exit(0);}
}
namespace Sub3{
    bool check(){for(int i=1;i<=n;i++)if((a[i]^i)||(a[n+n-i+1]^i))return false;return true;}
    void solve(){debug("sub 3\n");printf("%lld\n",1ll*(n-2)*(n-1));exit(0);}
}
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=m){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
int main(){
    scanf("%d",&n);m=n<<1;
    for(int i=1;i<=m;i++){
        scanf("%d",&a[i]);
        if(!p[a[i]].fi) p[a[i]].fi=i;
        else p[a[i]].se=i;
    }
    if(Sub2::check())   Sub2::solve();
    if(Sub3::check())   Sub3::solve();
    sort(p+1,p+n+1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        int li=p[i].fi,ri=p[i].se;
        int xi=ri-li-1,yi=m+li-ri-1;
        ans+=min(xi,yi);
        ans-=T.query(li,ri);
        T.add(ri,1);
    }
    printf("%lld\n",ans);
}