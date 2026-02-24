#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,maxk=20,maxK=(1<<18)+10,mod=998244353;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,k;
ll b[maxn][maxk];
pli A[maxn],B[maxn];
int p[maxn],f[maxK],S[maxn],T[maxn],fac[maxn],inv[maxn];
int g[maxK];bool h[maxK];
int str[maxk];
inline int C(int x,int y){
    if(x<y||x<0||y<0)   return 0;
    int ret=1;
    for(int i=1;i<=y;i++)   mmul(ret,x-i+1);
    mmul(ret,inv[y]);
    return ret;
}
void init(){
    const int N=18;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    for(int i=0;i<=k&&i<=m;i++){
        for(int j=0;j<=i;j++){
            if(j&1) mdel(str[i],immul(C(i,j),qpow(i-j,m)));
            else madd(str[i],immul(C(i,j),qpow(i-j,m)));
        }
        mmul(str[i],inv[i]);
    }
}
int main(){
    n=read();m=read();k=read();const int K=(1<<k)-1;
    init();
    int tot=0;
    for(int i=1;i<=n;i++)   A[i]=pli(readll(),i);
    for(int i=1;i<=n;i++){
        ll x=readll();
        B[i]=pli(x,i);
        for(int j=0;j<k;j++){b[i][j]=x%10;x/=10;}
    }
    sort(A+1,A+n+1);sort(B+1,B+n+1);
    for(int i=1;i<=n;i++)   p[B[i].se]=A[i].se;
    for(int i=1;i<n;i++){
        for(int j=0;j<k;j++)
            if(b[i][j]<b[i+1][j])S[i]|=1<<j;
            else if(b[i][j]>b[i+1][j])T[i]|=1<<j;
    }
    for(int i=1;i<n;i++)    g[K^S[i]]|=T[i],h[K^S[i]]=(p[i]>p[i+1]);
    for(int i=0;i<k;i++)for(int j=0;j<=K;j++)if(j&(1<<i))g[j^(1<<i)]|=g[j],h[j^(1<<i)]|=h[j];
    f[0]=1;
    auto lowbit=[&](int x){return x&-x;};
    for(int i=0;i<=K;i++){
        int ri=K^i;
        while(ri){
            int x=__lg(lowbit(ri));
            if(!(g[i]&(1<<x)))    madd(f[i|(1<<x)],f[i]);
            ri^=lowbit(ri);
        }
    }
    int ans=0;
    for(int s=0;s<=K;s++)
        if(!h[s])   madd(ans,immul(str[__builtin_popcount(s)],f[s]));
    printf("%d\n",ans);
}