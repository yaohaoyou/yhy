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
const int maxn=1e6+10,maxv=1e7+10,mod=998244353;
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
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,q;
int d[maxv];
bool ntp[maxv];
vector<int> p;
int a[maxn][10],len[maxn];
vector<pii> Q[maxn];
int lst[maxv];
mit ans[maxn],I[maxv],fac[maxv];
struct BIT{
    mit tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,mit s){while(x<=n){tr[x]*=s;x+=lowbit(x);}}
    inline mit que(int x){mit res=1;while(x){res*=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?mit(0):que(r)*qpow(que(l-1),mod-2);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=1;}
}T;
bool mem2;
void data(){
    n=1e6;
    printf("%d\n",n);for(int i=1;i<=n;i++)printf("9699690 ");puts("");
    printf("%d\n",n);while(n--)printf("%d %d\n",1,1000000);
    exit(0);
}
int main(){
    freopen("easy.in","r",stdin);freopen("easy.out","w",stdout);
    // data();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=1e7;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) p.eb(i),d[i]=i;
        for(int j:p){
            if(1ll*i*j>n)   break;
            ntp[i*j]=true;d[i*j]=j;
            if(i%j==0)  break;
        }
    }
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    mit inv=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)I[i+1]=inv*fac[i],inv*=(i+1);
    mems(ntp,0);
    n=read();
    for(int i=1;i<=n;i++){
        int x=read();
        while(x^1){
            if(!ntp[d[x]])  a[i][++len[i]]=d[x];
            ntp[d[x]]=true;
            x/=d[x];
        }
        for(int j=1;j<=len[i];j++)ntp[a[i][j]]=false;
    }
    q=read();
    for(int i=1;i<=q;i++){int l=read(),r=read();Q[r].eb(l,i);}
    T.clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++){
            if(lst[a[i][j]])    T.add(lst[a[i][j]],I[a[i][j]]);
            T.add(i,a[i][j]);
            lst[a[i][j]]=i;
        }
        for(auto [l,id]:Q[i])   ans[id]=T.query(l,i);
    }
    for(int i=1;i<=q;i++)   print(ans[i],'\n');Flush();
}