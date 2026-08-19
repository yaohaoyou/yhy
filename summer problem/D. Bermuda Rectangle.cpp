#include<bits/stdc++.h>
#define int long long
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=6e5+10;
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
ll n;int m,q;
pii Q[maxn];
LL ans[maxn];
void matt(int _cases){
    m=0;for(int i=1;i<=q;i++)ans[i]=0;
    scanf("%lld%lld",&n,&q);
    ll x=n;
    vector<ll> d;
    for(ll i=1;i*i<=x;i++){
        if(x%i==0){
            d.eb(i);
            if(i!=x/i)  d.eb(x/i);
        }
    }
    d.eb(0);
    sort(d.begin(),d.end());
    for(int i=1;i<=q;i++){
        ll x,y;scanf("%lld%lld",&x,&y);
        int k=upper_bound(d.begin(),d.end(),n/y)-d.begin()-1;
        ll lef=0;
        if(k>=0&&k<d.size())    ans[i]=LL(min(x,d[k]))*y,lef=min(x,d[k]);
        if(lef<x)   Q[++m]=pii(x,i),Q[++m]=pii(lef,-i);
    }
    sort(Q+1,Q+m+1);
    int i=1;LL now=0;
    for(int j=0;j+1<d.size();j++){
        ll l=d[j]+1,r=d[j+1];
        while(i<=m&&Q[i].fi<=r){
            if(Q[i].se>0)   ans[Q[i].se]+=now+LL(Q[i].fi-l+1)*(n/r);
            else    ans[-Q[i].se]-=now+LL(Q[i].fi-l+1)*(n/r);
            i++;
        }
        now+=LL(r-l+1)*(n/r);
        // printf("%lld : %lld\n",r,int(now));
    }
    for(int i=1;i<=q;i++)   print(ans[i],'\n');
}
main(){int T;scanf("%lld",&T);for(int i=1;i<=T;i++)matt(i);flush();}