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
bool mem1;
const int maxn=4e5+10;
int n,q,k;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmn(res,query(rson,pl,pr));return res;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
}
using namespace SegmentTree;
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){x++;while(x<=n+1){tr[x]+=s;x+=lowbit(x);}}
    inline void upd(int l,int r,int s){add(l,s);add(r+1,-s);}
    inline ll que(int x){x++;ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){mems(tr,0);}
}T;
int a[maxn];
vector<int> v[maxn],pq[maxn];
vector<pii> vq[maxn];
ll ans[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&q,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[a[i]].eb(i);
    for(int i=1;i<=q;i++){int x,v;scanf("%d%d",&x,&v);vq[v].eb(x,i);pq[x].eb(i);}
    ll now=0;
    for(int i=1;i<=n;i++){
        now+=T.query(a[i]+1,min(n,a[i]+k));
        for(int id:pq[i])  ans[id]=now;
        T.add(a[i],1);
    }
    T.clear();
    for(int i=n-k+1;i<=n;i++)for(int j:v[i])upd(all,0,j-1,1),T.upd(0,j-1,1);
    for(int i=n;i;i--){
        for(int j:v[i+k+1]) upd(all,j,n,-1);
        for(int j:v[i]) upd(all,0,j-1,-1),T.upd(0,j-1,-1);
        for(int j:v[i+1])   upd(all,j,n,1);
        if(i>k)for(int j:v[i-k])upd(all,0,j-1,1),T.upd(0,j-1,1);
        for(auto [j,id]:vq[i])   ans[id]+=query(all,0,j)-T.que(j);
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}