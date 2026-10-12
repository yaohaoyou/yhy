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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,m,q;
pii a[maxn];
ll s[maxn],ans[maxn];
int b[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   b[i]=a[i].se;
    sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].se=lower_bound(b+1,b+m+1,a[i].se)-b;
}
struct BIT{
    ll tr[maxn];int cnt[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s,int y){while(x<=m){tr[x]+=s;cnt[x]+=y;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
    inline ll bry(int k){
        int x=0,nw=0;ll res=0;
        for(int i=19;~i;i--)if((x|(1<<i))<=m&&nw+cnt[x|(1<<i)]<=k)
            x|=(1<<i),nw+=cnt[x],res+=tr[x];
        res+=1ll*(k-nw)*b[x+1];
        return res;
    }
}T;
void divide(int l,int r,int pl,int pr){
    int mid=(l+r)>>1;
    // assert(ans[mid]==ans[n+1]);
    ans[mid]=ans[n+1];
    int x;
    // for(int i=pl;i<=mid;i++)if(i)T.add(a[i].se,b[a[i].se],1);
    for(int i=pl;i<=pr;i++){
        if(i)   T.add(a[i].se,b[a[i].se],1);
        if(i>=mid){
            ll w=-T.bry(mid)+s[i+1];
            if(ans[mid]<w)  ans[mid]=w,x=i;
        }
    }
    for(int i=pl;i<=pr;i++)if(i)T.add(a[i].se,-b[a[i].se],-1);
    if(l^r){
        divide(l,mid,pl,x);
        for(int i=pl;i<x;i++)if(i)T.add(a[i].se,b[a[i].se],1);
        divide(mid+1,r,x,pr);
        for(int i=pl;i<x;i++)if(i)T.add(a[i].se,-b[a[i].se],-1);
    }
}
bool mem2;
int main(){
    mems(ans,-0x3f);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),a[i].fi+=a[i].se;
    sort(a+1,a+n+1,greater<pii>());
    for(int i=n;i;i--)  s[i]=s[i+1]+a[i].fi-a[i].se;
    discrete();
    divide(0,n,0,n);
    while(q--){int x;scanf("%d",&x);printf("%lld\n",ans[x]);}
}