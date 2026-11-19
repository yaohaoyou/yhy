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
const int maxn=5e5+10,inf=1e9;
bool mem1;
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
    struct tree{
        int mn,w,l,r,w0,l0,r0,L;
        tree operator+(tree y){
            tree res={min(mn,y.mn),max(w,y.w),l,y.r};
            res.L=L?L:y.L;
            if(!l)res.l=y.l;if(!y.r)res.r=r;
            if(r&&y.L){
                gmx(res.w,y.L-r);
                if(res.r==r)res.r=0;
            }
            int W0=w0,L0=l0,R0=r0;
            if(mn>res.mn)   W0=w,L0=l,R0=r;
            if(y.mn>res.mn) y.w0=y.w,y.l0=y.l,y.r0=y.r;
            res.l0=L0?L0:y.l0;res.r0=y.r0?y.r0:R0;
            res.w0=max(W0,y.w0);
            if(R0&&y.L){
                gmx(res.w0,y.L-R0);
                if(res.r0==R0)res.r0=0;
            }
            return res;
        }
        void swp(){swap(w,w0);swap(l,l0);swap(r,r0);}
    }tr[maxn<<2];
    int tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,int s){
        tr[p].mn+=s;tag[p]+=s;
        if(!tr[p].mn||tr[p].mn==s)   tr[p].swp();
    }
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){tr[p]={0,0,0,0,0,0,0,0};tag[p]=0;if(l==r)return;setmid;build(lson);build(rson);pu(p);}
    // int Qmn(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mn[p];setmid,res=inf;if(pl<=mid)res=Qmn(lson,pl,pr);if(pr>mid)gmn(res,Qmn(rson,pl,pr));return res;}
    // int Qmx(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mx[p];setmid,res=0;if(pl<=mid)res=Qmx(lson,pl,pr);if(pr>mid)gmx(res,Qmx(rson,pl,pr));return res;}
    void U(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)U(lson,pl,pr,s);if(pr>mid)U(rson,pl,pr,s);pu(p);}
    inline void upd(int x){
        int p=1,l=1,r=n;
        while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        if(b[x]){
            if(tr[p].mn)    tr[p]={tr[p].mn,0,x,x,0,0,0,x};
            else    tr[p]={tr[p].mn,0,0,0,0,x,x,x};
        }
        else    tr[p]={tr[p].mn,0,0,0,0,0,0,0};
        while(p>>=1)pu(p);
    }
    void prt(setpos){printf("[%d,%d] : %d %d %d\n",l,r,tr[p].l,tr[p].r,tr[p].mn);if(l==r)return;setmid;pd(p);prt(lson);prt(rson);}
}
using namespace SegmentTree;
inline void ins(int x){
    b[a[x]]++;upd(a[x]);
    if(x>1&&a[x-1]>a[x]){
        // for(int i=a[x];i<a[x-1];i++)    d[i]++;
        U(all,a[x],a[x-1]-1,1);
    }
}
inline void era(int x){
    if(x>1&&a[x-1]>a[x]){
        // for(int i=a[x];i<a[x-1];i++)    d[i]--;
        U(all,a[x],a[x-1]-1,-1);
    }
    b[a[x]]--;upd(a[x]);
}
bool mem2;
void matt(int _cases){
    fll(b,0,n);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    for(int i=1;i<=n;i++)   ins(i);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        era(x);if(x<n)era(x+1);a[x]=y;ins(x);if(x<n)ins(x+1);
        printf("%d\n",tr[1].w);
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}