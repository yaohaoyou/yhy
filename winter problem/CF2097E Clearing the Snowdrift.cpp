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
const int maxn=5e5+10,B=2000;
int n,m,d;
pii a[maxn];
int f[maxn],to[maxn];
bool liv[maxn];
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
void matt(int _cases){
    n=read();d=read();
    for(int i=1;i<=n;i++){
        a[i]=pii(read(),i);
        to[i]=min(((i-1)/B+1)*B,n)+1;f[i]=0;
    }
    for(int i=1;i<=n;i++)   liv[i]=false;
    sort(a+1,a+n+1,greater<pii>());a[n+1].fi=0;
    ll ans=0;int st=1e9;
    for(int i=1;i<=n;i++){
        st=min(st,a[i].se);
        int x=a[i].se,id=(x-1)/B+1,l=(id-1)*B+1,r=min(id*B,n);
        liv[x]=true;
        int lst=0;
        for(int j=x;j>=l;j--){
            if(liv[j])  lst=j;
            if(lst+d>r)   to[j]=lst+d,f[j]=1;
            else    to[j]=to[lst+d],f[j]=f[lst+d]+1;
        }
        if(a[i].fi^a[i+1].fi){
            int x=st,sum=0;while(x<=n)sum+=f[x],x=to[x];
            ans+=1ll*sum*(a[i].fi-a[i+1].fi);
        }
    }
    printf("%lld\n",ans);
}
int main(){int T=read();for(int i=1;i<=T;i++)matt(i);}