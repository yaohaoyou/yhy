#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<cstdio>
#include<vector>
#include<random>
#include<cassert>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define ep emplace
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define rep(i,s,b) for(int i=s;i<=(b);++i)
#define per(i,s,b) for(int i=s;i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=4e5+10,M=N*4,mod=998244353,B=131;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int n,p[N],q[N];
char s[N];
#define int mit
#define ll mit
struct SGT{
    #define ls (x<<1)
    #define rs (x<<1|1)
    int L[M],R[M];mit v[M],t[M];
    void bd(int l=1,int r=n,int x=1){
        L[x]=l,R[x]=r;v[x]=t[x]=0;
        if(l==r) return;
        int m=l+r>>1;
        bd(l,m,ls);bd(m+1,r,rs);
    }
    void pu(int x){v[x]=v[ls]+v[rs];}
    void cal(int x,mit k){v[x]+=k*(R[x]-L[x]+1),t[x]+=k;}
    void pd(int x){if(t[x])cal(ls,t[x]),cal(rs,t[x]),t[x]=0;}
    void upd(int l,int r,mit k,int x=1){
        if(L[x]>r||R[x]<l) return;
        if(l<=L[x]&&R[x]<=r) return cal(x,k);
        pd(x);upd(l,r,k,ls);upd(l,r,k,rs);pu(x);
    }
    mit qry(int l,int r,int x=1){
        if(L[x]>r||R[x]<l||l>r) return 0;
        if(l<=L[x]&&R[x]<=r) return v[x];
        pd(x);return qry(l,r,ls)+qry(l,r,rs);
    }
}t1,t2;
#undef int
#undef ll
int z[N],rz[N];
namespace Z{
    void build(){
        int p,r=0;
        for(int i=2;i<=n;i++){
            if(i<=r)    z[i]=min(r-i+1,z[i-p+1]);
            else    z[i]=0;
            while(i+z[i]<=n&&s[i+z[i]]==s[1+z[i]])z[i]++;
            if(i+z[i]-1>r) r=i+z[i]-1,p=i;
        }
        reverse(s+1,s+n+1);
        r=0;
        for(int i=2;i<=n;i++){
            if(i<=r)    rz[i]=min(r-i+1,rz[i-p+1]);
            else    rz[i]=0;
            while(i+rz[i]<=n&&s[i+rz[i]]==s[1+rz[i]])rz[i]++;
            if(i+rz[i]-1>r) r=i+rz[i]-1,p=i;
        }
        reverse(s+1,s+n+1);
    }
}
inline int rv(int x){return n+1-x;}
void misaka(int _ID){
    scanf("%s",s+1);
    n=strlen(s+1);
    Z::build();
    rep(i,1,n) p[i]=rz[rv(i-1)],q[i]=z[i];
    mit ans=0;
    t1.bd(),t2.bd();
    int j=0;
    rep(i,n/2+1,n){
        int L=max(i+1,n+1-p[i]),R=min(i+q[i],n);
        while(j<2*i-n-2){
            j++;
            int x=min(q[j],j-2);
            t1.upd(1,x,1),t2.upd(1,x,j);
        }
        ans+=t1.qry(L-i,R-i)*mit(2*i-n-2)-t2.qry(L-i,R-i);
    }
    printf("%d\n",ans);
}
bool __ed;
signed main(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=read();
    rep(i,1,T) misaka(i);
    return 0;
}
