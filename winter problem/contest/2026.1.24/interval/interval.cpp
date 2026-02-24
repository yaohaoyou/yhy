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
const int maxn=2e5+10;
int n;
int a[maxn];
struct seg{
    ll res,sum;int len;
    inline bool operator==(const seg&x)const{return sum*x.len==x.sum*len;}
    inline bool operator<(const seg &x)const{return sum*x.len<x.sum*len;}
    inline bool operator>(const seg &x)const{return sum*x.len>x.sum*len;}
    inline bool operator<=(const seg &x)const{return sum*x.len<=x.sum*len;}
    inline bool operator>=(const seg &x)const{return sum*x.len>=x.sum*len;}
    inline seg operator+(seg x){return {res+x.res+sum*x.len,sum+x.sum,len+x.len};}
    inline seg operator-(seg x){seg ret={res-x.res,sum-x.sum,len-x.len};ret.res-=x.sum*ret.len;return ret;}
    inline void operator-=(seg x){*this=*this-x;}
    inline void operator+=(seg x){*this=*this+x;}
};
stack<seg> stk,s1;
vector<seg> v[maxn];
seg b[maxn<<1];int m;
seg ins[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void discrete(){
    sort(b+1,b+m+1);
    m=unique(b+1,b+m+1)-b-1;
}
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    seg tr[maxn<<3];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void upd(int x,seg s,bool o){int p=1,l=1,r=m;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}o?tr[p]+=s:tr[p]-=s;while(p>>=1)pu(p);}
}
using namespace SegmentTree;
inline void upd(seg s,bool o){upd(lower_bound(b+1,b+m+1,s)-b,s,o);}
int main(){
    freopen("interval.in","r",stdin);freopen("interval.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=n;i;i--){
        seg now={a[i],a[i],1};
        while(!s1.empty()&&now>=s1.top()) v[i].eb(s1.top()),now+=s1.top(),s1.pop();
        ins[i]=now;
        s1.ep(now);b[++m]=now;
    }
    stack<seg>().swap(stk);
    for(int i=1;i<=n;i++){
        seg now={a[i],a[i],1};
        while(!stk.empty()&&now>=stk.top()) now+=stk.top(),stk.pop();
        stk.ep(now);b[++m]=now;
    }
    discrete();
    while(!s1.empty())  upd(s1.top(),1),s1.pop();
    stack<seg>().swap(stk);
    for(int i=1;i<=n;i++){
        upd(ins[i],0);for(seg j:v[i])upd(j,1);
        print(tr[1].res+1ll*(n-1)*a[i]);putc(' ');
        seg now={a[i],a[i],1};

        while(!stk.empty()&&now>=stk.top()) now+=stk.top(),upd(stk.top(),0),stk.pop();
        stk.ep(now);upd(now,1);
    }
    flush();
}