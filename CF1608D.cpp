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
const int maxn=6e5+10,mod=998244353,inv2=(mod+1)>>1,inv4=1ull*inv2*inv2%mod;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int fac[maxn],inv[maxn],pq[maxn];
void init(){
    const int N=maxn-10;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    pq[0]=1;for(int i=1;i<=N;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int n;
int a[maxn],b[maxn],f[maxn<<1],s[3][3];
char ch[5];
bool check(int x,int y){for(int i=1;i<=n;i++)if(a[i]==3-x||b[i]==3-y)return false;return true;}
void calc(int x){mems(f,0);for(int i=0;i<=x;i++)for(int j=0;i+j<=x;j++)madd(f[i-j+n],1ull*C(x,i)*C(x-i,j)%mod*pq[x-i-j]%mod);for(int i=0;i<=n+n;i++)printf("%d ",f[i]);puts("");}
void matt(int _cases){
    mems(s,0);mems(f,0);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",ch);
        a[i]=ch[0]=='?'?0:(ch[0]=='W')+1;
        b[i]=ch[1]=='?'?0:(ch[1]=='W')+1;
        s[a[i]][b[i]]++;
    }
    int ans=mod-1;for(int i=1;i<=n;i++)if(!a[i]&&!b[i])madd(ans,ans);else if(a[i]&&a[i]==b[i])ans=0;
    madd(ans,check(1,2)+check(2,1));
    // for(int i=n-s[0][0];i<=s[0][0]+n;i++)   f[i]=C(s[0][0]*2,s[0][0]+i-n);
    int l=-s[0][0],r=s[0][0];
    r+=s[0][1];
    // for(int i=l;i<=r;i++)  f[i+n]=C(s[0][0]*2+s[0][1],s[0][0]+i);
    l-=s[0][2];
    // for(int i=l;i<=r;i++){
    //     int x=s[0][0]*2+s[0][1],y=s[0][0],z=s[0][2];
    //     f[i+n]=C(x+z,x-y-i);
    // }
    r+=s[1][0];
    // for(int i=l;i<=r;i++){
    //     int x=s[0][0]*2+s[0][1]+s[0][2],y=s[0][0]+s[0][1],z=s[1][0];
    //     f[i+n]=C(x+z,x-y+i);
    // }
    l-=s[2][0];
    for(int i=l;i<=r;i++){
        int x=s[0][0]*2+s[0][1]+s[0][2]+s[1][0],y=s[0][0]+s[0][2],z=s[2][0];
        f[i+n]=C(x+z,x-y-i);
    }
    madd(ans,f[n-s[1][1]+s[2][2]]);
    printf("%d\n",ans);
}
int main(){init();int T=1;for(int i=1;i<=T;i++)matt(i);}