#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(LL x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
const int maxn=1e6+10;
int n,m,k;
ll a[maxn],b[maxn],g[maxn];
LL pre[maxn];
deque<pli> q;
void matt(int _cases){
    n=read();readll();k=read();
    LL sum=0,ans=0;
    for(int i=1;i<=n;i++)   a[i]=readll(),sum+=a[i];
    sort(a+1,a+n+1);
    m=0;int N=0;
    for(int i=1;i<=n;i++){
        int j=i;while(j<=n&&a[j]==a[i])j++;j--;
        for(int l=i+1;l<=j;l++) b[++m]=a[l];
        a[++N]=a[i];
        i=j;
    }
    for(int i=1;i<=m;i++)   pre[i]=pre[i-1]+b[i];
    LL s=0;ll lst=0;
    for(int i=1;i<=N;i++){
        s+=a[i];
        g[i]=__gcd(g[i-1],a[i]);
        if(k-i+1<0) break;
        if(k-i+1<=m)    ans=max(ans,sum-s+g[i]-pre[k-i+1]);
        if(k-i<=m){
            if(g[i]!=lst){
                q.clear();
                for(int j=i+1;j<=N;j++){
                    ll x=__gcd(g[i],a[j])-a[j];
                    while(!q.empty()&&q.back().fi<x) q.pop_back();
                    q.eb(x,j);
                }
                lst=g[i];
            }
            while(!q.empty()&&q.front().se<=i)   q.pop_front();
            if(!q.empty())  ans=max(ans,sum-s-pre[k-i]+q.front().fi);
        }
    }
    print(ans);putc('\n');
}
int main(){int T=read();for(int i=1;i<=T;i++)matt(i);flush();}