#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define ui unsigned int
#define eb emplace_back
#define ep emplace
#define puu pair<ui,ui>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define if(sth) if(__builtin_expect(sth,1))
using namespace std;
const int maxn=5e5+10,maxm=32;
int n,q,m;
ui M;
ui a[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ui x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
inline void gmx(ui &x,ui y){(x<y)&&(x=y);}
inline void gmn(ui &x,ui y){(x>y)&&(x=y);}
int len[maxn];
puu v[maxn][40];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ui sM,K;
    struct tree{
        ui fi,se;bool mk;
        inline void operator+=(const tree &y){
            if(fi>se)   return;
            if(y.fi>y.se)   return *this=y,void();
            if(!mk&&!y.mk)   gmx(fi,y.fi),gmn(se,y.se);
            else if(mk&&y.mk) gmn(fi,y.fi),gmx(se,y.se);
            else{
                if(mk){
                    if(y.fi<=fi)  se=min(y.se,fi),fi=y.fi;
                    else if(se<=y.se) fi=max(y.fi,se),se=y.se;
                    else    fi=1,se=0;
                    mk=false;
                }
                else{
                    if(fi<=y.fi)  gmn(se,y.fi);
                    else if(y.se<=se) gmx(fi,y.se);
                    else    fi=1,se=0;
                }
            }
            if(fi>se)    fi=1,se=0,mk=false;
        }
        inline tree operator+(tree y){tree res=*this;res+=y;return res;}
        inline void add(ui s){
            s&=sM;
            if(fi>se)   return;
            ui l=fi,r=se;
            if(s<=l){fi-=s;se-=s;}
            else if(s<=r){mk^=1;fi=r-s;se=K+l-s;}
            else{fi=K+l-s;se=K+r-s;}
            if(fi>se)   fi=1,se=0,mk=false;
        }
        inline tree addtr(ui s){tree res=*this;res.add(s);return res;}
    };
    tree tr[maxn<<2];
    ui tag[maxn<<2];
    // inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];tr[p].add(tag[p]);}
    void upd(setpos,int pl,int pr,ui s){if(l>=pl&&r<=pr)return tag[p]+=s,tr[p].add(s);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    tree res;
    void query(setpos,int pl,int pr,ui s,int id){if(l>=pl&&r<=pr)return v[id][++len[id]]=puu(p,s),void();s+=tag[p];setmid;if(pl<=mid)query(lson,pl,pr,s,id);if(pr>mid)query(rson,pl,pr,s,id);}
    void query(setpos,int pl,int pr,ui s){if(l>=pl&&r<=pr)return res+=tr[p].addtr(s),void();s+=tag[p];setmid;if(pl<=mid)query(lson,pl,pr,s);if(pr>mid)query(rson,pl,pr,s);}
    void build(setpos,ui L,ui R){tr[p].fi=tr[p].se=tr[p].mk=tag[p]=0;if(l==r)return tr[p]={L,R,false},tr[p].add(a[l]&sM),void();setmid;build(lson,L,R);build(rson,L,R);pu(p);}
}
using namespace SegmentTree;
struct ques{int op,l,r;ll k;}Q[maxn];
ui ans[maxn];
void solve1(int i){
    K=(1ll<<i+1);sM=K-1;
    build(all,1u<<i,(1ll<<i+1)-1);
    for(int _=1;_<=q;_++){
        int op=Q[_].op,l=Q[_].l,r=Q[_].r;ll k=Q[_].k;l++;
        if(!op) upd(all,l,r,k);
        else{
            res.fi=0;res.se=sM;res.mk=false;
            query(all,l,r,0,_);
            res=tr[v[_][1].fi].addtr(v[_][1].se);
            for(int j=2;j<=len[_];j++){
                if(res.fi>res.se)   break;
                res+=tr[v[_][j].fi].addtr(v[_][j].se);
            }
            // printf("%d %d %d\n",res.fi,res.se,res.mk);
            if(!res.mk&&res.fi<=res.se&&!res.fi) ans[_]|=(1u<<i);
            else if(res.mk&&res.fi<=res.se)    ans[_]|=(1u<<i);
        }
    }
}
void solve2(int i){
    K=(1ll<<i+1);sM=K-1;
    build(all,1u<<i,(1ll<<i+1)-1);
    for(int _=1;_<=q;_++){
        int op=Q[_].op,l=Q[_].l,r=Q[_].r;ll k=Q[_].k;l++;
        if(!op){if(k&sM)upd(all,l,r,k&sM);}
        else{
            // res.fi=0;res.se=sM;res.mk=false;
            // v[_].clear();query(all,l,r,_);
            res=tr[v[_][1].fi].addtr(v[_][1].se&sM);
            for(int j=2;j<=len[_];j++){
                if(res.fi>res.se)   break;
                res+=tr[v[_][j].fi].addtr(v[_][j].se&sM);
            }
            // printf("%d %d %d\n",res.fi,res.se,res.mk);
            if(!res.mk&&res.fi<=res.se&&!res.fi) ans[_]|=(1u<<i);
            else if(res.mk&&res.fi<=res.se)    ans[_]|=(1u<<i);
        }
    }
}
int main(){
    n=read();q=read();m=read();M=(1ll<<m)-1;
    for(int i=1;i<=n;i++)   a[i]=readll();
    for(int i=1;i<=q;i++){
        Q[i].op=read();Q[i].l=read();Q[i].r=read();
        if(!Q[i].op)    Q[i].k=readll();
    }
    solve1(m-1);
    for(int i=0;i<m-1;i++)  solve2(i);
    for(int i=1;i<=q;i++)if(Q[i].op)print(ans[i]),putc('\n');
    flush();
}