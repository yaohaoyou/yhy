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
const int maxn=2e6+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char ch){if(!x)return putc(48),putc(ch),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
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
    int tr[maxn<<2],tag[maxn<<2],pos[maxn];
    int mn[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pu2(int p){mn[p]=min(mn[ls],mn[rs]);}
    void build(setpos){if(l==r)return pos[l]=p,tr[p]=a[l],void();setmid;build(lson);build(rson);pu(p);}
    inline void pt(int x){int p=pos[x];tag[p]=tr[p];while(p^1){if(p&1)p>>=1,tag[p]=max(tr[ls],tag[rs]);else p>>=1,tag[p]=tag[ls];}}
    int binary(setpos,int x){
        if(l==r)    return l;
        setmid;if(x<=mid)return binary(lson,x);
        if(r>=x){
            if(max(a[mid],tag[rs])<=x)  return binary(lson,x);
            return binary(rson,x);
        }
        else{
            if(max(a[mid],tr[rs])<=x)   return binary(lson,x);
            return binary(rson,x);
        }
    }
    inline void upda(int x,int s){a[x]=s;int p=pos[x];tr[p]=s;while(p>>=1)pu(p);}
    inline void upd(int x,int s){int p=pos[x];mn[p]=s;while(p>>=1)pu2(p);}
    int bry(setpos,int x){
        if(mn[p]>x) return -1;
        if(l==r)    return l;
        setmid;if(x>mid)return bry(rson,x);
        int res=bry(lson,x);if(~res)return res;
        return bry(rson,x);
        // if(l<=x){
        //     if(min(a[mid+1],tag[ls])<=x)    return binary(rson,x);
        // }
    }
}
using namespace SegmentTree;
inline int binary(int x){
    if(a[x]>x)  return x+1;
    pt(x);
    return binary(all,x);
}
int main(){
    freopen("ds.in","r",stdin);freopen("ds.out","w",stdout);
    read();n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    build(all);
    for(int i=1;i<=n;i++)   upd(i,b[i]=binary(i));
    // for(int i=1;i<=n;i++)   printf("%d ",b[i]);puts("");
    int lstans=0;
    while(q--){
        int op=read(),p=read()^lstans,val;
        if(op==1){
            val=read()^lstans;
            upda(p,val);
            upd(p,b[p]=binary(p));
            upd(val,b[val]=binary(val));
        }
        else{
            if(a[p]<=p){print(lstans=p,'\n');debug("%d\n",lstans);continue;}
            print(lstans=bry(all,p),'\n');
            if(lstans==692){
                for(int i=387;i<=690;i++)   printf("%d ",a[i]);puts("");
                printf("%d\n",*max_element(a+387,a+690+1));
                debug("%d %d %d %d\n",p,a[p],lstans,binary(690));
            }
        }
    }
    flush();
}