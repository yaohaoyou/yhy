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
bool mem1;
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
const int maxn=1e6+10;
int n;
ll b;
bool check(LL x){
    LL l=x*n*(n-2)+2*n,r=x*(n-1)*(n-1);
    return l<r;
}
bool chk(LL x){
    LL l=x*n*(n-2)+2*n,r=x*(n-1)*(n-1);
    if(l>=r) return 0;
    b=l/(1ll*n*(n-1))+1;assert(LL(b)*n*(n-1)>l);
    return (LL(b)*n*(n-1)>l&&LL(b)*n*(n-1)<r);
}
void data(){
    int T=1000;
    printf("%d\n",T);
    for(int i=1;i<=T;i++) printf("%d\n",i+1);
    exit(0);
}
void matt(){
    // data();
    n=read();
    if(n==2){
        puts("0 1\n1 1\n1 1");
        return;
    }
    ll l=1,r=1e13,res=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid))  res=mid,r=mid-1;
        else    l=mid+1;
    }
    for(ll a=res;;a++){
        if(chk(a)){
            printf("%lld %lld\n",1ll*n*(n-2),a);
            printf("1 1 ");for(int i=3;i<=n;i++)printf("%lld ",a);puts("");
            check(a);for(int i=1;i<=n;i++)printf("%lld ",b);puts("");
            break;
        }
    }
    // for(int i=1;i<=100;i++)if(check(i))printf("i = %d\n",i);puts("");
    // assert(res);
    // printf("%lld %lld\n",1ll*n*(n-2),res);
    // printf("1 1 ");for(int i=3;i<=n;i++)printf("%lld ",res);puts("");
    // check(res);for(int i=1;i<=n;i++)printf("%lld ",b);puts("");
}
bool mem2;
int main(){
    freopen("tasc.in","r",stdin);freopen("tasc.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=read();while(T--)matt();
}