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
const int maxn=1e6+10;
int n;
int a[maxn],R[maxn],nx[maxn];
vector<int> vl[maxn];
vector<pii> vr[maxn];
int mn[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
stack<int> stk;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){gmx(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){fill(tr+1,tr+n+1,0);}
}T;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){tr[p]=s;setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;}
    int query(setpos,int pl,int pr){if(!tr[p])return 0;if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmx(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
void matt(int _cases){
    T.clear();fill(tr+1,tr+(n<<2)+1,0);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    stack<int>().swap(stk);
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]>=a[i])  stk.pop();
        R[i]=stk.empty()?0:stk.top();
        if(R[i])    vl[R[i]].eb(i);
        stk.ep(i);
    }
    stack<int>().swap(stk);
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]<=a[i]) stk.pop();
        nx[i]=stk.empty()?n+1:stk.top();
        stk.ep(i);
    }
    stack<int>().swap(stk);
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]<=a[i]) stk.pop();
        if(a[i]<a[nx[i]]-1){
            int k=query(all,a[i]+1,a[nx[i]]-1);
            if(k)   vr[k].eb(i,nx[i]);
        }
        stk.ep(i);
        upd(a[i],i);
    }
    fill(mn+1,mn+n+1,n+1);
    for(int i=1;i<=n;i++){
        for(auto [j,k]:vr[i]){
            int x=T.que(a[j]-1);
            // printf("%d %d %d\n",i,j,k);
            if(x)   gmn(mn[x],k);
        }
        for(int j:vl[i])   T.add(a[j],j);
        vl[i].clear();vr[i].clear();
    }
    int now=n+1;ll ans=0;
    for(int i=n;i;i--){
        gmn(now,mn[i]);
        if(now<=n)   ans+=n-now+1;
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}