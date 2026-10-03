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
const int maxn=1e5+10;
int n,m,q;
ll ans,all;
pii a[maxn],b[maxn],Q[maxn];
int d[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=m){gmx(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=m;i++)tr[i]=0;}
}T;
void solve(){
    T.clear();
    for(int i=1;i<=n;i++)   b[i]=a[i];
    ans=0;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        int mx=max(2,T.que(a[i].se));
        // for(int j=1;j<i;j++)if(a[i].fi>=a[j].fi&&a[i].se>=a[j].se)gmx(mx,a[j].fi+a[j].se);
        ans+=a[i].fi+d[a[i].se]-mx;
        T.add(a[i].se,a[i].fi+d[a[i].se]);
    }
    for(int i=1;i<=n;i++)   a[i]=b[i];
}
void discrete(){
    for(int i=1;i<=n;i++)   d[++m]=a[i].se;
    for(int i=1;i<=q;i++)   d[++m]=Q[i].se;
    sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=n;i++)   a[i].se=lower_bound(d+1,d+m+1,a[i].se)-d;
    for(int i=1;i<=q;i++)   Q[i].se=lower_bound(d+1,d+m+1,Q[i].se)-d;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),all+=a[i].fi+a[i].se-2;
    scanf("%d",&q);
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].fi,&Q[i].se);
    discrete();
    for(int i=1;i<=q;i++){
        n++;a[n]=Q[i];
        all+=a[n].fi+d[a[n].se]-2;
        solve();printf("%lld %lld\n",all,ans);
        all-=a[n].fi+d[a[n].se]-2;
        n--;
    }
}