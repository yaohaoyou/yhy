#include<cstdio>
#include<algorithm>
#define db double
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
const int maxn=1e5+10,n=39989,V=4e4+10,Y=1e9;
const db eps=1e-10;
int q,lstans;
struct line{db k,b;void init(int x0,int y0,int x1,int y1){if(x0==x1){k=0;b=max(y0,y1);}else{k=1.0*(y1-y0)/(x1-x0);b=y0-k*x0;}}}a[maxn];
inline int cmp(line x,line y,int point){db xx=x.k*point+x.b,yy=y.k*point+y.b;return abs(xx-yy)<eps?0:xx<yy?-1:1;}
inline bool cmp(int x,int y,int p){int rt=cmp(a[x],a[y],p);return rt?rt<0:x>y;}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define pos p,l,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[V<<2];
    void upd(setpos,int u){
        setmid,&v=tr[p];
        if(!cmp(u,v,mid)) swap(u,v);
        if(!cmp(u,v,l))   upd(lson,u);
        if(!cmp(u,v,r))   upd(rson,u);
    }
    void update(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return upd(pos,s);setmid;if(pl<=mid)update(lson,pl,pr,s);if(pr>mid)update(rson,pl,pr,s);}
    inline int query(int x){int p=1,l=1,r=n,ret=0;while(l^r){if(!cmp(tr[p],ret,x))ret=tr[p];setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}if(!cmp(tr[p],ret,x))ret=tr[p];return ret;}
}
using namespace SegmentTree;
int main(){
    scanf("%d",&q);
    int c=0;
    while(q--){
        int op,l,r,y0,y1;
        scanf("%d",&op);
        if(!op){
            scanf("%d",&l);
            l=(l+lstans-1)%n+1;
            printf("%d\n",lstans=query(l));
        }
        else{
            c++;
            scanf("%d%d%d%d",&l,&y0,&r,&y1);
            l=(l+lstans-1)%n+1;r=(r+lstans-1)%n+1;y0=(y0+lstans-1)%Y+1;y1=(y1+lstans-1)%Y+1;
            if(l>r)swap(l,r),swap(y0,y1);
            a[c].init(l,y0,r,y1);
            update(all,l,r,c);
        }
    }
}