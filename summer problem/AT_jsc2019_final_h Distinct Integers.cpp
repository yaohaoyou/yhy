#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
int n,q;
int a[maxn];
set<int> st[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define pos p,l,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];ll sum[maxn<<2];
    vector<piii> path;
    ll query(setpos,int s){
        if(tr[p]<=s) return 1ll*s*(r-l+1);
        if(l==r)    return tr[p];
        setmid;
        if(tr[ls]<=s)   return query(lson,s)+query(rson,s);
        return query(lson,s)+sum[p]-sum[ls];
    }
    inline void pu(setpos){tr[p]=max(tr[ls],tr[rs]);setmid;sum[p]=sum[ls]+query(rson,tr[ls]);}
    void upd(setpos,int x,int s){if(l==r)return tr[p]=sum[p]=s,void();setmid;(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(pos);}
    inline void querypath(setpos,int pl,int pr){if(l>=pl&&r<=pr)return path.eb(p,pii(l,r)),void();setmid;if(pl<=mid)querypath(lson,pl,pr);if(pr>mid)querypath(rson,pl,pr);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   st[a[i]].ep(i);
    for(int i=1;i<=n;i++){
        auto it=st[a[i]].find(i);
        int pre=(it!=st[a[i]].begin())?*prev(it):0;
        upd(all,i,pre);
    }
    while(q--){
        int op,l,r;scanf("%d%d%d",&op,&l,&r);
        if(!op){
            l++;
            int pre=0;
            {
                auto it=st[a[l]].find(l);
                if(it!=st[a[l]].begin())    pre=*prev(it);
                if((++it)!=st[a[l]].end())  upd(all,*it,pre);
                st[a[l]].erase(l);
            }
            a[l]=r;
            {
                auto it=st[a[l]].ep(l).fi;
                if(it!=st[a[l]].begin())    pre=*prev(it);
                else    pre=0;
                if((++it)!=st[a[l]].end())  upd(all,*it,l);
                upd(all,l,pre);
            }
        }
        else{
            l++;
            path.clear();
            querypath(all,l,r);
            int mx=l-1;ll ans=1ll*(l+r)*(r-l+1)/2;
            for(piii x:path){
                int p=x.fi,pl=x.se.fi,pr=x.se.se;
                ans-=query(p,pl,pr,mx);
                mx=max(mx,tr[p]);
            }
            printf("%lld\n",ans);
        }
    }
}