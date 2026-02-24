#pragma GCC optimize(2,3,"Ofast","inline")
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
const int maxn=5e5+10,M=2000,maxk=M+10,mod=998244353;
int n,k;
int a[maxn];
int f[maxn],g[maxn],h[maxn],ff[maxn],gg[maxn];
int fac[maxn],inv[maxn];
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
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
void init(){
    const int N=5e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return (x<0||y<0||x<y)?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int fa[maxn],cc[maxn];
int c=0;
void data(){
    n=5e5;
    for(int i=1;i<n;i++)   printf("%d ",i);puts("");
    exit(0);
}
void matt(){
    // data();
    scanf("%d%d",&n,&k);
    for(int i=2;i<=n;i++)   scanf("%d",&fa[i]);
    for(int i=1;i<=n;i++)   h[i]=0,g[i]=gg[i]=1,ff[i]=1;
    for(int i=0;i<=n;i++)   cc[i]=C(i,k-1);
    int ans=0;
    for(int _=1;_<=M;_++){
        for(int u=1;u<=n;u++)   f[u]=0;
        for(int u=2;u<=n;u++){
            f[fa[u]]+=g[u];
        }
        for(int u=1;u<=n;u++){
            int s=f[u]+gg[fa[u]]-h[u];
            if(u==1)    s=f[u];
            assert(s>=0&&s<=n);
            madd(ans,cc[s]);
            // if(s>=k-1)  printf("%d %d\n",s,k-1);
            g[u]=s;
        }
        for(int j=1;j<=n;j++)   gg[j]=g[j],g[j]=f[j],h[j]=ff[j];
        for(int j=1;j<=n;j++)   ff[j]=f[j];
        // for(int j=1;j<=n;j++)   printf("%d : %d %d\n",j,i,gg[j]);
    }
    if(k==1)    ans=n;
    if(k==2)    ans=immul(n,n-1);
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}