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
int n,q;
int a[maxn],b[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mn[maxn<<2],mx[maxn<<2],tr[maxn<<2],len[maxn<<2],tag[maxn<<2];
    ll sum[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);mn[p]=min(mn[ls],mn[rs]);mx[p]=max(mx[ls],mx[rs]);sum[p]=sum[ls]+sum[rs];}
    inline void pt(int p,int s){tag[p]=s;mn[p]=mx[p]=s;sum[p]=1ll*len[p]*s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){if(l==r)return tr[p]=a[l],len[p]=1,void();setmid;build(lson);build(rson);pu(p);len[p]=len[ls]+len[rs];}
    int bry(setpos,int pl,int pr,int s){
        if(tr[p]<=s)    return 0;
        if(l==r)    return l;
        pd(p);setmid;
        if(l>=pl&&r<=pr)    return tr[ls]>s?bry(lson,pl,pr,s):bry(rson,pl,pr,s);
        if(pr<=mid)return bry(lson,pl,pr,s);
        if(pl>mid)return bry(rson,pl,pr,s);
        int x=bry(lson,pl,pr,s);if(x)return x;
        return bry(rson,pl,pr,s);
    }
    inline int bl(int s){
        int p=1,l=1,r=n;
        while(l^r){pd(p);setmid;(mx[ls]>=s)?(p=ls,r=mid):(p=rs,l=mid+1);}
        return l;
    }
    inline int br(int s){
        int p=1,l=1,r=n;
        while(l^r){pd(p);setmid;(mn[rs]>s)?(p=ls,r=mid):(p=rs,l=mid+1);}
        return mn[p]==s?l:0;
    }
    inline int f(int x){int w=bry(all,x,n,x);return w?w-1:n;}
    inline void upd(int x){
        int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);};
        tr[p]=a[x];mn[p]=mx[p]=sum[p]=f(x);while(p>>=1)pu(p);
    }
    void U(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)U(lson,pl,pr,s);if(pr>mid)U(rson,pl,pr,s);pu(p);}
    ll Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return sum[p];pd(p);setmid;ll res=0;if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)res+=Q(rson,pl,pr);return res;}
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=i-read()+1;
    build(all);
    for(int i=1;i<=n;i++)   upd(i);
    while(q--){
        int op=read(),l=read(),r=read();
        if(op==1){
            int x=l,L=bl(x-1),R=br(x-1);
            a[x]=x-r+1;
            upd(x);
            if(R){
                while(L<=R){
                    int fl=f(L);
                    if(fl==n){U(all,L,R,n);break;}
                    else{
                        U(all,L,a[fl+1]-1,fl);
                        // assert(a[fl+1]-1<=R);
                        for(int j=L;j<a[fl+1];j++)  assert(f(j)==fl);
                        L=a[fl+1];
                    }
                }
            }
            L=bl(x);
            if(L<=a[x]-1)   U(all,L,a[x]-1,x-1);
        }
        else{
            ll ans=0;
            int p=bl(r);
            if(p<=r)    ans+=1ll*(r-max(l,p)+1)*r;
            if(p>l) ans+=Q(all,l,p-1);
            ans-=1ll*(l+r-2)*(r-l+1)/2;
            // for(int i=l;i<=r;i++)   ans+=min(r,f(i))-i+1,assert(f(i)==Q(all,i,i));
            printf("%lld\n",ans);
        }
    }
}