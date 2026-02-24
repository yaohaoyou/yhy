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
const int maxn=2e6+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){if(y<0)return qpow(qpow(x,-y),mod-2);int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
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
int n;
int a[maxn],b[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=2e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return (x<0||y<0||x<y)?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    init();
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   b[i]=read();
    sort(a+1,a+n+1);sort(b+1,b+n+1);
    int ans=1;
    ll H=n,W=n;
    for(int l1=1,l2=1;l1<=n||l2<=n;){
        ll h,w,x;
        if(l1<=n&&a[l1]<b[l2]){
            int r1=l1;while(r1<=n&&a[r1]==a[l1])    r1++;r1--;
            h=r1-l1+1;w=0;x=a[l1];
            l1=r1+1;
        }
        else if(a[l1]==b[l2]){
            int r1=l1;while(r1<=n&&a[r1]==a[l1])    r1++;r1--;
            int r2=l2;while(r2<=n&&b[r2]==a[l1])  r2++;r2--;
            h=r1-l1+1;w=r2-l2+1;x=a[l1];
            l1=r1+1;l2=r2+1;
        }
        else{
            int r2=l2;while(r2<=n&&b[r2]==b[l2])    r2++;r2--;
            h=0;w=r2-l2+1;x=b[l2];
            l2=r2+1;
        }
        int res=0;
        for(int i=0;i<=h;i++){
            int vi=1ull*C(h,i)*qpow(x,i*W)%mod*qpow(x+1,(h-i)*W+w*H-h*w)%mod;
            if(i&1) vi=imdel(0,vi);
            int X=qpow(mod-immul(x,qpow(x+1,mod-2)),H-i);
            if((H-i+1)&1){
                // for(int j=0;j<=w;j++){
                //     int v=1ull*C(w,j)*qpow(X,j)%mod;
                //     if((j*(H-i+1))&1) v=imdel(0,v);
                //     mmul(v,vi);
                //     madd(res,v);
                // }
                int v=qpow(imadd(1,mod-X),w);
                mmul(v,vi);madd(res,v);
            }
            else{
                int v=qpow(imadd(1,X),w);
                mmul(v,vi);madd(res,v);
            }
        }
        mmul(ans,res);
        H-=h;W-=w;
    }
    printf("%d\n",ans);
}