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
const int maxn=1e6+10,mod=1e9+7;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,q,tot;
struct SGT{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],len[maxn<<2],tag[maxn<<2];
    inline void pt(int p,int s){madd(tr[p],immul(len[p],s));madd(tag[p],s);}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    inline void pu(int p){tr[p]=imadd(tr[ls],tr[rs]);}
    void build(setpos){if(l==r)return len[p]=1,void();setmid;build(lson);build(rson);len[p]=len[ls]+len[rs];}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)madd(res,query(rson,pl,pr));return res;}
}T;
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],val[maxn<<2],tag[maxn<<2],sz[maxn<<2],lf[maxn<<2],siz[maxn<<2],dfn[maxn<<2],L[maxn<<2],R[maxn<<2];
    void build(setpos){dfn[p]=++tot;if(l==r)return sz[p]=siz[p]=lf[p]=1,L[dfn[p]]=R[dfn[p]]=l,void();setmid;build(lson);build(rson);siz[p]=siz[ls]+siz[rs]+(lf[p]=lf[ls]+lf[rs]);sz[p]=sz[ls]+sz[rs]+1;L[dfn[p]]=l;R[dfn[p]]=r;}
    inline void pt(int p,int s){madd(val[p],s);madd(tag[p],s);madd(tr[p],immul(siz[p],s));}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    inline void pu(int p){tr[p]=imadd(immul(val[p],lf[p]),imadd(tr[ls],tr[rs]));}
    void upd(setpos,int pl,int pr,int s){
        if(dfn[p]+sz[p]-1<pl||dfn[p]>pr)    return;
        if(pl<=dfn[p]&&dfn[p]+sz[p]-1<=pr)  return pt(p,s),void();
        if(pl<=dfn[p]&&dfn[p]<=pr)  madd(val[p],s);
        pd(p);setmid;
        upd(lson,pl,pr,s);upd(rson,pl,pr,s);
        pu(p);
    }
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=immul(val[p],min(r,pr)-max(l,pl)+1);if(pl<=mid)madd(res,query(lson,pl,pr));if(pr>mid)madd(res,query(rson,pl,pr));return res;}
    int queryL(setpos,int pl,int pr){if(dfn[p]+sz[p]-1<pl||dfn[p]>pr)return 1e9;if(pl<=dfn[p]&&dfn[p]<=pr)return l;pd(p);setmid,res=1e9;res=queryL(lson,pl,pr);if(res==1e9)res=queryL(rson,pl,pr);return res;}
    int queryR(setpos,int pl,int pr){if(dfn[p]+sz[p]-1<pl||dfn[p]>pr)return 0;if(pl<=dfn[p]&&dfn[p]<=pr)return r;pd(p);setmid,res=0;res=queryR(rson,pl,pr);if(!res)res=queryR(lson,pl,pr);return res;}
    void print(setpos){printf("[%d,%d] : %d\n",l,r,tr[p]);if(l==r)return;pd(p);setmid;print(lson);print(rson);pu(p);}
}
using namespace SegmentTree;
int main(){
    freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    n=read();q=read();
    build(all);T.build(all);
    while(q--){
        int op=read(),l=read(),r=read();
        if(op==1)   upd(all,l,r,read());
        else if(op==2)  T.upd(all,queryL(all,l,r),queryR(all,l,r),read());
        else print(imadd(T.query(all,l,r),query(all,l,r))),putc('\n');
        // print(all);
    }
    flush();
}