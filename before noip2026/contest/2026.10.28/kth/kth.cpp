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
int n,p;ll k;
ll a[maxn],b[maxn],c[maxn],d[maxn],e[maxn];
ll dd[maxn],ee[maxn];
struct SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all0(x) T[0].rt[x],1,dd[0]
    #define all1(x) T[1].rt[x],1,ee[0]
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tot,rt[maxn],tr[maxn*20],lc[maxn*20],rc[maxn*20];
    void U(int &p,int q,int l,int r,int x){
        p=++tot;tr[p]=tr[q]+1;lc[p]=lc[q];rc[p]=rc[q];
        if(l==r)return;
        setmid;(x<=mid)?U(ls,lc[q],l,mid,x):U(rs,rc[q],mid+1,r,x);
    }
    int Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid&&ls)res=Q(lson,pl,pr);if(pr>mid&&rs)res+=Q(rson,pl,pr);return res;}
}T[2];
bool check(ll w){
    w-=a[n];
    ll K=k;
    for(int i=1;i+p-1<=n;i++){
        if(i+p<=n-p+1){
            int x=upper_bound(dd+1,dd+dd[0]+1,w-b[i+p-1]+b[i-1])-dd;
            if(x^1) K-=T[0].Q(all0(n-p+1),1,x-1)-T[0].Q(all0(i+p-1),1,x-1);
        }
        if(i+1<=min(n-p+1,i+p-1)){
            int x=upper_bound(ee+1,ee+ee[0]+1,w+b[i-1]-c[i+p-1])-ee;
            if(x^1) K-=T[1].Q(all1(min(n-p+1,i+p-1)),1,x-1)-T[1].Q(all1(i),1,x-1);
        }
        if(K<=0)return true;
    }
    return false;
}
void discrete(){
    memc(dd,d);memc(ee,e);
    sort(dd+1,dd+n+1);int m=unique(dd+1,dd+n+1)-dd-1;dd[0]=m;
    for(int i=1;i<=n;i++)   d[i]=lower_bound(dd+1,dd+m+1,d[i])-dd;
    
    sort(ee+1,ee+n+1);m=unique(ee+1,ee+n+1)-ee-1;ee[0]=m;
    for(int i=1;i<=n;i++)   e[i]=lower_bound(ee+1,ee+m+1,e[i])-ee;
}
bool mem2;
int main(){
    freopen("kth.in","r",stdin);freopen("kth.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();p=read();k=readll();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   b[i]=read()-a[i];
    for(int i=1;i<=n;i++)   c[i]=read()-a[i]-b[i];
    for(int i=1;i<=n;i++)   a[i]+=a[i-1],b[i]+=b[i-1],c[i]+=c[i-1];
    for(int i=1;i<=n;i++)   d[i]=b[i+p-1]-b[i-1],e[i]=b[i+p-1]-c[i-1];
    discrete();
    for(int i=1;i<=n;i++)   T[0].U(T[0].rt[i],T[0].rt[i-1],1,dd[0],d[i]),T[1].U(T[1].rt[i],T[1].rt[i-1],1,ee[0],e[i]);
    ll l=a[n],r=a[n]+b[n]+c[n],ans;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else    l=mid+1;
    }
    printf("%lld\n",ans);
}