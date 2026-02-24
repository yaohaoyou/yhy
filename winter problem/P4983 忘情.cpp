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
const int maxn=1e5+10;
int n,m;
int a[maxn],s[maxn];
ll dp[maxn];int p[maxn];
inline ll sqr(int x){return 1ll*x*x;}
struct line{
    int k;ll b;int id;
    inline ll get(int x){return 1ll*k*x+b;}
};
deque<line> dq;
int DP(ll x){
    dq.clear();
    dq.eb((line){0,1,0});
    for(int i=1;i<=n;i++){
        while(dq.size()>1&&dq[0].get(s[i])>dq[1].get(s[i]))    dq.pop_front();
        dp[i]=dq[0].get(s[i])+sqr(s[i])+2*s[i]-x;p[i]=p[dq[0].id]+1;
        line nw={-2*s[i],dp[i]+sqr(s[i]-1),i};
        while(dq.size()>1&&(dq[dq.size()-2].b-nw.b)*(dq.back().k-nw.k)<(dq.back().b-nw.b)*(dq[dq.size()-2].k-nw.k)) dq.pop_back();
        dq.eb(nw);
        // for(int j=0;j<i;j++)if(dp[j]+sqr(s[i]-s[j]+1)-x<dp[i])dp[i]=dp[j]+sqr(s[i]-s[j]+1)-x,p[i]=p[j]+1;
    }
    return p[n];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    ll l=-sqr(n*1000+1),r=-1,k;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(DP(mid)<=m)  k=mid,l=mid+1;
        else    r=mid-1;
    }
    DP(k);
    printf("%lld\n",dp[n]+k*m);
}