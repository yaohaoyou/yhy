#include<bits/stdc++.h>
// #include "game.h"
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=5e4+10,maxp=maxn*100,inf=1e9;
const ll INF=1e18;
int n,m,k,l,tot,S,T;
struct point{ll x,y;int id;point(ll _x=0,ll _y=0,int _id=0){x=_x;y=_y;id=_id;}void ch(){ll _x=x;x+=y;y-=_x;}};
struct robot{int a,b,t,w;point in,out;}a[maxn];
point p[maxn<<1];
ll b[maxn<<1];
void init(int c,int t){return;}
namespace Graph{
    const int maxm=maxp*10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w,co=e[i].co;i;i=e[i].nxt,t=e[i].to,w=e[i].w,co=e[i].co)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w,co;}e[maxm];
    inline void add(int u,int v,int w,int co){e[++cnt]={head[u],v,w,co};head[u]=cnt;}
    inline void adde(int u,int v,int w,int co){add(u,v,w,co);add(v,u,0,-co);}
}
using namespace Graph;
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) root[x],1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int nw;
    int root[maxn],lc[maxp],rc[maxp];
    void upd(int &p,int q,int l,int r,int x,int id){
        p=++tot;if(q)adde(p,q,k,0);
        lc[p]=lc[q];rc[p]=rc[q];
        if(l==r)return adde(p,id,k,0);
        setmid;(x<=mid)?upd(ls,lc[q],l,mid,x,id):upd(rs,rc[q],mid+1,r,x,id);
        if(ls)adde(p,ls,k,0);if(rs)adde(p,rs,k,0);
    }
    void ADD(setpos,int pl,int pr,int x){if(!p)return;if(l>=pl&&r<=pr)return adde(x,p,k,0);setmid;if(pl<=mid)ADD(lson,pl,pr,x);if(pr>mid)ADD(rson,pl,pr,x);}
}
using namespace SegmentTree;
inline void rebuild(){for(int i=0;i<=tot;i++)head[i]=lc[i]=rc[i]=0;cnt=1;}
ll dis[maxp],h[maxp];
int ti[maxp];
int pre[maxp];
bool vis[maxp];
priority_queue<pli,vector<pli>,greater<pli>> q;
bool dijkstra(){
    while(!q.empty())q.pop();
    for (int i=1;i<=tot;i++)  dis[i]=INF,vis[i]=0;
    dis[S]=0;
    q.ep(0,S);
    while (!q.empty()) {
        int u=q.top().se;q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        go(u,i){
            ll nc=co+h[u]-h[t];
            if (w&&dis[t]>dis[u]+nc) {
                dis[t]=dis[u]+nc;pre[t]=i;
                if(!vis[t]) q.ep(dis[t],t);
            }
        }
    }
    return dis[T] != INF;
}
inline ll PD(){  // Primal-Dual
    ll cost=0;int tim=k;
    fill(h+1,h+tot+1,0);
    while(tim--){
        if(!dijkstra()) return -1;
        for(int i=1;i<=tot;i++)   h[i]+=dis[i];
        for(int p=T;p^S;p=e[pre[p]^1].to){
            e[pre[p]].w--;e[pre[p]^1].w++;
        }
        cost+=h[T];
    }
    return cost;
}
void discrete(){
    m=0;
    for(int i=1;i<=n;i++)   b[++m]=a[i].in.y,b[++m]=a[i].out.y;
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].in.y=lower_bound(b+1,b+m+1,a[i].in.y)-b,a[i].out.y=lower_bound(b+1,b+m+1,a[i].out.y)-b;
}
ll game(int N,int M,int K,vector<int> A,vector<int> B,vector<int> vT,vector<int> W){
    rebuild();
    n=N;m=M;k=K;S=tot=1;T=n+1<<1;
    for(int i=1;i<=n;i++){
        a[i]={A[i-1],B[i-1],vT[i-1],W[i-1]};
        a[i].in=point(a[i].a,a[i].t);
        a[i].out=point(a[i].b,a[i].t+abs(a[i].a-a[i].b));
        a[i].in.ch();a[i].out.ch();
        if(a[i].out.y>a[i].in.y)    swap(a[i].in,a[i].out);
        a[i].in.id=++tot;a[i].out.id=++tot;
        if(a[i].in.x==a[i].in.y)    adde(S,a[i].in.id,1,0);
        if(a[i].out.y==a[i].out.x-2*m)  adde(a[i].out.id,T,1,0);
        adde(a[i].in.id,a[i].out.id,1,a[i].w);
    }
    assert(T==++tot);
    discrete();
    l=0;for(int i=1;i<=n;i++)   p[++l]=a[i].in,p[++l]=a[i].out;
    sort(p+1,p+l+1,[&](point x,point y){return make_pair(pll(x.x,-x.y),x.id&1)<make_pair(pll(y.x,-y.y),y.id&1);});
    // for(int i=1;i<=l;i++)if(!(p[i].id&1)){
        // for(int j=i+1;j<=l;j++)if((p[j].id&1)&&(p[j].y<=p[i].y))adde(p[j].id,p[i].id,k,0);
    // }
    nw=0;
    for(int i=1;i<=l;i++){
        if(p[i].id&1){  // out
            ADD(all(nw),p[i].y,m,p[i].id);
        }
        else{  // in
            nw++;
            upd(root[nw],root[nw-1],1,m,p[i].y,p[i].id);
        }
    }
    return PD();
}
signed main() {
    // freopen("D:\\download\\game\\game5.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int c, t;
    std::cin >> c >> t;
    init(c, t);
    for (int i = 1; i <= t; i++) {
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<int> a(n), b(n), t(n), w(n);
        for (int j = 0; j < n; j++) std::cin >> a[j] >> b[j] >> t[j] >> w[j];
        std::cout << game(n, m, k, a, b, t, w) << '\n';
    }
    return 0;
}