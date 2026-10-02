#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
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
int n;
int t[maxn];
ll p[maxn],f[maxn];
priority_queue<pli> q;
int a[maxn];
ll check(ll en){
    while(!q.empty())q.pop();
    ll now=0;int i=1,s=0;
    while(s^n){
        int j=i;
        if(i<=n&&(p[a[i]]<=now||q.empty()||p[a[i]]<en-q.top().fi)){
            if(p[a[i]]<=now){
                while(j<=n&&p[a[j]]<=now){
                    q.ep(t[a[j]]+f[a[j]],a[j]);
                    j++;
                }
            }
            else{
                gmx(now,p[a[i]]);
                q.ep(t[a[j]]+f[a[j]],a[j]);
                j++;
            }
        }
        if(now+q.top().fi<en&&(i>n||p[a[i]]>=en-q.top().fi))   now=en-q.top().fi;
        while(!q.empty()&&now+q.top().fi>=en){
            now+=t[q.top().se];
            s++;
            q.pop();
        }
        i=j;
    }
    return now<=en;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)   p[i]=readll(),t[i]=read(),f[i]=readll();
    iota(a+1,a+n+1,1);
    sort(a+1,a+n+1,[&](int x,int y){return p[x]<p[y];});
    ll l=0,r=5e14,p=-1;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid))  p=mid,r=mid-1;
        else    l=mid+1;
    }
    printf("%lld\n",p);
}