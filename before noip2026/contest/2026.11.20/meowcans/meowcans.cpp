#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<mit,mit>
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
const int maxn=(1<<20)+10,maxm=1e5+10,mod=998244353,inv2=(mod+1)>>1,B=100;
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
mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,N;
int a[maxn],b[maxn];
mit fac[maxm],inv[maxm],S[maxn],T[maxn];
vector<pii> dvd(int l,int r,int d){
    int mid=(l+r)>>1;
    // debug("%d %d %d %d\n",l,mid,r,d);
    vector<pii> f(r-l+1);
    if(l==r){f[0]=pii(S[l],T[l]);return f;}
    vector<pii> fl=dvd(l,mid,d-1),fr=dvd(mid+1,r,d-1);
    for(int i=0;i<fl.size();i++)    f[i]=pii(fl[i].fi*fr[i].fi,fl[i].se*fr[i].se);
    for(int i=0;i<fl.size();i++)    f[i+fl.size()]=pii(fl[i].fi*fr[i].se,fl[i].se*fr[i].fi);
    return f;
}
void init(){
    n=1e5;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
inline mit C(int x,int y){return x<0||y<0||x<y?mit(0):fac[x]*inv[y]*inv[x-y];}
vector<mit> IFWT(vector<mit> f){
    for(int i=0;i<n;i++){
        for(int j=0;j<=N;j++)if(!(j&(1<<i))){
            mit x=f[j],y=f[j^(1<<i)];
            f[j]=(x+y)*inv2;f[j^(1<<i)]=(x-y)*inv2;
        }
    }
    return f;
}
struct ques{int l,r,id;}Q[maxn];
bool mem2;
int main(){
    freopen("meowcans.in","r",stdin);freopen("meowcans.out","w",stdout);
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();N=(1<<n)-1;
    for(int i=0;i<=N;i++)   a[i]=read();
    for(int i=0;i<=N;i++)   b[i]=read();
    for(int i=0;i<=N;i++){
        // for(int j=0;j<=b[i];j++)    S[i]+=C(a[i],j);
        Q[i]={b[i],a[i],i};
        if(!a[i])   T[i]=1;
        else{
            if(b[i]&1)  T[i]=mod-C(a[i]-1,b[i]);
            else    T[i]=C(a[i]-1,b[i]);
        }
        // printf("%d %d\n",S[i],T[i]);
    }
    sort(Q,Q+N+1,[&](ques x,ques y){return (x.l-1)/B+1==(y.l-1)/B+1?x.r<y.r:x.l<y.l;});
    mit now=1;
    for(int i=0,l=0,r=0;i<=N;i++){
        while(l>Q[i].l) now-=C(r,l),l--;
        while(r<Q[i].r) now=now*2-C(r,l),r++;
        while(l<Q[i].l) l++,now+=C(r,l);
        while(r>Q[i].r) r--,now=(now+C(r,l))*inv2;
        S[Q[i].id]=now;
    }
    vector<pii> res=dvd(0,N,n);vector<mit> F;
    for(pii i:res)F.eb(i.fi);
    vector<mit> ans=IFWT(F);
    for(mit i:ans)  printf("%d ",i);
}