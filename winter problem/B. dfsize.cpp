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
const int maxn=5010;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ll x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n;
int a[maxn],dp[maxn][maxn];
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
void matt(int _cases){
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    ll ans=0;
    for(int i=n;i;i--){
        dp[i][i]=0;
        for(int j=i+1;j<=n;j++) dp[i][j]=dp[i+1][j];
        dp[i][i+a[i]-1]++;
        for(int j=i+a[i];j<=n;j++)  gmx(dp[i][j],dp[i][i+a[i]-1]+dp[i+a[i]][j]);
        ans+=(a[i]!=1);
        for(int j=i+1;j<=n;j++) ans+=a[i]^a[j]^(j-i-dp[i+1][j]+(a[i]!=j-i+1));
        // for(int j=i+1;j<=n;j++) printf("%d %d : %d\n",i,j,dp[i][j]);
    }
    printf("%lld\n",ans);
}
int main(){int T=read();for(int i=1;i<=T;i++)matt(i);}