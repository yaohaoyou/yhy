#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
const int maxn=1e6+10,MOD=1e9+7,mod=1e9+6,B=60;
int n,q,typ;
int a[maxn],P[maxn];
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
    inline int qpow(int x,ll y,int p=mod){int res=1;while(y){if(y&1)res=1ull*res*x%p;x=1ull*x*x%p;y>>=1;}return res;}
}
using namespace FastMod;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=imadd(tr[ls],tr[rs]);}
    inline void pt(int p,int s){mmul(tr[p],s);mmul(tag[p],s);}
    inline void pd(int p){if(tag[p]^1)pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=1;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)madd(res,query(rson,pl,pr));return res;}
    void build(setpos){tr[p]=tag[p]=1;if(l==r)return tr[p]=P[l],void();setmid;build(lson);build(rson);pu(p);}
}
using namespace SegmentTree;
__gnu_pbds::gp_hash_table<int,int> mp;
int main(){
    n=read();q=read();typ=read();
    for(int i=1;i<=n;i++)   a[i]=read()+1;
    {
        int pq=qpow(5,B,MOD),x=1;
        for(int i=0;i*B<MOD;i++){x=1ull*x*pq%MOD,mp[x]=i;}
        for(int i=1;i<=n;i++){
            int x=a[i];
            for(int j=0;j<B;j++){
                if(mp.find(x)!=mp.end()){P[i]=mp[x]*B+(B-j);break;}
                x=5ull*x%MOD;
            }
        }
        build(all);
    }
    int out=0;
    while(q--){
        int op=read(),l=read(),r=read(),k;
        if(op==1)   upd(all,l,r,qpow(2,read()));
        else{
            int ans=imdel(qpow(5,query(all,l,r),MOD),1);
            if(!typ)  printf("%d\n",ans);
            else out^=ans;
        }
    }
    if(typ)    printf("%d\n",out);
}