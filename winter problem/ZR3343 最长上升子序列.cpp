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
const int maxn=1.5e5+10,inf=1e9;
int n;
int a[maxn],f[maxn],g[maxn];
inline void gmn(auto &x,auto y){if(x>y)x=y;}
inline void gmx(auto &x,auto y){if(x<y)x=y;}
struct BIT{
    pii tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,pii s){while(x<=n){gmx(tr[x],s);x+=lowbit(x);}}
    inline pii que(int x){pii res=pii(-inf,-inf);while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=n;i++)tr[i]=pii(-inf,-inf);}
}T;
void solve(int l,int r){
    if(l>r) return;
    if(f[l-1]==f[r+1]){for(int i=l;i<=r;i++)f[i]=f[i-1];return;}
    int mid=(l+r)>>1;
    T.clear();pii dp=pii(0,0);
    for(int i=1;i<=n;i++){
        pii to=dp,nw=T.que(a[i]-1);nw.fi++;
        to.fi-=mid-1;to.se++;
        // printf("(%d,%d)\n",max(to,nw).fi,max(to,nw).se);
        T.add(a[i],max(to,nw));
        gmx(dp,max(to,nw));
    }
    f[mid]=dp.se;
    solve(l,mid-1);solve(mid+1,r);
}
void matt(int _cases){
    T.clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),f[i]=0;
    f[0]=n;f[n+1]=0;
    solve(1,n);
    g[0]=0;
    for(int i=0;i<=n;i++)for(int j=f[i+1]+1;j<=f[i];j++)g[j]=i;
    for(int i=1;i<=n;i++)printf("%d ",g[i]+=g[i-1]);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}