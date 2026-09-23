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
const int maxn=3e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
    inline void mdiv(int &x,int y){mmul(x,qpow(y,mod-2));}
    inline int imdiv(int x,int y){mdiv(x,y);return x;}
}
using namespace FastMod;
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
int n,q;
int a[maxn],b[maxn];
int fac[maxn],inv[maxn];
int ans=1;
set<int> s;
void init(){
    const int N=3e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int iC(int x,int y){return x<y?0:1ull*inv[x]*fac[y]%mod*fac[x-y]%mod;}
int solve(int x){
    int lst=1;
    for(int i:s)    mmul(ans,C(n-lst,i-lst-1)),lst=i;
    return ans;
}
inline void del(int x){
    if(x==1)    return;
    auto it=s.lower_bound(x);
    int lst=1;if(it!=s.begin())lst=*prev(it);
    mmul(ans,iC(n-lst,x-lst-1));
}
inline void add(int x){
    if(x==1)    return;
    auto it=s.lower_bound(x);
    int lst=1;if(it!=s.begin())lst=*prev(it);
    mmul(ans,C(n-lst,x-lst-1));
}
void chk(int x){
    if((x^1)&&(x<=n)){
        if(a[x]>a[x-1]){
            if(s.find(x)==s.end()){
                auto it=s.lower_bound(x);
                int nx=0;if(it!=s.end())nx=*it;
                if(nx)del(nx);
                s.ep(x);add(x);if(nx)add(nx);
            }
        }
        else{
            if(s.find(x)!=s.end()){
                auto it=s.find(x);
                del(x);
                int nx=0;
                if(next(it)!=s.end())nx=*next(it);
                if(nx)del(nx);
                s.erase(it);
                if(nx)  add(nx);
            }
        }
    }
}
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=2;i<=n;i++)if(a[i]>a[i-1])s.ep(i);
    print(solve(1),'\n');
    while(q--){
        int x=read(),y=read();swap(a[x],a[y]);
        chk(x);chk(x+1);chk(y);chk(y+1);
        // printf("%d\n",solve(1));
        print(ans,'\n');
    }
    Flush();
}