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
const int maxn=1e5+10;
int n;
ll ans;
struct node{int a,b,c,d;}a[maxn];
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
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define lso lc[p],l,mid
    #define rso rc[p],mid+1,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    #define setposp int &p,int l,int r
    #define pos p,l,r
    #define all(x) rt[x],1,n
    const int maxm=maxn*400;
    int tot;
    int rt[maxn<<2],tr[maxm],lc[maxm],rc[maxm];
    void upd(setposp,int x,int s){if(!p)p=++tot;tr[p]+=s;if(l==r)return;setmid;(x<=mid)?upd(lso,x,s):upd(rso,x,s);}
    inline void upd(int &q,int x,int s){
        if(!q)q=++tot;
        int l=1,r=n,p=q;
        while(l^r){
            tr[p]+=s;
            setmid;
            if(x<=mid){
                if(!lc[p])lc[p]=++tot;
                p=lc[p];r=mid;
            }
            else{
                if(!rc[p])rc[p]=++tot;
                p=rc[p];l=mid+1;
            }
        }
        tr[p]+=s;
    }
    void upd(setpos,int x,int y,int s){upd(rt[p],y,s);if(l==r)return;setmid;(x<=mid)?upd(lson,x,y,s):upd(rson,x,y,s);}
    int query(setpos,int pl,int pr){if(!p)return 0;if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid)res=query(lso,pl,pr);if(pr>mid)res+=query(rso,pl,pr);return res;}
    int query(setpos,int pl,int pr,int ql,int qr){if(l>=pl&&r<=pr)return query(all(p),ql,qr);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr,ql,qr);if(pr>mid)res+=query(rson,pl,pr,ql,qr);return res;}
    void clr(setpos){rt[p]=0;if(l==r)return;setmid;if(rt[ls])clr(lson);if(rt[rs])clr(rson);}
    void clear(){for(int i=0;i<=tot;i++)tr[i]=lc[i]=rc[i]=0;tot=0;}
}
using namespace SegmentTree;
void divide(int l,int r){
    if(l==r)    return;
    int mid=(l+r)>>1;
    divide(l,mid);divide(mid+1,r);
    auto cmpb=[&](node x,node y){return x.b<y.b;};
    sort(a+l,a+mid+1,cmpb);sort(a+mid+1,a+r+1,cmpb);
    ll res=0;
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid&&a[j].b<a[i].b){upd(1,1,n,a[j].c,a[j].d,1);j++;}
        if(a[i].c>1&&a[i].d>1)  res+=query(1,1,n,1,a[i].c-1,1,a[i].d-1);
    }
    ans+=res;
    clr(1,1,n);clear();
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)   a[i].a=read(),a[i].b=read(),a[i].c=read(),a[i].d=read();
    sort(a+1,a+n+1,[&](node x,node y){return x.a<y.a;});
    divide(1,n);
    printf("%lld\n",ans);
}