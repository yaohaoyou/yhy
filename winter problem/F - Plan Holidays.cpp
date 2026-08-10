#include<bits/stdc++.h>
#define rep(i) for(int i:{0,1})
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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n,k;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{
        int len;
        ll a[2][2];
        inline ll* operator[](int x){return a[x];}
        inline tree operator+(tree y){
            tree res;res.len=len+y.len;
            if(len==1&&y.len==1){
                rep(i)rep(j)res[i][j]=a[i][i]+y[j][j];
                return res;
            }
            if(len==1){
                res[0][0]=a[0][0]+y[1][0];
                res[0][1]=a[0][0]+y[1][1];
                res[1][0]=a[1][1]+y[1][0];
                if(y.len>2) gmn(res[1][0],a[1][1]+y[0][0]);
                res[1][1]=min(a[1][1]+y[1][1],a[1][1]+y[0][1]);
                return res;
            }
            if(y.len==1){
                res[0][0]=a[0][1]+y[0][0];
                res[1][0]=a[1][1]+y[0][0];
                res[0][1]=a[0][1]+y[1][1];
                if(len>2)   gmn(res[0][1],a[0][0]+y[1][1]);
                res[1][1]=min(a[1][1]+y[1][1],a[1][0]+y[1][1]);
                return res;
            }
            rep(i)rep(j){
                res[i][j]=a[i][1]+y[1][j];
                if(i||len>2)    gmn(res[i][j],a[i][0]+y[1][j]);
                if(j||y.len>2)  gmn(res[i][j],a[i][1]+y[0][j]);
            }
            return res;
        }
        void build(int x){mems(a,0x3f);a[0][0]=0;a[1][1]=x;len=1;}
    };
    tree tr[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    void build(setpos){if(l==r)return tr[p].build(a[l]);setmid;build(lson);build(rson);pu(p);}
    tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;if(pr<=mid)return query(lson,pl,pr);if(pl>mid)return query(rson,pl,pr);return query(lson,pl,pr)+query(rson,pl,pr);}
}
using namespace SegmentTree;
void matt(int _cases){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    ll ans=1e18;
    for(int i=1;i+k-1<=n;i++){
        int r=i+k-1;
        gmn(ans,query(all,i,r)[1][1]);
        if(r<n)gmn(ans,query(all,i,r+1)[1][1]);
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}