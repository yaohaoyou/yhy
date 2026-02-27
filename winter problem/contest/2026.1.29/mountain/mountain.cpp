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
const int maxn=1e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y=mod-2){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,q;
int a[maxn],ia[maxn],to[maxn];
vector<int> I[maxn],D[maxn];
multiset<int> st;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pt(int p,int s){mmul(tr[p],s);mmul(tag[p],s);}
    inline void pu(int p){tr[p]=imadd(tr[ls],tr[rs]);}
    inline void pd(int p){if(tag[p]^1)pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=1;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    void build(setpos){tag[p]=1;if(l==r)return tr[p]=1,void();setmid;build(lson);build(rson);pu(p);}
}
using namespace SegmentTree;
int main(){
    freopen("mountain.in","r",stdin);freopen("mountain.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){int p,q;scanf("%d%d",&p,&q);a[i]=immul(p,qpow(q));ia[i]=qpow(a[i]);}
    for(int i=1;i<=m;i++){int l,r;scanf("%d%d",&l,&r);I[l+1].eb(l);D[r+1].eb(l);}
    build(all);
    for(int i=1;i<=n;i++){
        for(int j:I[i]) st.ep(j);
        for(int j:D[i]) st.erase(st.find(j));
        to[i]=st.empty()?0:*prev(st.end());
        upd(all,to[i]+1,i,ia[i]);
    }
    printf("%d\n",tr[1]);
    while(q--){
        int x,p,q;
        scanf("%d%d%d",&x,&p,&q);
        int t=a[x];
        a[x]=immul(p,qpow(q));
        ia[x]=qpow(a[x]);
        mmul(t,ia[x]);
        upd(all,to[x]+1,x,t);
        printf("%d\n",tr[1]);
    }
}