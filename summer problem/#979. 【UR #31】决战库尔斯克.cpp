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
const int maxn=5e5+10;
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
ll ans;
ll a[maxn];
void solve(int l,int r){
    if(l>=r)    return;
    ll d;int mid=r;
    while(mid>=l&&a[mid]*2>a[r]) mid--;
    ans=max(ans,d=a[r]-a[mid+1]);
    solve(l,mid);
    while(l<=mid&&a[l]<=ans+1)    l++;
    for(int i=l;i<=mid;i++){
        ll p=a[r]/a[i]-1;
        // a[i]*p,a[i]*(p+1)-1;
        int k=lower_bound(a+1,a+n+1,(p+1)*a[i])-a-1;
        if(a[k]>=a[i])ans=max(ans,a[k]%a[i]);
        ans=max(ans,a[r]%a[i]);
    }
}
void matt(){
    ans=0;
    n=read();
    for(int i=1;i<=n;i++)   a[i]=readll();
    sort(a+1,a+n+1);
    solve(1,n);
    printf("%lld\n",ans);
}
int main(){int T=read();while(T--)matt();}