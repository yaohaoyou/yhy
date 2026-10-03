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
using namespace std;
const int maxn=1e6+10,maxq=1e4+10,maxk=1010;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,q,k,T;
struct db{
    ll p,q;
    db(ll x=0,ll y=0){p=x;q=y;/*if(p&&q){int g=__gcd(abs(p),abs(q));p/=g;q/=g;}*/}
    inline db operator*(ll x){return db(p*x,q);}
    inline db operator+(ll x){return db(p+q*x,q);}
    inline bool operator<(db x)const{return LL(p)*x.q<LL(x.p)*q;}
    inline bool operator>(db x)const{return LL(p)*x.q>LL(x.p)*q;}
};
inline db abs(db x){return db(abs(x.p),x.q);}
struct line{
    int a,b;
    inline db get(int x){return db(b-a,T)*x+a;}
}a[maxn];
int main(){
    n=read();T=read();k=read();
    for(int i=1;i<=n;i++)   a[i]=(line){read(),read()};
    sort(a+1,a+n+1,[&](line x,line y){return x.a<y.a;});
    q=read();
    while(q--){
        int x=read(),d=read();
        int L=1,R=n;db ans=db(1e9,1);
        while(L<=R){
            int mid=(L+R)>>1;
            bool up=0,dw=0;
            for(int i=max(1,mid-k);i<=min(mid+k,n);i++){
                db dis=a[i].get(x)+(-d);
                if(dis.p>=0)    dw=1;
                else    dis.p*=-1,up=1;
                ans=min(ans,dis);
            }
            if(up&&dw){
                for(int i=max(1,mid-k-k);i<mid-k;i++)   ans=min(ans,abs((a[i].get(x)+(-d))));
                for(int i=mid+k;i<=min(mid+k+k,n);i++)  ans=min(ans,abs((a[i].get(x)+(-d))));
                break;
            }
            if(up)  L=mid+1;
            else    R=mid-1;
        }
        ll g=__gcd(ans.p,ans.q);
        ans.p/=g;ans.q/=g;
        printf("%lld %lld\n",ans.p,ans.q);
    }
}