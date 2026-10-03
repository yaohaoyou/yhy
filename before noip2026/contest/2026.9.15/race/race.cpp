#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pil pair<int,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5e5+10;
const ll INF=1e18;
int n,K,ans=1;
ll a[maxn],b[maxn],c[maxn],d[maxn];
pii tg[maxn];
struct Stack{
    int st[maxn],len;
    inline int& operator[](int x){return st[x];}
    inline void ep(int x){st[++len]=x;}
    inline void pop(){len--;}
    inline int top(){return st[len];}
    inline int size(){return len;}
    inline bool empty(){return !len;}
    inline void clear(){len=0;}
}stk;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],mx[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    void build(setpos){tr[p]=-INF;if(l==r)return mx[p]=d[l],void();setmid;build(lson);build(rson);pu(p);mx[p]=max(mx[ls],mx[rs]);}
    inline void pt(int p,ll s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void upd(setpos,int pl,int pr,ll s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline void upd(int x,ll s){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
    int binary(setpos,int pr,ll s){
        if(mx[p]+K<s)   return 0;
        if(l==r)    return l;
        pd(p);setmid;
        if(r<=pr){
            if(mx[rs]+K>=max(s,tr[ls])) return binary(rson,pr,max(s,tr[ls]));
            return binary(lson,pr,s);
        }
        if(pr<=mid) return binary(lson,pr,s);
        int x=binary(rson,pr,max(tr[ls],s));if(x)return x;
        return binary(lson,pr,s);
    }
    void print(setpos){if(l==r)return printf("%lld ",tr[p]),void();setmid;pd(p);print(lson);print(rson);pu(p);}
}
using namespace SegmentTree;
bool mem2;
int main(){
    freopen("race.in","r",stdin);freopen("race.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024); 
    scanf("%d%d",&n,&K);
    for(int i=1;i<n;i++)   scanf("%lld",&a[i]),a[i]+=a[i-1];
    a[n+1]=1e18;
    for(int i=1;i<=n;i++)   scanf("%lld",&b[i]),b[i]+=b[i-1];
    for(int i=1;i<=n;i++)   c[i]=a[i-1]-b[i-1],d[i]=b[i]-a[i-1];
    build(all);
    stk.ep(n+1);c[n+1]=-INF;
    for(int i=n;i;i--){
        upd(i,d[i]);
        while(stk.size()>1&&c[stk.top()]<=c[i]){int x=stk.top();if(tg[x].se)upd(all,tg[x].fi,n,-tg[x].se);stk.pop();}
        if(stk.size()>1){
            int x=stk.top();tg[i]=pii(x-1,c[x]-c[i]);
            upd(all,x-1,n,tg[i].se);
        }
        stk.ep(i);
        int l=2,r=stk.size(),p=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(c[stk[mid]]-c[i]<=K) p=stk[mid-1]-1,r=mid-1;
            else l=mid+1;
        }
        gmx(ans,binary(all,p,-INF)-i+1);
    }
    printf("%d\n",ans);
}