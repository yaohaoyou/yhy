#include<bits/stdc++.h>
#define db double
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
const int maxn=1e5+10,V=1e4;
const ll INF=4e18;
int n,m;
ll a[maxn];
int b[maxn],c[maxn];
int s[maxn],pre[maxn];
int buc[maxn];
ll dp[maxn];
struct line{int k;ll b;}L[maxn];
inline bool cmp(int u,int v,int x){return 1ll*L[u].k*x+L[u].b<=1ll*L[v].k*x+L[v].b;}
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) root[x],1,m
    #define pos p,l,r
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int tot,root[V+10];
    int tr[maxn*20],lc[maxn*20],rc[maxn*20];
    void upd(setpos,int u){
        if(!p)  p=++tot;
        setmid,&v=tr[p];
        if(!v)  return v=u,void();
        if(!cmp(u,v,b[mid])) swap(u,v);
        if(l==r)return;
        if(!cmp(u,v,b[l]))   upd(lson,u);
        if(!cmp(u,v,b[r]))   upd(rson,u);
    }
    inline ll query(int x,int y,int c){
        int p=root[c],l=1,r=m;ll ret=-INF;
        while(l^r){
            if(!p)  return ret;
            if(tr[p])ret=max(ret,1ll*L[tr[p]].k*y+L[tr[p]].b);
            setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        if(p&&tr[p])ret=max(ret,1ll*L[tr[p]].k*y+L[tr[p]].b);
        return ret;
    }
}
using namespace SegmentTree;
void discrete(){
    for(int i=1;i<=n;i++)   b[i]=a[i]*2*s[i];
    sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   c[i]=lower_bound(b+1,b+m+1,a[i]*2*s[i])-b;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   pre[i]=buc[a[i]],buc[a[i]]=i;
    for(int i=1;i<=n;i++)   s[i]=s[pre[i]]+1;
    discrete();
    ll ans=0;
    for(int i=1;i<=n;i++){
        s[i]++;
        dp[i]=-INF;
        // for(int j=pre[i],c=1;j;j=pre[j],c++){
        //     int x=s[i],y=s[j];
        //     dp[i]=max(dp[i],-y*(a[i]*2*x)+(dp[j-1]+a[i]*y*y));
        // }
        dp[i]=query(c[i],a[i]*2*s[i],a[i]);
        dp[i]+=a[i]*s[i]*s[i];
        dp[i]=max(dp[i],dp[i-1]+a[i]);
        s[i]--;
        L[i]={-s[i],dp[i-1]+a[i]*s[i]*s[i]};upd(all(a[i]),i);
        // printf("dp[%d] = %d\n",i,dp[i]);
        ans=max(ans,dp[i]);
    }
    printf("%lld\n",ans);
}