#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define pil pair<int,ll>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=3e5+10;
const ll inf=1e18;
int n,q;
int w[maxn],h[maxn];
stack<int> stk;
vector<pil> v[maxn];
vector<pii> Q[maxn];
ll ans[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setpos int p,int l,int r
    #define setmid int mid=(l+r)>>1
    ll tr[maxn<<2];
    inline void pushup(int p){tr[p]=min(tr[ls],tr[rs]);}
    ll query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return tr[p];
        setmid;ll res=inf;
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res=min(res,query(rson,pl,pr));
        return res;
    }
    void update(setpos,int x,ll s){
        if(l==r)    return tr[p]=min(tr[p],s),void();
        setmid;
        if(x<=mid)  update(lson,x,s);
        else    update(rson,x,s);
        pushup(p);
    }
}
using namespace SegmentTree;
inline ll calc(int x,int y){return 1ll*(w[y]-w[x])*(h[y]+h[x]);}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d",&w[i],&h[i]);
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&h[stk.top()]>h[i])  stk.pop();
        if(!stk.empty()){int l=stk.top();v[l].eb(i,calc(l,i));}
        stk.push(i);
    }
    while(!stk.empty())stk.pop();
    for(int i=n;i;i--){
        while(!stk.empty()&&h[stk.top()]>h[i])  stk.pop();
        if(!stk.empty()){int r=stk.top();v[i].eb(r,calc(i,r));}
        stk.push(i);
    }
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[l].eb(r,i);}
    mems(tr,0x3f);
    for(int l=n;l;l--){
        for(auto [r,v]:v[l])    update(all,r,v);
        for(auto [r,id]:Q[l])   ans[id]=query(all,l,r);
    }
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}