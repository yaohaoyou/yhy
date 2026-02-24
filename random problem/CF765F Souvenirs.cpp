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
const int maxn=1e5+10,maxq=3e5+10,V=1e9;
int n,q;
int a[maxn],ans[maxq];
vector<pii> Q[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x){tr[x]=min(tr[x],s);x^=lowbit(x);}}
    inline void clear(){mems(tr,0x3f);}
    inline int que(int x){int res=V+10;while(x<=n){res=min(res,tr[x]);x+=lowbit(x);}return res;}
}T;
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all rt,0,V
    #define setpos int p,int l,int r
    #define setmid int mid=(l+r)>>1
    int rt,tot;
    int tr[maxn<<5],lc[maxn<<5],rc[maxn<<5];
    void update(int &p,int l,int r,int x,int s){
        if(!p)  p=++tot;
        tr[p]=max(tr[p],s);
        // printf("upd %d %d %d : %d\n",p,l,r,tr[p]);
        if(l==r)    return;
        setmid;
        (x<=mid)?update(lson,x,s):update(rson,x,s);
    }
    int query(setpos,int pl,int pr){
        // debug("%d %d %d : %d\n",p,l,r,tr[p]);
        // if(!p)  return 0;
        if(l>=pl&&r<=pr)    return tr[p];
        setmid,res=0;
        if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));
        return res;
    }
}
using namespace SegmentTree;
void matt(){
    for(int i=1;i<=n;i++){
        int pos=query(all,a[i],V);
        // debug("pos[%d] = %d\n",i,pos);
        // debug("i = %d\n",i);
        while(pos){
            // debug("pos = %d %d\n",pos,a[pos]-a[i]);
            T.add(pos,a[pos]-a[i]);
            pos=query(all,a[i],(a[pos]+a[i]-1)/2);
        }
        for(auto [r,id]:Q[i]){
            // debug("query %d = %d\n",r,T.que(r));
            ans[id]=min(ans[id],T.que(r));
        }
        update(all,a[i],i);
    }
}
int main(){
    mems(ans,0x3f);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int l,r;scanf("%d%d",&l,&r);
        Q[r].eb(l,i);
    }
    T.clear();
    matt();
    for(int i=1;i<=n;i++)   a[i]=V-a[i];
    T.clear();mems(tr,0);mems(lc,0);mems(rc,0);rt=tot=0;
    matt();
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}