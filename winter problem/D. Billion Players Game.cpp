#include<bits/stdc++.h>
#define int long long
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
const ll INF=1e18;
int n,l,r;
int a[maxn];
ll s[maxn];
inline ll sum(int l,int r){return l>r?0:s[r]-s[l-1];}
inline ll calc(ll p,int x,int y){
    if(y<=x)    return -INF;
    int k=upper_bound(a+1,a+n+1,p)-a-1;k=min(k,x);
    // printf("calc %lld %lld\n",p,x);
    ll res=0;
    if(k>0) res+=1ll*k*p-s[k];
    if(k+1<=x)  res-=(sum(k+1,x)-1ll*(x-k)*p);
    k=lower_bound(a+1,a+n+1,p)-a;k=max(k,y);
    if(k<=n)    res+=sum(k,n)-1ll*(n-k+1)*p;
    if(y<=k-1)  res-=1ll*(k-y)*p-sum(y,k-1);
    // printf("res = %lld\n",res);
    return res;
}
inline ll f(int x,int y){
    // ll res=INF;
    // vector<int> tmp;tmp.clear();
    // for(int i=l;i<=r;i++)   res=min(res,calc(i,x,y)),tmp.eb(calc(i,x,y));
    // if(is_sorted(tmp.begin(),tmp.end()))return res;
    // reverse(tmp.begin(),tmp.end());
    // if(is_sorted(tmp.begin(),tmp.end()))return res;
    // assert(0);
    return min(calc(l,x,y),calc(r,x,y));
}
void matt(int _cases){
    scanf("%lld%lld%lld",&n,&l,&r);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    ll ans=0;
    for(int i=0;i<=n;i++){
        // for(int j=i;j<=n+1;j++)   printf("%lld ",f(i,j));puts("");
        int L=i+1,R=n+1;
        while(L<=R){
            int mid=(L+R)>>1;
            ll x=f(i,mid),y=f(i,mid-1);
            ans=max(ans,x);ans=max(ans,y);
            if(x>=y) L=mid+1;
            else R=mid-1;
        }
        // printf("%lld %lld\n",calc(l,i),calc(r,i));
    }
    printf("%lld\n",ans);
}
main(){int T;scanf("%lld",&T);for(int i=1;i<=T;i++)matt(i);}