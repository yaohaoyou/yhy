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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3e5+10;
int n,q;
pii a[maxn];
struct tree{
    int l,r,x;ll k;  // 若在 t\in[l,r] 时刻出发，在 t+x 时刻到达，花费 k 的代价
    tree operator+(tree y){
        int pl=max(l,y.l-x),pr=min(r,y.r-x);
        if(pl<=pr)  return {pl,pr,x+y.x,k+y.k};
        if(l>pr)    return {l,l,x+y.x-(l-pr),k+y.k+(l-pr)};
        return {r,r,x+y.x+(pl-r),k+y.k};
    }
};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n-1
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    tree tr[maxn<<2][2];
    int pos[maxn];
    inline void pu(int p){tr[p][0]=tr[ls][0]+tr[rs][0];tr[p][1]=tr[rs][1]+tr[ls][1];}
    void build(setpos){if(l==r)return pos[l]=p,void();setmid;build(lson);build(rson);}
    inline void upd(int x){
        int p=pos[x];
        tr[p][0]=tr[p][1]={a[x].fi,a[x].se,1,0};
        while(p>>=1)pu(p);
    }
    tree Q0(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p][0];setmid;return pr<=mid?Q0(lson,pl,pr):pl>mid?Q0(rson,pl,pr):Q0(lson,pl,pr)+Q0(rson,pl,pr);}
    tree Q1(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p][1];setmid;return pr<=mid?Q1(lson,pl,pr):pl>mid?Q1(rson,pl,pr):Q1(rson,pl,pr)+Q1(lson,pl,pr);}
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),a[i].se--;
    if(n^1)build(all);for(int i=1;i<n;i++)upd(i);
    while(q--){
        int op,x,y,l,r;scanf("%d%d",&op,&x);
        if(op==1){
            scanf("%d%d",&a[x].fi,&a[x].se);a[x].se--;
            upd(x);
        }
        else{
            scanf("%d%d%d",&l,&y,&r);
            if(x==y){printf("%d\n",max(0,l-r));continue;}
            if(x<y){
                tree t=Q0(all,x,y-1);
                ll ans=t.k;if(l>t.r)ans+=l-t.r,l=t.r;gmx(l,t.l);
                printf("%lld\n",ans+max(0,l+t.x-r));
            }
            else{
                tree t=Q1(all,y,x-1);
                ll ans=t.k;if(l>t.r)ans+=l-t.r,l=t.r;gmx(l,t.l);
                printf("%lld\n",ans+max(0,l+t.x-r));
            }
        }
    }
}