#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,maxm=55;
int m,q;
int a[maxn];
ull ans[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ull x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
inline ll S(int l,int r){return l>r?0:1ull*(l+r)*(r-l+1)/2;}
struct tree{
    int k,rt=1;
    ull f[70],pq[70];
    int lim;
    ull dvd(ll n,int x,int de){
        if(n<=k+1){
            ull res=0;
            if(n&1) res=S(2,n/2+1)*2+1;
            else res=S(2,n/2)*2+n/2+2;
            res+=de*n;
            return res;
        }
        ll all=1;
        // x=0;while(pq[x]+pq[x]*k+1<=n)x++;
        while(pq[x]+LL(pq[x])*k+1>n)x--;x++;
        // printf("%d %d %lld\n",x,k,n);
        all=pq[x];
        ll l=1,r=n/(all+1),p=(n-all/k)/(all+1);
        ull res=f[x]*p+S(de+1,de+p)*all+S(de+1,de+p);
        all=(all+1)*p;
        return res+dvd(n-all,x,de+p);
    }
    ull slv(ll n){
        if(k==1){
            ll d=0;ull ans=0;
            while((1ll<<(d+1))-1<=n)    d++,ans+=d*(1ll<<d-1);
            n-=(1ll<<d)-1;
            return ans+n*(d+1);
        }
        return dvd(n,lim,0);
    }
    void build(){
        const ll N=1e18;
        ll x=k;
        f[0]=pq[0]=1;
        for(int i=1;;i++){
            pq[i]=x;lim=i;
            f[i]=dvd(x,i,0);
            if(LL(x)*k<=N)  x*=k;
            else break;
        }
    }
}T[maxm];
namespace Sub2{
    void solve(){
        while(q--){
            ll n=readll();
            ll d=0;ull ans=0;
            while((1ll<<(d+1))-1<=n)    d++,ans+=d*(1ll<<d-1);
            n-=(1ll<<d)-1;
            ans+=n*(d+1);
            print(ans);putc('\n');
        }
        flush();
        exit(0);
    }
}
mt19937_64 matt(time(0));
inline ll rd(){return abs((ll)matt())%1000000000000000000ll;}
void data(){
    m=50;q=1e5;
    printf("%d %d\n",m,q);
    for(int i=1;i<=m;i++)printf("%d ",i+1);puts("");
    while(q--)  printf("%lld\n",rd());
    exit(0);
}
int main(){
    // data();
    m=read();q=read();
    for(int i=1;i<=m;i++)   T[i].k=read();
    if(m==1&&T[1].k==1) Sub2::solve();
    for(int i=1;i<=m;i++)if(T[i].k^1)T[i].build();
    while(q--){
        ll n=readll();ull ans=0;
        for(int i=1;i<=m;i++)   ans+=T[i].slv(n);
        print(ans);putc('\n');
    }
    flush();
}