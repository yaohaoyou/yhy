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
    int fr[maxn<<2],to[maxn<<2],pos[maxn];  // fr[p] 表示跳出 [l,r] 的最小起点，to[p] 表示跳到的位置（即 max[l,r]）
    inline void pu(int p){
        to[p]=max(to[ls],to[rs]);
        fr[p]=to[ls]>=fr[rs]?fr[ls]:fr[rs];
    }
    void build(setpos){if(l==r)return fr[p]=(a[l]<=l?l+1:l),to[p]=a[l],pos[l]=p,void();setmid;build(lson);build(rson);pu(p);}
    inline void upd(int x){int p=pos[x];fr[p]=a[x]<=x?x+1:x;to[p]=a[x];while(p>>=1)pu(p);}
    int jump(setpos,int x,int now){
        if(l==r)    return max(to[p],now);
        setmid;
        if(l>x){
            if(now>=fr[p])    return max(now,to[p]);
            if(now>=fr[ls])   return jump(rson,x,max(now,to[ls]));
            return jump(lson,x,now);
        }
        if(x>mid)return jump(rson,x,now);
        int tp=jump(lson,x,now);
        if(tp<=mid) return tp;
        return jump(rson,x,tp);
    }
}
using namespace SegmentTree;
int main(){
    freopen("ds.in","r",stdin);freopen("ds.out","w",stdout);
    read();n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    build(all);
    int lstans=0;
    while(q--){
        int op=read(),p=read()^lstans,v;
        if(op==1){
            v=read()^lstans;
            a[p]=v;upd(p);
        }
        else{
            // for(int i=1;i<=n;i++)   printf("%d ",a[i]);
            // printf("\nquery %d\n",p);
            print(lstans=jump(all,p,p),'\n');
        }
    }
    flush();
}