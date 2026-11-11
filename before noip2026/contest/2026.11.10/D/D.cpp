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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3e5+10;
int n,m;
int a[maxn],b[maxn],w[maxn],h[maxn],d[maxn];
int p[maxn],q[maxn],L[maxn],R[maxn];
int deg[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],pos[maxn];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    void build(setpos){if(l==r)return pos[l]=p,tr[p]=b[::p[l]],void();setmid;build(lson);build(rson);pu(p);}
    inline void upd(int x){int p=pos[x];tr[p]=b[::p[x]];while(p>>=1)pu(p);}
    int bry(setpos,int pl,int pr,int x){
        if(tr[p]>x) return 0;
        if(l==r)    return h[::p[l]];
        if(l>=pl&&r<=pr){
            setmid;
            if(tr[rs]<=x)   return bry(rson,pl,pr,x);
            return bry(lson,pl,pr,x);
        }
        setmid,t=0;
        if(pr>mid){t=bry(rson,pl,pr,x);if(t)return t;}
        if(pl<=mid)return bry(lson,pl,pr,x);
        return 0;
    }
}
using namespace SegmentTree;
multiset<ll> s[maxn],st;
void calc(int x,bool o){
    int mx=s[b[x]].empty()?0:*s[b[x]].rbegin();
    if(o)   s[b[x]].erase(s[b[x]].find(w[x]));
    if(!L[x])   w[x]=1;
    else    w[x]=bry(all,L[x],R[x],b[x])+1;
    s[b[x]].ep(w[x]);
    if(*s[b[x]].rbegin()^mx){
        st.erase(st.find(1ll*n*mx+b[x]));
        mx=*s[b[x]].rbegin();
        st.ep(1ll*n*mx+b[x]);
    }
}
bool mem2;
int main(){
    int q;
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]),deg[a[i]]++;
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    mems(h,0x3f);
    queue<int> que;
    for(int i=1;i<=m;i++)if(!deg[i])que.ep(i),h[i]=1;
    while(!que.empty()){
        int u=que.front();que.pop();
        if(!(--deg[a[u]]))  que.ep(a[u]),h[a[u]]=h[u]+1;
    }
    iota(p+1,p+m+1,1);
    sort(p+1,p+m+1,[&](int x,int y){return pii(a[x],h[x])<pii(a[y],h[y]);});
    for(int i=1;i<=m;i++)   ::q[::p[i]]=i;
    for(int i=1;i<=m;i++){
        if(!L[a[p[i]]]) L[a[p[i]]]=i;
        R[a[p[i]]]=i;
    }
    build(all);
    for(int i=1;i<=n;i++)   st.ep(i);
    for(int i=1;i<=m;i++)   calc(i,0);
    while(q--){
        int x;scanf("%d",&x);
        int mx=*s[b[x]].rbegin();
        st.erase(st.find(1ll*n*mx+b[x]));
        s[b[x]].erase(s[b[x]].find(w[x]));
        if(!s[b[x]].empty())    st.ep(1ll*n**s[b[x]].rbegin()+b[x]);
        else    st.ep(b[x]);
        scanf("%d",&b[x]);upd(::q[x]);
        calc(x,0);calc(a[x],1);
        ll ans=*st.begin();
        if(ans>2ll*n*m) puts("-1");
        else    printf("%lld\n",ans);
    }
}