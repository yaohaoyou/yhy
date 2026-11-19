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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
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
const int maxn=1e6+10;
int n,k,q;
int ans[maxn];
vector<pii> Q[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],pos[maxn];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    int s;
    void build(setpos){if(l==r)return pos[l]=p,void();setmid;build(lson);build(rson);}
    int bry(setpos,int pr){
        if(l==r){
            if(tr[p]<s){s-=tr[p];return 0;}
            return l;
        }
        setmid;
        if(r<=pr){
            if(tr[rs]<s){s-=tr[rs];return bry(lson,pr);}
            return bry(rson,pr);
        }
        if(pr<=mid) return bry(lson,pr);
        int x=bry(rson,pr);if(x)return x;
        return bry(lson,pr);
    }
    inline void upd(int x){int p=pos[x];tr[p]++;while(p>>=1)pu(p);}
}
using namespace SegmentTree;
pii a[maxn];
int f[maxn];
bool mem2;
int main(){
    freopen("devil.in","r",stdin);freopen("devil.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();k=read();q=read();
    for(int i=1;i<=n;i++)   a[i].fi=read(),a[i].se=i;
    build(all);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        s=k;f[a[i].se]=bry(all,a[i].se);
        upd(a[i].se);
    }
    for(int i=1;i<=q;i++){
        int l=read(),r=read();
        Q[l-1].eb(l,-i);Q[r].eb(l,i);
    }
    for(int i=1,c=0;i<=n;i++){
        if(f[i])    T.add(f[i],1);
        else    c++;
        for(auto [l,id]:Q[i]){
            if(id<0)    ans[-id]-=T.que(l-1)+c;
            else    ans[id]+=T.que(l-1)+c;
        }
    }
    for(int i=1;i<=q;i++)   print(ans[i],'\n');
    Flush();
}