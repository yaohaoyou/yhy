#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define LL __uint128_t
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
char O[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(LL x){if(!x)return putc(48),void();int len=0;while(x)cc[len++]=O[x%16],x/=16;while(len--)putc(cc[len]);}
    inline void print(LL x,char ch){print(x);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
const int maxn=3e5+10,w=128,lgN=19;
bool mem1;
int n,q;
LL a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    LL tr[maxn<<2][lgN],tag[maxn<<2];
    int len[maxn<<2];bool bk[maxn<<2];
    inline void pu(int p){
        bk[p]=bk[ls]|bk[rs];
        if(!bk[p])  return len[p]=-1,void();
        LL k=0,tmp;
        len[p]=max(len[ls],len[rs]);
        for(int i=0;i<=len[p];i++){
            (i>len[ls])&&(tr[ls][i]=0);
            (i>len[rs])&&(tr[rs][i]=0);
            tmp=tr[ls][i]^tr[rs][i];
            tr[p][i]=k^tmp;
            k=(k&tmp)|(tr[ls][i]&tr[rs][i]);
        }
        if(k)   tr[p][++len[p]]=k;
    }
    void build(setpos){tag[p]=-1;if(l==r){tr[p][0]=a[l];if(!a[l])len[p]=-1,bk[p]=false;else bk[p]=true;return;}setmid;build(lson);build(rson);pu(p);}
    inline void pt(int p,LL s){
        if(!bk[p])  return;
        tag[p]&=s;bk[p]=false;
        for(int i=0;i<=len[p];i++)if(tr[p][i])tr[p][i]&=s,bk[p]|=tr[p][i];
        if(!bk[p])len[p]=-1;
        else{while(!tr[p][len[p]])len[p]--;}
    }
    inline void pd(int p){if(~tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=-1;}}
    void upd(setpos,int pl,int pr,LL s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    void div(setpos,int pl,int pr,LL s){
        if(l==r){
            a[l]=tr[p][0]/s;if(!a[l])len[p]=-1,bk[p]=false;else bk[p]=true;
            tr[p][0]=a[l];return;
        }
        pd(p);setmid;if(pl<=mid&&bk[ls])div(lson,pl,pr,s);if(pr>mid&&bk[rs])div(rson,pl,pr,s);pu(p);
    }
    LL query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr){
            LL res=0;
            for(int i=0;i<=len[p];i++)if(tr[p][i])res+=tr[p][i]*(LL(1)<<i);
            return res;
        }
        pd(p);setmid;
        LL res=0;if(pl<=mid&&bk[ls])res=query(lson,pl,pr);if(pr>mid&&bk[rs])res+=query(rson,pl,pr);return res;
    }
}
using namespace SegmentTree;
bool mem2;
inline LL readLL() {
    LL res = 0;
    char c=getc();
    while(!isalnum(c))  c=getc();
    while(isalnum(c)){
        res = res << 4 | (c <= '9' ? c - '0' : c - 'a' + 10);
        c=getc();
    }
    return res;
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=readLL();
    build(all);
    while(q--){
        int op=read(),l=read(),r=read();LL v;
        if(op<=2)v=readLL();
        if(op==1){
            if(v^1)div(all,l,r,v);
        }
        else if(op==2)  upd(all,l,r,v);
        else    print(query(all,l,r),'\n');
    }
    flush();
}