#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pil pair<int,ll>
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
const int maxn=1e6+10;
const ll INF=1e18;
bool mem1;
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
int a[maxn],b[maxn],pr[maxn],sf[maxn];
ll s[maxn],f[maxn];
vector<pii> v,seg[maxn];
pil stk[maxn];
int sl;
bool mem2;
void matt(int _cases){
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   b[i]=read();
    ll ans=0;
    {
        int p=0;sf[0]=1e9;
        for(int i=1;i<=n;i++)if(b[i]>=0)pr[i]=max(pr[p],a[i]),p=i;
        p=0;for(int i=n;i;i--)if(b[i]>=0)sf[i]=min(sf[p],a[i]),p=i;
    }
    v.clear();
    for(int i=1;i<=n;i++)if(b[i]>=0){
        if(pr[i]^sf[i]) ans+=b[i];
        else    v.eb(a[i],i);
    }
    if(v.empty())   return printf("%lld\n",ans),void();
    v.insert(v.begin(),pii(0,0));
    for(int i=1;i<v.size();i++)s[i]=s[i-1]+b[v[i].se];
    for(int i=1,j=0;i<=n;i++)if(b[i]<0){
        while(j+1<v.size()&&v[j+1].se<i)    j++;
        int k=upper_bound(v.begin(),v.end(),pii(a[i],1e9))-v.begin();
        if(k<v.size()&&v[k].se<i){if(j>=0)seg[j].eb(k,b[i]);}
        else{
            k=lower_bound(v.begin(),v.end(),pii(a[i],0))-v.begin()-1;
            if(j+1<=k)  seg[k].eb(j+1,b[i]);
        }
    }
    fll(f,0,v.size());
    f[0]=sl=0;stk[++sl]=pil(0,f[0]);
    for(int i=1;i<v.size();i++){
        f[i]=f[i-1];
        for(auto [l,w]:seg[i]){
            gmx(f[i],f[l-1]+s[i]-s[l-1]+w);
            if(l<i){
                pil t=*lower_bound(stk+1,stk+sl+1,pil(l,-INF));
                assert(t.fi>=l);
                gmx(f[i],t.se+s[i]+w);
            }
        }
        pil w=pil(i,f[i]-s[i]);
        while(sl&&stk[sl].se<=w.se)sl--;
        stk[++sl]=w;
        seg[i].clear();
    }
    seg[0].clear();
    printf("%lld\n",ans+f[v.size()-1]);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);read();int T=read();for(int i=1;i<=T;i++)matt(i);}