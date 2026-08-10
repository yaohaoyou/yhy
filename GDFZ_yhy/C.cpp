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
const int maxn=2e5+10;
int n,q;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mx[maxn<<3];
    multiset<int> tr[maxn<<3];
    inline void pu(int p){mx[p]=max({mx[ls],mx[rs],tr[p].empty()?-1:*prev(tr[p].end())});}
    void ins(setpos,int pl,int pr,int k){if(l>=pl&&r<=pr)return tr[p].ep(k),mx[p]=max(mx[p],k),void();setmid;if(pl<=mid)ins(lson,pl,pr,k);if(pr>mid)ins(rson,pl,pr,k);pu(p);}
    int query(setpos,int pl,int pr){int res=tr[p].empty()?-1:*prev(tr[p].end());if(l>=pl&&r<=pr)return max(mx[p],res);setmid;if(pl<=mid)res=max(res,query(lson,pl,pr));if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
    void era(setpos,int pl,int pr,int k){
        if(mx[p]<k&&(tr[p].empty()||*prev(tr[p].end())<k))  return;
        setmid;
        if(l>=pl&&r<=pr){
            if(!tr[p].empty()&&*prev(tr[p].end())==k){
                tr[p].erase(prev(tr[p].end()));
                if(l==r) mx[p]=tr[p].empty()?-1:*prev(tr[p].end());
                else pu(p);
                return;
            }
            era(lson,pl,pr,k);era(rson,pl,pr,k);pu(p);
            return;
        }
        if(!tr[p].empty()&&*prev(tr[p].end())==k){
            tr[p].erase(prev(tr[p].end()));
            tr[ls].ep(k);tr[rs].ep(k);pu(ls);pu(rs);
        }
        if(pl<=mid)era(lson,pl,pr,k);if(pr>mid)era(rson,pl,pr,k);pu(p);
    }
}
using namespace SegmentTree;
int main(){
    freopen("memory.in","r",stdin);freopen("memory.out","w",stdout);
    scanf("%d%d",&n,&q);
    mems(mx,-1);
    while(q--){
        int op,l,r,k;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1){scanf("%d",&k);ins(all,l,r,k);}
        else if(op==2){k=query(all,l,r);if(~k)era(all,l,r,k);}
        else    printf("%d\n",query(all,l,r));
    }
}