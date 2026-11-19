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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e6+10,mod=998244353,B=1<<15;
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
inline mit qpow(mit x,ll y){y%=(mod-1);mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
mit P[maxn],P2[maxn];
inline mit q2(ll y){y%=(mod-1);return P2[y>>15]*P[y&(B-1)];}
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
int n;
int a[maxn],b[maxn];
mit f[maxn],g[maxn],pq[maxn],inv[maxn];
set<int> s;
inline mit cf(int x,int i){
    int y=*s.upper_bound(x);
    // printf("f [%d,%d] : %d\n",x,y,f[x]*qpow(2,1ll*(y-x)*h));
    mit res=(q2(1ll*(y-x)*(i+1)+i)-pq[y-x])*inv[y-x+1];
    // for(int j=i;j;j--)res+=qpow(2,1ll*(y-x)*j)*pq[j-1];
    return res*f[x];
    // return f[x]*qpow(2,1ll*(y-x)*i)*pq[i-1];
}
inline mit cg(int y,int i){
    int x=*(--s.find(y));
    mit res=(q2(1ll*(y-x)*(i+1)+i)-pq[y-x])*inv[y-x+1];
    // for(int j=i;j;j--)res+=qpow(2,1ll*(y-x)*j)*pq[j-1];
    return res*g[y];
    // printf("g [%d,%d] : %d\n",x,y,g[y]*qpow(2,1ll*(y-x)*h));
    // return g[y]*qpow(2,1ll*(y-x)*i)*pq[i-1];
}
void baoli(){
    mit ans=0;
    for(int s=0;s<(1<<n);s++){
        fll(b,0,n+1);
        for(int i=1;i<=n;i++)if(s&(1<<i-1)){
            for(int j=1;j<=i;j++)gmx(b[j],a[i]);
        }
        else{
            for(int j=i+1;j<=n+1;j++)gmx(b[j],a[i]);
        }
        ll w=0;
        for(int i=1;i<=n+1;i++) w+=b[i];
        ans+=qpow(2,w);
    }
    printf("%d\n",ans);
    exit(0);
}
void init(){
    P[0]=1;for(int i=1;i<=B;i++)P[i]=P[i-1]*2;
    P2[0]=1;for(int i=1;i<=B;i++)P2[i]=P2[i-1]*P[B];
}
bool mem2;
int main(){
    freopen("god.in","r",stdin);freopen("god.out","w",stdout);
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read(),b[a[i]]=i;
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*2,inv[i]=qpow(pq[i]-1,mod-2);
    a[0]=n+1;a[n+1]=n+2;s.ep(0);s.ep(n+1);
    f[0]=1;
    mit sf=0,sg=0,ans=cf(0,n);
    for(int i=n;i;i--){
        auto it=s.lower_bound(b[i]);
        int y=*it,x=*prev(it);mit dp=a[x]<a[y]?f[x]:g[y];
        if(a[x]<a[y])   ans-=cf(x,i),f[x]=0;
        else    ans-=cg(y,i),g[y]=0;
        f[b[i]]=dp*q2(1ll*(b[i]-x)*i);g[b[i]]=dp*q2(1ll*(y-b[i])*i);
        s.ep(b[i]);
        ans+=cf(b[i],i-1)+cg(b[i],i-1);
    }
    for(int i=0;i<=n+1;i++){
        if(f[i])    ans+=f[i];
        if(g[i])    ans+=g[i];
    }
    printf("%d\n",ans);
}