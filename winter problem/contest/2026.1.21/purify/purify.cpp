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
using namespace std;
const int maxn=2e5+10;
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
int n,m;
ll sum;
ll a[maxn],s[maxn],b[maxn];
int c[maxn];
pli p[maxn];
bool check(){for(int i=1;i<=n;i++)if(s[i]<s[i-1])return false;return true;}
struct BIT{
    ll tr[maxn];
    int len;
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=len){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return que(r)-que(l-1);}
    void init(int x){len=x;for(int i=0;i<=len;i++)tr[i]=0;}
}T[3];
void discrete(){
    for(int i=1;i<=n;i++)b[i]=s[i]%sum;sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)c[i]=lower_bound(b+1,b+m+1,s[i]%sum)-b;
}
void discrete2(){
    memc(b,s);sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)c[i]=lower_bound(b+1,b+m+1,s[i])-b;
}
void matt(int _cases){
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    s[0]=0;for(int i=1;i<=n+n;i++)s[i]=s[i-1]+a[(i-1)%n+1];sum=s[n];
    if(s[n]<0||(!s[n]&&count(a+1,a+n+1,0)!=n))  return puts("-1"),void();
    if(*min_element(a+1,a+n+1)>=0)  return puts("0"),void();
    ll ans=0;
    for(int i=1;i<=n+n;i++) s[i]+=1e9+10;
    discrete();
    for(int i=1;i<=n+n;i++) p[i]=pli(s[i],i);
    sort(p+1,p+n+n+1);
    T[0].init(n+n);T[1].init(n+n);T[2].init(m);
    for(int i=1;i<=n+n;i++){
        auto [x,j]=p[i];
        T[0].add(j,x/sum);T[1].add(j,1);
        if(j<=n){
            ans+=((x-1)/sum+1)*T[1].query(j+1,j+n-1)-T[0].query(j+1,j+n-1);
            int r=(s[j]-1)%sum+1;
            if(r<=b[m])ans-=T[2].query(lower_bound(b+1,b+m+1,r)-b,m);
        }
        if(p[i].fi!=p[i+1].fi){int k=i;while(k>0&&p[k].fi==p[i].fi)if(p[k].se<=n)T[2].add(c[p[k--].se],1);else k--;}
    }
    discrete2();T[2].init(m);
    for(int i=1;i<=n;i++){
        // for(int j=1;j<=n;j++)if(s[j]<s[i])ans-=((s[i]-1)%sum+1<=s[j]%sum);
        int r=(s[i]-1)%sum+1;
        ll L=s[i]/sum*sum+r;while(L>=s[i])L-=sum;while(L<s[i]-sum)L+=sum;
        ll R=min(s[i]-1,L-r+sum-1);
        L=lower_bound(b+1,b+m+1,L)-b;
        R=upper_bound(b+1,b+m+1,R)-b-1;
        if(L<=R)    ans+=T[2].query(L,R);
        T[2].add(c[i],1);
        // for(int j=1;j<i;j++)if(s[i]-sum<=s[j]&&s[j]<=s[i]-1)ans+=((s[i]-1)%sum+1<=s[j]%sum);
        // for(int j=1;j<i;j++)ans+=(s[j]>=L&&s[j]<=R);
    }
    printf("%lld\n",ans);
}
int main(){freopen("purify.in","r",stdin);freopen("purify.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}