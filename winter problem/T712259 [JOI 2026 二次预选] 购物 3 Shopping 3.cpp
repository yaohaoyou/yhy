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
const int maxn=3e5+10;
int n,q,C,D;
ll ans;
int a[maxn];
ll s[maxn];
inline ll calc(int x){
    int k=lower_bound(a+1,a+n+1,1ll*x*D)-a;
    ll res=k<=n?s[n]-s[k-1]-1ll*(n-k+1)*x*D+1ll*x*C:1ll*x*C;
    // printf("%d %d : %lld\n",x,k,res);
    ans=min(ans,res);
    return res;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    while(q--){
        scanf("%d%d",&C,&D);
        ans=1e18;
        int l=1,r=1e9;
        while(l<=r){
            int mid=(l+r)>>1;
            if(calc(mid)>=calc(mid-1))  r=mid-1;
            else l=mid+1;
        }
        printf("%lld\n",ans);
    }
}