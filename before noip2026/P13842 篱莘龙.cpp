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
const int maxn=2e6+10;
int n;
pii a[maxn];
int b[maxn],c[maxn];
int f[maxn];
vector<pii> v[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n*2
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<int> vec[maxn<<2];
    struct tree{
        // a 的最大值，a 的最大值位置是否 b 都是最小值，b 的最小值
        int mx,fl,mnb,res;
        inline tree operator+(tree y){
            tree ret;
            ret.mx=max(mx,y.mx);
            if(mx>y.mx) ret.fl=fl&&mnb<=y.mnb;
            else if(mx<y.mx)    ret.fl=y.fl&&y.mnb<=mnb;
            else    ret.fl=fl&&y.fl&&mnb==y.mnb;
            ret.mnb=min(mnb,y.mnb);
            ret.res=max(res,y.res);
            return ret;
        }
    }tr[maxn<<2];
    int ta[maxn<<2],tb[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pta(int p,int s){tr[p].mx+=s;tr[p].res+=s;ta[p]+=s;}
    inline void ptb(int p,int s){
        tr[p].mnb+=s;tb[p]+=s;
        if(tr[p].fl&&!tr[p].mnb)    tr[p].res=tr[p].mx;
        else    tr[p].res=tr[p].mx+1;
    }
    inline void pd(int p){if(ta[p])pta(ls,ta[p]),pta(rs,ta[p]),ta[p]=0;if(tb[p])ptb(ls,tb[p]),ptb(rs,tb[p]),tb[p]=0;}
    void build(setpos){if(l==r)return tr[p]={0,1,0,0},void();setmid;build(lson);build(rson);pu(p);}
    void Ua(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pta(p,s);setmid;pd(p);if(pl<=mid)Ua(lson,pl,pr,s);if(pr>mid)Ua(rson,pl,pr,s);pu(p);}
    void Ub(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptb(p,s);setmid;pd(p);if(pl<=mid)Ub(lson,pl,pr,s);if(pr>mid)Ub(rson,pl,pr,s);pu(p);}
    void upd(setpos,int pl,int pr,int id){if(l>=pl&&r<=pr)return vec[p].eb(id),void();setmid;if(pl<=mid)upd(lson,pl,pr,id);if(pr>mid)upd(rson,pl,pr,id);}
    inline void get(int x,int id){
        int p=1,l=1,r=n*2;
        while(l^r){
            for(int i:vec[p])if(!f[i]){
                if(i>id)    f[i]=-1;
                else v[id].eb(a[i].se,a[i].fi),f[i]=1;
            }
            vec[p].clear();
            setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        for(int i:vec[p])if(!f[i]){
            if(i>id)    f[i]=-1;
            else v[id].eb(a[i].se,a[i].fi),f[i]=1;
        }
        vec[p].clear();
    }
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    read();n=read();
    for(int i=1;i<=n;i++)   a[i]=pii(read(),read()),swap(a[i].fi,a[i].se);
    for(int i=1;i<=n;i++)if(a[i].fi-1>=a[i].se+1)upd(all,a[i].se+1,a[i].fi-1,i);
    for(int i=1;i<=n;i++)if(a[i].fi<=a[i].se)get(a[i].fi,i),get(a[i].se,i);
    build(all);
    for(int i=1;i<=n;i++){
        int l=min(a[i].fi,a[i].se),r=max(a[i].fi,a[i].se);
        if(a[i].fi<=a[i].se)    Ua(all,l,r,1);
        else if(~f[i]) Ub(all,l,r,1);
        for(pii j:v[i]) Ub(all,j.fi,j.se,-1);
        print(tr[1].res,'\n');
    }
    FastIO::flush();
}