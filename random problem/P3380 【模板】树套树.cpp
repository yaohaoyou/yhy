#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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
using namespace __gnu_pbds;
const int maxn=5e4+10,INF=2147483647;
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
    tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> tr[maxn<<2];
    void build(setpos){
        for(int i=l;i<=r;i++)   tr[p].insert(pii(a[i],i));
        if(l==r)    return;
        setmid;build(lson);build(rson);
    }
    int query_rank(setpos,int pl,int pr,int s){
        if(l>=pl&&r<=pr)    return tr[p].order_of_key(pii(s,0));
        setmid,res=0;
        if(pl<=mid) res=query_rank(lson,pl,pr,s);
        if(pr>mid)  res+=query_rank(rson,pl,pr,s);
        return res;
    }
    void update(setpos,int x,int s){
        tr[p].erase(pii(a[x],x));tr[p].insert(pii(s,x));
        if(l==r)    return;
        setmid;
        (x<=mid)?update(lson,x,s):update(rson,x,s);
    }
    int find_prev(setpos,int pl,int pr,int s){
        if(l>=pl&&r<=pr){auto it=tr[p].lower_bound(pii(s,0));return it==tr[p].begin()?-INF:prev(it)->fi;}
        setmid,res=-INF;
        if(pl<=mid) res=find_prev(lson,pl,pr,s);
        if(pr>mid)  res=max(res,find_prev(rson,pl,pr,s));
        return res;
    }
    int find_next(setpos,int pl,int pr,int s){
        if(l>=pl&&r<=pr){auto it=tr[p].upper_bound(pii(s,n+1));return it==tr[p].end()?INF:it->fi;}
        setmid,res=INF;
        if(pl<=mid) res=find_next(lson,pl,pr,s);
        if(pr>mid)  res=min(res,find_next(rson,pl,pr,s));
        return res;
    }
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(all);
    while(q--){
        int op,l,r,k;
        scanf("%d%d%d",&op,&l,&r);
        if(op^3)    scanf("%d",&k);
        if(op==1)   printf("%d\n",query_rank(all,l,r,k)+1);
        else if(op==2){
            k--;
            int L=1,R=1e8,ans=0;
            while(L<=R){
                int mid=(L+R)>>1;
                if(query_rank(all,l,r,mid)<=k)  ans=mid,L=mid+1;
                else    R=mid-1;
            }
            printf("%d\n",ans);
        }
        else if(op==3)  update(all,l,r),a[l]=r;
        else if(op==4)  printf("%d\n",find_prev(all,l,r,k));
        else    printf("%d\n",find_next(all,l,r,k));
    }
}