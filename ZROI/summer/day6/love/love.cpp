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
const int maxn=2e6+10;
const ll INF=1e18;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline int read01(){char c=getc();while(c<48||c>49)c=getc();return c-'0';}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::read01;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,m,k;
int a[maxn],b[maxn];
int id[maxn],bl[maxn],br[maxn];
ll f[maxn][2],g[maxn];
inline ll calc(int l,int x){
    ll res=0;
    for(int i=l,j=bl[x];i<=l+k-1;i++,j++)   res+=abs(b[i]-j);
    return res;
}
void data(){
    puts("1");
    n=2e6;k=2;
    printf("%d %d\n",n,k);
    for(int i=1;i<=n;i++)printf("%d",rand()&1);puts("");
    exit(0);
}
void matt(int _cases){
    // data();
    n=read();k=read();
    for(int i=1;i<=n;i++)   a[i]=read01(),id[i]=(i-1)/k+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*k,n);
    m=0;for(int i=1;i<=n;i++)if(!a[i])b[++m]=i;
    if(m%k||n%k)    return puts("-1"),void();
    for(int i=1;i<=m/k;i++){
        int L=id[b[bl[i]]],R=id[b[br[i]]];
        if(i==1){
            for(int j=L;j<=R;j++)g[j]=calc(bl[i],j);
        }
        else{
            if(id[b[br[i-1]]]==L)   g[L]=f[i-1][0]+calc(bl[i],L);
            else    g[L]=min(f[i-1][0],f[i-1][1])+calc(bl[i],L);
            for(int j=L+1;j<=R;j++) g[j]=min(f[i-1][0],f[i-1][1])+calc(bl[i],j);
        }
        for(int j=L+1;j<=R;j++) gmn(g[j],g[j-1]);
        f[i][1]=g[R];
        f[i][0]=L==R?INF:g[R-1];
        for(int j=L;j<=R;j++)   g[j]=0;
    }
    printf("%lld\n",min(f[m/k][0],f[m/k][1]));
}
int main(){freopen("love.in","r",stdin);freopen("love.out","w",stdout);int T=read();for(int i=1;i<=T;i++)matt(i);}