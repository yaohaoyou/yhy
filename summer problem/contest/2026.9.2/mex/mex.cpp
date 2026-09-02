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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10,inf=1e9;
int n,m,q;
int a[maxn],pre[maxn],buc[maxn];
set<int> st[maxn];
multiset<int> pq;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tr2[maxn<<2],mn[maxn<<2],pos[maxn],L[maxn<<2],R[maxn<<2];
    int query(setpos,int s){
        if(l==r)    return l-min(pre[l],s);
        setmid;
        if(mn[rs]>=s)   return min(query(lson,s),mid+1-s);
        return min(tr2[ls],query(rson,s));
    }
    inline void pu(setpos){
        mn[p]=min(mn[ls],mn[rs]);
        setmid;
        tr2[ls]=query(lson,mn[rs]);
        tr[p]=min(tr2[ls],tr[rs]);
    }
    void build(setpos){L[p]=l;R[p]=r;if(l==r)return tr[p]=l-pre[l],mn[p]=pre[l],pos[l]=p,void();setmid;build(lson);build(rson);pu(p,l,r);}
    inline void upd(int x){
        int p=pos[x];tr[p]=x-pre[x];mn[p]=pre[x];
        while(p>>=1)pu(p,L[p],R[p]);
    }
}
using namespace SegmentTree;
int main(){
    freopen("mex.in","r",stdin);freopen("mex.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   buc[i]=-inf;
    for(int i=1;i<=n;i++){pre[i]=buc[a[i]];buc[a[i]]=i;st[a[i]].ep(i);}
    for(int i=1;i<=m;i++)   pq.ep(buc[i]);
    build(all);
    while(q--){
        int p,x;scanf("%d%d",&p,&x);
        auto it=st[a[p]].upper_bound(p);
        int nx=it==st[a[p]].end()?0:*it,pr;
        it--;
        pr=it==st[a[p]].begin()?-inf:*(--it);
        if(nx)  pre[nx]=pr,upd(nx);
        else    pq.erase(pq.find(p)),pq.ep(pr);
        st[a[p]].erase(p);
        
        it=st[x].lower_bound(p);
        nx=it==st[x].end()?0:*it;
        pr=it==st[x].begin()?-inf:*(--it);
        if(nx)  pre[nx]=p,upd(nx);
        else{
            if(pq.find(pr)==pq.end())printf("%d\n",pr),exit(0);pq.erase(pq.find(pr)),pq.ep(p);
        }
        pre[p]=pr;upd(p);
        a[p]=x;
        st[a[p]].ep(p);
        int ans=min(n-*pq.begin()+1,query(all,*pq.begin()));
        // printf("%d\n",query(all,*pq.begin()));
        printf("%d\n",ans>n?-1:ans);
    }
}