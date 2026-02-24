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
const int maxn=5e5+10;
int n,m;
int a[maxn];ll s[maxn];
ll dp[maxn];int p[maxn];
inline ll w(int l,int r){
    ll mid=(l+r)>>1;
    return (mid-l)*a[mid]-(s[mid-1]-s[l-1])+(s[r]-s[mid])-(r-mid)*a[mid];
}
deque<pii> dq;
int DP(ll x){
    dq.clear();
    dq.eb(0,1);
    for(int i=1;i<=n;i++){
        while(dq.size()>1&&dq[1].se<=i) dq.pop_front();
        dp[i]=dp[dq[0].fi]+w(dq[0].fi+1,i)-x;p[i]=p[dq[0].fi]+1;
        while(!dq.empty()&&dp[i]+w(i+1,max(i+1,dq.back().se))<dp[dq.back().fi]+w(dq.back().fi+1,max(i+1,dq.back().se)))dq.pop_back();
        if(dq.empty()){dq.eb(i,1);continue;}
        int l=max(i+1,dq.back().se),r=n,j=dq.back().fi,k=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(dp[i]+w(i+1,mid)<dp[j]+w(j+1,mid))  k=mid,r=mid-1;
            else l=mid+1;
        }
        if(k)   dq.eb(i,k);
        // dp[i]=1e18;
        // for(int j=0;j<i;j++)if(dp[j]+w(j+1,i)-x<dp[i])dp[i]=dp[j]+w(j+1,i)-x,p[i]=p[j]+1;
    }
    return p[n];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    ll l=-n*2e6,r=n*2e6,k;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(DP(mid)<=m)  k=mid,l=mid+1;
        else    r=mid-1;
    }
    DP(k);
    printf("%lld\n",dp[n]+k*m);
}