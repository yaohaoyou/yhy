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
const int maxn=4e5+10,inf=1e9;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline int read01(){char c=getc();while((c^48)&&(c^49))c=getc();return c-48;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::read01;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n,q;
bool a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2][2],tr2[maxn<<2][2],pos[maxn<<2];bool tag[maxn<<2],tr3[maxn<<2][2],R[maxn<<2];
    inline void pu(int p){
        tr[p][0]=min(tr[ls][0],tr[rs][0]);tr[p][1]=min(tr[ls][1],tr[rs][1]);
        tr2[p][0]=min(tr2[ls][0],tr2[rs][0]);tr2[p][1]=min(tr2[ls][1],tr2[rs][1]);
        tr3[p][0]=tr3[ls][0]|tr3[rs][0];tr3[p][1]=tr3[ls][1]|tr3[rs][1];
        R[p]=R[rs];
    }
    inline void pt(int p){swap(tr[p][0],tr[p][1]);swap(tr2[p][0],tr2[p][1]);swap(tr3[p][0],tr3[p][1]);R[p]^=1;tag[p]^=1;}
    inline void pd(int p){if(tag[p]){pt(ls);pt(rs);tag[p]=false;}}
    void build(setpos){tag[p]=0;tr[p][0]=tr[p][1]=tr2[p][0]=tr2[p][1]=inf;if(l==r)return tr[p][a[l]]=pos[p]=l,R[p]=a[l],void();setmid;build(lson);build(rson);pu(p);pos[p]=pos[ls];}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    inline int query(int x){if(x<=0||x>n)return -1;int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return R[p];}
    inline void upd(int x){
        int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        int a1=query(x-2),a2=query(x-1),a3=query(x);
        tr2[p][0]=tr2[p][1]=inf;tr3[p][0]=tr3[p][1]=false;
        if(x>1&&a2==a3)  tr2[p][a3]=x;
        if(x>2&&a1!=a2&&a2!=a3) tr3[p][a3]=true;
        while(p>>=1)pu(p);
    }
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p][0];pd(p);setmid,res=inf;if(pl<=mid){res=query(lson,pl,pr);if(res^inf)return res;}return query(rson,pl,pr);}
}
using namespace SegmentTree;
inline int solve(){
    int p=tr2[1][1];
    if(p==inf)   return tr3[1][1];
    if(p==n)    return tr3[1][1];
    int k=query(all,p+1,n);
    return (k!=inf)?n-k+1:tr3[1][1];
}
void matt(){
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read01();
    build(all);
    for(int i=1;i<=n;i++)   upd(i);
    ll ans=solve();
    for(int i=1;i<=q;i++){
        int l=read(),r=read();
        upd(all,l,r);upd(l);if(l+1<=n)upd(l+1);if(r+1<=n)upd(r+1);if(r+2<=n)upd(r+2);
        ans^=1ll*(i+1)*solve();
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%*d%d",&T);while(T--)matt();}