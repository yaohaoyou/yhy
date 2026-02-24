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
const int maxn=5e5+10;
int n,q;
int a[maxn],L[maxn],R[maxn];
stack<int> stk;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mx[maxn<<2];
    ll sum[maxn<<2],mul[maxn<<2];
    inline void pu(int p){mx[p]=max(mx[ls],mx[rs]);}
    void build(setpos){mx[p]=sum[p]=mul[p]=0;if(l==r)return mx[p]=a[l],void();setmid;build(lson);build(rson);pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mx[p];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmx(res,query(rson,pl,pr));return res;}
    int binaryL(setpos,int pl,int x){
        if(mx[p]<x)return 0;
        if(l==r)return l;
        setmid;
        if(l>=pl) return mx[ls]>=x?binaryL(lson,pl,x):binaryL(rson,pl,x);
        if(pl<=mid){int res=binaryL(lson,pl,x);if(res)return res;}
        return binaryL(rson,pl,x);
    }
    int binaryR(setpos,int pr,int x){
        if(mx[p]<x)return 0;
        if(l==r)return l;
        setmid;
        if(r<=pr) return mx[rs]>=x?binaryR(rson,pr,x):binaryR(lson,pr,x);
        if(pr>mid){int res=binaryR(rson,pr,x);if(res)return res;}
        return binaryR(lson,pr,x);
    }
    void upd(setpos,int pl,int pr,ll x,ll y){if(l>=pl&&r<=pr)return sum[p]+=x,mul[p]+=y,void();setmid;if(pl<=mid)upd(lson,pl,pr,x,y);if(pr>mid)upd(rson,pl,pr,x,y);}
    inline ll query(int x){
        int p=1,l=1,r=n;ll su=0,mu=0;
        while(l^r){
            su+=sum[p];mu+=mul[p];
            setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        su+=sum[p];mu+=mul[p];
        return su+mu*x;
    }
    inline void upd(int x){int p=1,l=1,r=n;while(l^r){gmx(mx[p],a[x]);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}gmx(mx[p],a[x]);}
}
using namespace SegmentTree;
void solve(){
    stack<int>().swap(stk);
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]<=a[i]) stk.pop();
        L[i]=stk.empty()?i:i-stk.top();
        stk.ep(i);
    }
    stack<int>().swap(stk);
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]<a[i])  stk.pop();
        R[i]=stk.empty()?n-i+1:stk.top()-i;
        stk.ep(i);
    }
    build(all);
    for(int i=1;i<=n;i++){
        int l=min(L[i],R[i]),r=max(L[i],R[i]);
        if(l>1)   upd(all,1,l-1,0,a[i]);
        if(max(1,l)<=r) upd(all,max(1,l),r,1ll*l*a[i],0);
        if(r+1<=l+r) upd(all,r+1,l+r,1ll*a[i]*(l+r),-a[i]);
    }
}
int main(){
    freopen("ds.in","r",stdin);freopen("ds.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    solve();
    while(q--){
        char op[5];scanf("%s",op);
        int k;scanf("%d",&k);
        if(op[0]=='+'){
            a[k]++;upd(k);
            int pr=k>1?binaryR(all,k-1,a[k]):0,nx=k<n?binaryL(all,k+1,a[k]):n+1;
            if(!nx)nx=n+1;
            int l=min(k-pr,nx-k),r=max(k-pr,nx-k);
            if(l>1)   upd(all,1,l-1,0,1);
            if(max(1,l)<=r) upd(all,max(1,l),r,l,0);
            if(r+1<=l+r) upd(all,r+1,l+r,(l+r),-1);
        }
        else    printf("%lld\n",query(k));
    }
}