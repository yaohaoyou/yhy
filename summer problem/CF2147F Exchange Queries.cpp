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
const int maxn=1e5+10;
int n,Q;
int p[maxn],q[maxn],ip[maxn],iq[maxn];
inline ll C2(int x){return 1ll*x*(x-1)/2;}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tag[maxn<<2];
    struct tree{
        int L,R,mn;ll s;
        tree operator+(tree y){if(mn<y.mn) return *this;if(mn>y.mn) return y;return {L,y.R,mn,s+y.s+C2(y.L-R-1)};}
    }tr[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,int s){tr[p].mn+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    void build(setpos){tag[p]=0;if(l==r)return tr[p]={l,l,0,0},void();setmid;build(lson);build(rson);pu(p);}
    int query(setpos,int x){if(l==r)return tr[p].mn;pd(p);setmid,ret=x<=mid?query(lson,x):query(rson,x);pu(p);return ret;}
}
using namespace SegmentTree;
inline void upd(int x,int s){int l=p[x],r=q[x];if(l>r)swap(l,r);upd(all,l,r,s);}
void matt(){
    scanf("%d%d",&n,&Q);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]),ip[p[i]]=i;
    for(int i=1;i<=n;i++)   scanf("%d",&q[i]),iq[q[i]]=i;
    build(all);
    for(int i=1;i<=n;i++)   upd(i,1);
    while(Q--){
        int op,i,j;scanf("%d%d%d",&op,&i,&j);
        if(op==1){
            upd(i,-1);upd(j,-1);
            swap(p[i],p[j]);
            upd(i,1);upd(j,1);
        }
        else{
            upd(i,-1);upd(j,-1);
            swap(q[i],q[j]);
            upd(i,1);upd(j,1);
        }
        int l=tr[1].L,r=tr[1].R;
        if(tr[1].mn^1)   l=0,r=0;
        printf("%lld\n",n+C2(n)+tr[1].s+C2(l)+C2(n-r));
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}