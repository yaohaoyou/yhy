#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
const ll INF=6e18;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
bool mem1;
int n;
int a[maxn];
ll f[maxn],g[maxn],s[maxn],sd[maxn],su[maxn],p[maxn];
struct line{
    ll k;LL b;
    line(ll _k=0,LL _b=-INF){k=_k;b=_b;}
    inline LL get(ll x){return LL(k)*x+b;}
};
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll b[maxn];int m;
    line tr[maxn<<2];
    inline void ins(line x){
        int p=1,l=1,r=m;
        while(true){
            setmid;
            line &y=tr[p];
            if(x.get(b[mid])>y.get(b[mid]))   swap(x,y);
            if(l==r)return;
            if(x.get(b[l])>y.get(b[l]))   p=ls,r=mid;
            else if(x.get(b[r])>y.get(b[r]))  p=rs,l=mid+1;
            else    return;
        }
    }
    inline ll query(ll x){
        int p=1,l=1,r=m,X=lower_bound(b+1,b+m+1,x)-b;ll res=-INF;
        while(l^r){
            setmid;
            gmx(res,tr[p].get(x));
            (X<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        gmx(res,tr[p].get(x));
        return res;
    }
    void clear(){fll(tr,line(),(n<<2)+5);}
    void build(ll *ar){
        for(int i=1;i<=n;i++)   b[i]=ar[i];
        sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    }
}T[2];
inline ll sdw(int l,int r){return sd[r]-sd[l-1]-(2*(n-r)+1-3)*(s[r]-s[l-1]);}
inline ll sup(int l,int r){return su[r]-su[l-1]-(2*l-4)*(s[r]-s[l-1]);}
bool mem2;
void matt(int _cases){
    T[0].clear();T[1].clear();
    n=read();a[n+1]=0;
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i],su[i]=su[i-1]+1ll*a[i]*(i+i-1),sd[i]=sd[i-1]+1ll*a[i]*((n-i)*2+1);
    if(n==1)    return printf("%d\n",a[1]),void();
    iota(p+1,p+n+1,1);T[0].build(p);
    for(int i=1;i<=n;i++)   p[i]=a[i]+a[i+1]+2*s[i-1];
    T[1].build(p);
    f[1]=g[1]=a[1];
    for(int i=1;i<=n;i++){
        if(i^1){
            f[i]=g[i]=-INF;
            // for(int j=i-1;j;j--)    gmx(f[i],(g[j]-sd[j]-1ll*j*(a[j]+a[j-1])+2*(n-1)*s[j])+1ll*i*(a[j]+a[j-1]-2*s[j]));
            f[i]=T[0].query(i);
            f[i]+=sd[i]-(2*(n-i)-2)*s[i];
            // for(int j=1;j<i;j++)    gmx(g[i],f[j]-su[j-1]-a[j]+(2*j-4)*s[j-1]-1ll*j*(a[i]+a[i+1]+2*s[i-1]));
            g[i]=T[1].query(a[i]+a[i+1]+2*s[i-1]);
            g[i]+=1ll*i*(a[i]+a[i+1])+a[i]+su[i-1]+4*s[i-1];
        }
        T[0].ins(line(a[i]+a[i-1]-2*s[i],g[i]-sd[i]-1ll*i*(a[i]+a[i-1])+2*(n-1)*s[i]));
        T[1].ins(line(-i,f[i]-su[i-1]-a[i]+(2*i-4)*s[i-1]));
        // printf("%d %d\n",f[i],g[i]);
    }
    printf("%lld\n",max(f[n],g[n]));
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}