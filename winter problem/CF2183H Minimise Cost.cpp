#include<bits/stdc++.h>
#define LL __int128
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
const int maxn=5e5+10;
int n,m,st;
int a[maxn];ll s[maxn];
LL dp[maxn];int p[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(LL x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
inline LL w(int l,int r){return LL(r-l+1)*(s[r]-s[l-1]);}
inline LL h(int x,int r){return dp[x]+w(x+1,r);}
deque<pii> dq;
int DP(LL x){
    dq.clear();
    dq.eb(0,1);
    for(int i=1;i<=n;i++){
        if((i^1)&&a[i]<0)   continue;
        while(dq.size()>1&&dq[1].se<=i) dq.pop_front();
        dp[i]=h(dq[0].fi,i)-x;p[i]=p[dq[0].fi]+1;
        while(!dq.empty()&&h(i,max(max(st,i+1),dq.back().se))<h(dq.back().fi,max(max(st,i+1),dq.back().se)))dq.pop_back();
        if(dq.empty()){dq.eb(i,1);continue;}
        int l=max(max(st,i+1),dq.back().se),r=n,j=dq.back().fi,k=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(h(i,mid)<h(j,mid))  k=mid,r=mid-1;
            else l=mid+1;
        }
        if(k)   dq.eb(i,k);
    }
    return p[n];
}
void matt(int _cases){
    n=read();m=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    sort(a+1,a+n+1);
    st=1;while(st<=n&&a[st]<0)st++;
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    if(n-st+1<=m){
        LL ans=0;
        reverse(a+1,a+n+1);
        for(int i=1;i<m;i++)    ans+=a[i];
        for(int i=m;i<=n;i++)   ans+=1ll*a[i]*(n-m+1);
        print(ans);putc('\n');
        return;
    }
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    LL l=-1e9*n*n,r=1e9*n*n,k;
    while(l<=r){
        LL mid=(l+r)>>1;
        if(DP(mid)<=m)  k=mid,l=mid+1;
        else    r=mid-1;
    }
    DP(k);
    print(dp[n]+k*m);putc('\n');
}
int main(){int T=read();for(int i=1;i<=T;i++)matt(i);flush();}