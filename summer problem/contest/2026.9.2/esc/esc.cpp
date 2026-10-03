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
const int maxn=1e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,L;
int a[maxn],b[maxn],d[maxn];
pii c[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=L){madd(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){madd(res,tr[x]);x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:imdel(que(r),que(l-1));}
    void clear(){for(int i=0;i<=L;i++)tr[i]=0;}
}T;
void discrete(){
    for(int i=1;i<=n;i++)d[++L]=c[i].se;d[++L]=0;
    sort(d+1,d+L+1);L=unique(d+1,d+L+1)-d-1;
    for(int i=1;i<=n;i++)   c[i].se=lower_bound(d+1,d+L+1,c[i].se)-d;
}
int main(){
    // freopen("esc.in","r",stdin);freopen("esc.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    int N=0;
    for(int i=1;i<=n;i++){
        int l,r;
        l=upper_bound(b+1,b+m+1,a[i])-b-1;
        r=lower_bound(b+1,b+m+1,a[i])-b;
        if(l&&r&&l<=m&&r<=m)    c[++N]=pii(a[i]-b[l],b[r]-a[i]);
    }
    n=N;
    sort(c+1,c+n+1);n=unique(c+1,c+n+1)-c-1;
    discrete();
    T.add(1,1);
    for(int i=1;i<=n;i++){
        int r=i;while(r<=n&&c[r].fi==c[i].fi)r++;r--;
        for(int k=r;k>=i;k--)   T.add(c[k].se,T.query(1,c[k].se-1));
        i=r;
    }
    printf("%lld\n",T.query(1,L));
}