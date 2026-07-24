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
const int maxn=1e6+10,inf=1e9;
const ll INF=1e18;
int n;
ll a[maxn],f[maxn];  // f[i] 表示现在在 i+0.5，到达 0 的答案
inline void gmn(auto &x,auto y){if(x>y)x=y;}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
struct Line{int k;ll b;Line(int x=inf,ll y=0){k=x;b=y;};ll get(int x){return 1ll*k*x+b;}};
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int b[maxn];
    Line tr[maxn<<2];
    void upd(setpos,Line x){
        setmid;
        Line &u=tr[p];
        if(u.k==inf)    return u=x,void();
        if(u.get(b[mid])>x.get(b[mid])) swap(u,x);
        if(l==r)    return;
        (u.k<x.k)?upd(lson,x):upd(rson,x);
    }
    ll query(setpos,int x){ll res=tr[p].k!=inf?tr[p].get(x):INF;if(l==r)return res;setmid;return (x<=b[mid])?min(query(lson,x),res):min(query(rson,x),res);}
    inline void clear(){for(int i=0;i<=(n<<2);i++)tr[i]=Line();}
}T[2];
void matt(int _cases){
    T[0].clear();T[1].clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   T[0].b[i]=-a[i],T[1].b[i]=i;
    sort(T[0].b+1,T[0].b+n+1);
    f[0]=0;
    T[0].upd(all,Line(0,-1));
    for(int i=1;i<=n;i++){
        f[i]=min({f[i-1]+a[i],T[0].query(all,-a[i])+i*a[i]+i,T[1].query(all,i)+i+i});
        // printf("ins (%d,%d) %lld\n",i,f[i]-i-1,T[0].query(all,-a[i]));
        T[0].upd(all,Line(i,f[i]-i-1));
        T[1].upd(all,Line(a[i],f[i]-i*a[i]-i-i));
        // printf("%d ",f[i]);
        // for(int j=0;j<i;j++){
        //     gmn(f[i],(-a[i]*j+f[j]-j-1)+i*a[i]+i);
        //     if(j)   gmn(f[i],(i*a[j]+f[j]-j*a[j]-j*2)+i*2);
        // }
        printf("%lld ",f[i]);
    }
    puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}