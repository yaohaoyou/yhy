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
const int maxn=2e5+10,mod=998244353;
struct mint{
    int v;
    mint(int _x=0){v=_x;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mint operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mint operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mint operator*(int y){return 1ull*v*y%mod;}
};
inline mint qpow(mint x,int y){mint res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,m,q;
int a[maxn],b[maxn];
mint g[maxn],s[maxn];
mint f[20][maxn],F[20][maxn];
struct BIT{
    int now;
    mint tr[maxn];int tim[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void chk(int x){if(tim[x]^now)tim[x]=now,tr[x]=0;}
    inline void add(int x,mint s){x++;while(x<=n+1){chk(x);tr[x]+=s;x+=lowbit(x);}}
    inline mint que(int x){x++;mint res=0;while(x){chk(x);res+=tr[x];x^=lowbit(x);}return res;}
    inline mint query(int l,int r){return l>r?mint(0):que(r)-que(l-1);}
    void clear(){now++;}
}T;
void divide(int L,int R,int d){
    if(L==R)    return;
    int l=b[L-1]+1,r=b[R];
    int mid=(L+R)>>1,p=b[mid];
    T.clear();T.add(a[p],1);f[d][p+1]=1;
    for(int i=p+2;i<=r;i++){
        int w=T.que(a[i]-1);
        if(a[i]<a[i-1])T.clear();
        T.add(a[i-1],w);
        f[d][i]=f[d][i-1]+T.que(n);
    }

    T.clear();T.add(a[p+1],1);f[d][p]=1;
    for(int i=p-1;i>=l;i--){
        int w=T.query(a[i]+1,n);
        if(a[i]>a[i+1])T.clear();
        T.add(a[i+1],w);
        f[d][i]=f[d][i+1]+T.que(n);
    }
    divide(L,mid,d+1);divide(mid+1,R,d+1);
    F[d][L]=F[d+1][L]+F[d+1][mid+1]+f[d][l]*f[d][r];
}
mint dvd(int L,int R,int d,int ql,int qr){
    if(L==R)    return 0;
    int l=b[L-1]+1,r=b[R];
    if(l>=ql&&r<=qr)    return F[d][L];
    int mid=(L+R)>>1,p=b[mid];
    if(ql<=p&&qr>p) return f[d][max(ql,l)]*f[d][min(qr,r)]+dvd(L,mid,d+1,ql,qr)+dvd(mid+1,R,d+1,ql,qr);
    if(qr<=p)   return dvd(L,mid,d+1,ql,qr);
    return dvd(mid+1,R,d+1,ql,qr);
}
bool mem2;
int main(){
    // freopen("c.in","r",stdin);freopen("c.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   g[i]=g[i-1]+qpow(2,i)-1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=2;i<=n;i++)if(a[i]<a[i-1])b[++m]=i-1;
    b[++m]=n;
    for(int i=1;i<=m;i++)   s[i]=s[i-1]+g[b[i]-b[i-1]];
    divide(1,m,0);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        mint ans=dvd(1,m,0,l,r);
        int kl=lower_bound(b,b+m+1,l-1)-b+1,kr=upper_bound(b+1,b+m+1,r)-b-1;
        if(kl<=kr)  ans+=s[kr]-s[kl-1];
        if(--kl){
            int L=max(l,b[kl-1]+1),R=min(b[kl],r);
            if(L<=R)ans+=g[R-L+1];
        }
        if(++(kr)^kl){
            int L=max(l,b[kr-1]+1),R=min(b[kr],r);
            if(L<=R)ans+=g[R-L+1];
        }
        ans*=2;
        printf("%d\n",ans);
    }
}