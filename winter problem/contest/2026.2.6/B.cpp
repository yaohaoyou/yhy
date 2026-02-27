#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,N=1e9;
bool mem1;
int n,k;
ll m;
struct ope{int x,p,id;}b[maxn];
ll pre[maxn],suf[maxn];
int d[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   d[i]=b[i].x;
    sort(d+1,d+n+1);k=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++)   b[i].x=lower_bound(d+1,d+k+1,b[i].x)-d;
}
inline pli get(pli x,int p,int q){return pli(1ll*(q-p)*x.se+x.fi,x.se);}
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all rt,-N,N
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int tot,rt;
    int lc[maxn*40],rc[maxn*40];
    pli tr[maxn*40];
    inline void pt(int p,pli s){tr[p].fi+=s.fi;tr[p].se+=s.se;}
    void upd(setpos,int pl,int pr,pli s){
        if(!p)p=++tot;
        if(l>=pl&&r<=pr)return pt(p,s);
        setmid;if(pr<=mid)return upd(lson,pl,pr,s);if(pl>mid)return upd(rson,pl,pr,s);
        upd(lson,pl,pr,s);upd(rson,mid+1,pr,get(s,pl,mid+1));
    }
    inline ll query(int x){
        int p=rt,l=-N,r=N;ll res=0;
        while(l^r){
            if(!p)break;
            // printf("%d [%d,%d] : (%d,%d)\n",p,l,r,tr[p].fi,tr[p].se);
            setmid;
            res+=tr[p].fi+1ll*tr[p].se*(x-l);
            (x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        if(p){res+=tr[p].fi+1ll*tr[p].se*(x-l);}
        return res;
    }
    void clear(){for(int i=0;i<=tot;i++)lc[i]=rc[i]=0,tr[i]=pli(0,0);tot=rt=0;}
}
using namespace SegmentTree;
struct ST{
    int Log[maxn];
    ll st[20][maxn];
    void build(ll *arr){
        for(int i=2;i<=k;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=k;i++)   st[0][i]=arr[i];
        for(int i=1;i<=Log[k];i++)
            for(int j=1;j+(1<<i)-1<=k;j++)  st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline ll query(int l,int r){if(l>r)return -1e18;int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}pr,sf,st;
bool mem2;
void matt(int _cases){
    clear();
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&b[i].x,&b[i].p),b[i].id=i;
    discrete();
    for(int i=1;i<=n;i++){
        int x=b[i].x,p=b[i].p;
        // printf("%d %d : %d\n",d[x]-p+1,d[x]);
        upd(all,d[x]-p+1,d[x],pii(1,1));upd(all,d[x]+1,d[x]+p,pii(p-1,-1));
    }
    for(int i=1;i<=k;i++)   pre[i]=query(d[i]);
    st.build(pre);
    for(int i=1;i<=k;i++)   suf[i]=pre[i]+d[i];
    for(int i=1;i<=k;i++)   pre[i]=pre[i]-d[i];
    pr.build(pre);sf.build(suf);

    for(int i=1;i<=n;i++){
        int x=d[b[i].x],p=b[i].p;
        int L=lower_bound(d+1,d+k+1,x-p+1)-d,R=upper_bound(d+1,d+k+1,x+p)-d-1;
        printf("%d",st.query(1,L-1)<=m&&pr.query(L,b[i].x)+x-p<=m&&st.query(R+1,k)<=m&&sf.query(b[i].x,R)-x-p<=m);
    }
    puts(""); 
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}