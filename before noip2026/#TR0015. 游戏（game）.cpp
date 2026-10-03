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
const int maxn=1e5+10;
int n,q;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii tr[maxn<<2][2];
    bool tag[maxn<<2];
    inline void pu(int p){
        tr[p][0].fi=min(tr[ls][0].fi,tr[rs][0].fi);
        tr[p][0].se=max(tr[ls][0].se,tr[rs][0].se);
        tr[p][1].fi=min(tr[ls][1].fi,tr[rs][1].fi);
        tr[p][1].se=max(tr[ls][1].se,tr[rs][1].se);
    }
    inline void pt(int p){tag[p]^=1;swap(tr[p][0],tr[p][1]);}
    inline void pd(int p){if(tag[p])pt(ls),pt(rs),tag[p]=0;}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    void build(setpos){if(l==r)return tr[p][a[l]]=pii(l,l),tr[p][!a[l]]=pii(1e9,0),void();setmid;build(lson);build(rson);pu(p);}
    pii query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p][1];pd(p);setmid;pii res=pii(1e9,0);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid){pii t=query(rson,pl,pr);return pii(min(t.fi,res.fi),max(t.se,res.se));}return res;}
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    while(q--){
        int op,x,y;scanf("%d%d",&op,&x);
        if(op==1){
            scanf("%d",&y);
            upd(all,x,y);
        }
        else{
            int res=0;
            while(x--){
                int l,r;scanf("%d%d",&l,&r);
                pii t=query(all,l,r);
                if(t.fi<=n||t.se)   res^=r-l+1-2*min(t.fi-l,r-t.se);
            }
            puts(res?"Yes":"No");
        }
    }
}