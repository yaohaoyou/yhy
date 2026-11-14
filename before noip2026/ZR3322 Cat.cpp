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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=100010;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
ll n;int q;
unordered_map<ll,int> a;
vector<int> fr[maxn];
int cnt[maxn];
vector<ll> v;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%lld%d",&n,&q);
    ll l=1,r=n,p=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(LL(mid)*(mid+1)<=n)  p=mid,l=mid+1;
        else    r=mid-1;
    }
    ll x=p*(p+1);LL ans=LL(4)*p*(p+1)*(p+p+1)/6-p*(p+1)/2;
    if(n-x<=p+1)    ans+=LL(n-x)*(2*p+1),p=p<<1|1;
    else    ans+=LL(2*p+1)*(p+1)+LL(n-x-p-1)*(2*p+2),p=(p+1)<<1;
    print(ans);putc('\n');flush();//if(!q)return 0;
    for(int i=1;;i++){
        ll x=i,c=1;
        vector<ll> nw;
        if(!a[i]){
            a[i]=i,nw.eb(i);
        }
        while(x>=i){
            x=(x-c)<<1;c<<=1;
            if(x>i&&!a[x]){
                a[x]=i,nw.eb(x);
            }
        }
        if(v.size()+nw.size()>=n){
            sort(nw.begin(),nw.end(),greater<ll>());
            for(int i=0;v.size()<n;i++)   v.eb(nw[i]);
            break;
        }
        else for(ll i:nw)v.eb(i);
    }
    sort(v.begin(),v.end());
    ll sum=0;for(ll i:v)sum+=a[i],fr[a[i]].eb(i),cnt[a[i]]++;
    // for(int i=1;i<=n;i++){
    //     printf("%d : ",i);for(int j:fr[i])    printf("%d ",j);
    //     puts("");
    // }
    // printf("%d %d\n",a[v.back()],p);
    assert(a[v.back()]==p);
    for(int i=1;i<=n;i++)   printf("%d\n",cnt[i]);puts("");
    while(q--){
        int x;scanf("%d",&x);
        ll l=0,r=1e18,ans=0;
        while(l<=r){
            ll mid=(l+r)>>1,now=0;
            for(ll x=2;x<=mid*2;x<<=1){
                // x/2+x*(k-1)<=mid && __lg(x)+1+2*(k-1)<=p;
                ll k=min((mid-x/2)/x+1,(p-__lg(x)-1)/2+1);
                now+=max(0ll,k);
            }
            if(now>=x)  ans=mid,r=mid-1;
            else    l=mid+1;
        }
        printf("%lld %lld\n",ans,v[x-1]);
        // printf("%d\n",a[v[x-1]],v[x-1]);
    }
}