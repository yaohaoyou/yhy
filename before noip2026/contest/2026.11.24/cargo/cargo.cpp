#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=3e5+10;
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
bool mem1;
int n,m;
ll a[maxn],b[maxn];
int ht[maxn];
pll c[maxn<<1];int siz;
struct SET{
    priority_queue<ll> q1,q2;
    inline void clear(){while(!q1.empty())q1.pop();while(!q2.empty())q2.pop();}
    inline void ep(ll x){q1.ep(x);}
    inline void erase(ll x){q2.ep(x);}
    inline ll top(){while(!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();return q1.top();}
    inline void pop(){q1.pop();}
    inline bool empty(){return q1.size()==q2.size();}
}st;
bool mem2;
void matt(int _cases){
   st.clear();siz=0;
    n=read();m=read();a[n+1]=0;
    for(int i=1;i<=n;i++)   a[i]=read(),a[i]+=a[i-1];
    for(int i=1;i<=m;i++)   b[i]=read(),b[i]+=b[i-1];
    ll x=max(b[m]-a[n],0ll),ans=1e18;
    for(int i=0,j=0;i<=n;i++){
        while(j<m&&a[i]+x>=b[j+1])j++;
        if(i){
            for(int k=ht[i-1];k<=j;k++){
                if(k^m) c[++siz]=pll(b[k+1]-a[i-1],a[i]-b[k]);
                st.ep(a[i]-b[k]);
            }
        }
        else{
            for(int k=0;k<=j;k++)st.ep(a[i]-b[k]);
        }
        ht[i]=j;
    }
    ans=st.top()+x;
    sort(c+1,c+siz+1);
    for(int _=1;_<=siz;_++){
        st.erase(c[_].se);
        gmn(ans,c[_].fi+st.top());
    }
    printf("%lld\n",ans);
}
int main(){freopen("cargo.in","r",stdin);freopen("cargo.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);read();int T=read();for(int i=1;i<=T;i++)matt(i);}