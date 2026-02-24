//  P6242 【模板】线段树 3（区间最值操作、区间历史最值）
/*
1. 区间加
2. 区间取 min
3. 求区间和
4. 求区间 max
5. 求历史版本区间 max
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int maxn=5e5+10,inf=0x3f3f3f3f;
int n,q;
int a[maxn];
inline void getmax(int &x,int y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define s(p)    tr[p].s // 区间和
    #define mx(p)   tr[p].mx    // 区间最大值
    #define cnt(p)  tr[p].cnt   // 区间最大值个数
    #define se(p)   tr[p].se    // 区间次大值
    #define mxh(p)  tr[p].mxh   // 区间历史最大值
    #define mxt(p)  tr[p].mxtag // 区间最大值加法标记
    #define mxht(p) tr[p].mxhtag    // 区间最大值加法标记历史最大值
    #define set(p)  tr[p].setag // 区间非最大值加法标记
    #define seht(p) tr[p].sehtag    // 区间非最大值加法标记历史最大值
    struct tree{
        int s;
        int mx,cnt,se,mxh;
        int mxtag,mxhtag,setag,sehtag;
    }tr[maxn<<2];
    inline void pushup(int p){
        s(p)=s(ls)+s(rs);
        mx(p)=max(mx(ls),mx(rs));
        mxh(p)=max(mxh(ls),mxh(rs));
        if(mx(ls)==mx(rs)){cnt(p)=cnt(ls)+cnt(rs);se(p)=max(se(ls),se(rs));}
        else if(mx(ls)>mx(rs)){cnt(p)=cnt(ls);se(p)=max(se(ls),mx(rs));}
        else{cnt(p)=cnt(rs);se(p)=max(mx(ls),se(rs));}
    }
    inline void slv(int p,int l,int r,int mxk,int mxhk,int sek,int sehk){
        s(p)+=(mxk*cnt(p)+sek*(r-l+1-cnt(p)));
        getmax(mxh(p),mx(p)+mxhk);mx(p)+=mxk;
        if(se(p)!=-inf) se(p)+=sek;
        getmax(mxht(p),mxt(p)+mxhk);mxt(p)+=mxk;
        getmax(seht(p),set(p)+sehk);set(p)+=sek;
    }
    inline void pushdown(int p,int l,int r){
        if(!mxt(p)&&!mxht(p)&&!set(p)&&!seht(p)) return;
        int mid=(l+r)>>1,max1=max(mx(ls),mx(rs));
        if(max1==mx(ls)) slv(lson,mxt(p),mxht(p),set(p),seht(p));else slv(lson,set(p),seht(p),set(p),seht(p));
        if(max1==mx(rs)) slv(rson,mxt(p),mxht(p),set(p),seht(p));else slv(rson,set(p),seht(p),set(p),seht(p));
        mxt(p)=mxht(p)=set(p)=seht(p)=0;
    }
    void build(int p,int l,int r){
        if(l==r){
            s(p)=mx(p)=mxh(p)=a[l];
            cnt(p)=1;
            se(p)=-inf;
            return;
        }
        int mid=(l+r)>>1;
        build(lson);build(rson);
        pushup(p);
    }
    void updateadd(int p,int l,int r,int pl,int pr,int s){
        if(l>=pl&&r<=pr){
            s(p)+=(r-l+1)*s;
            getmax(mxh(p),mx(p)+=s);
            if(se(p)!=-inf) se(p)+=s;
            getmax(mxht(p),mxt(p)+=s);
            getmax(seht(p),set(p)+=s);
            return;
        }
        pushdown(p,l,r);
        int mid=(l+r)>>1;
        if(pl<=mid)   updateadd(lson,pl,pr,s);
        if(pr>mid)   updateadd(rson,pl,pr,s);
        pushup(p);
    }
    void updatemin(int p,int l,int r,int pl,int pr,int s){
        if(s>=mx(p))    return;
        if(l>=pl&&r<=pr&&se(p)<s){
            int del=mx(p)-s;
            s(p)-=cnt(p)*del;
            mxt(p)-=del;
            mx(p)=s;
            return;
        }
        pushdown(p,l,r);
        int mid=(l+r)>>1;
        if(pl<=mid)   updatemin(lson,pl,pr,s);
        if(pr>mid)  updatemin(rson,pl,pr,s);
        pushup(p);
    }
    int queryS(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return s(p);
        pushdown(p,l,r);
        int mid=(l+r)>>1,res=0;
        if(pl<=mid)   res=queryS(lson,pl,pr);
        if(pr>mid)  res+=queryS(rson,pl,pr);
        pushup(p);
        return res;
    }
    int queryMX(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return mx(p);
        pushdown(p,l,r);
        int mid=(l+r)>>1,res=-inf;
        if(pl<=mid)   res=queryMX(lson,pl,pr);
        if(pr>mid)  res=max(res,queryMX(rson,pl,pr));
        pushup(p);
        return res;
    }
    int queryMXH(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return mxh(p);
        pushdown(p,l,r);
        int mid=(l+r)>>1,res=-inf;
        if(pl<=mid)   res=queryMXH(lson,pl,pr);
        if(pr>mid)  res=max(res,queryMXH(rson,pl,pr));
        pushup(p);
        return res;
    }
}
using namespace SegmentTree;
signed main(){
    scanf("%lld%lld",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,1,n);
    while(q--){
        int opt,l,r,k;
        scanf("%lld%lld%lld",&opt,&l,&r);
        if(opt==1){
            scanf("%lld",&k);
            updateadd(1,1,n,l,r,k);
        }
        else if(opt==2){
            scanf("%lld",&k);
            updatemin(1,1,n,l,r,k);
        }
        else if(opt==3) printf("%lld\n",queryS(1,1,n,l,r));
        else if(opt==4) printf("%lld\n",queryMX(1,1,n,l,r));
        else    printf("%lld\n",queryMXH(1,1,n,l,r));
    }
}