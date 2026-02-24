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
const int maxn=1e5+10;
int n,m;
ll a[maxn];
int rnk[maxn][4];
vector<int> vec[2];
int tot;
namespace Graph{
    const int maxm=maxn*50;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn*17];
    struct edge{int nxt,to;ll w;}e[maxm];
    inline void add(int u,int v,ll w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,ll w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int typ;
    int id[maxn<<2];ll L[maxn<<2],R[maxn<<2];
    inline void pu(int p){
        L[p]=L[ls];R[p]=R[rs];
        if(typ==0)  add(id[p],id[ls],R[p]-R[ls]),add(id[p],id[rs],0);
        if(typ==1)  add(id[p],id[ls],0),add(id[p],id[rs],L[rs]-L[p]);
        if(typ==2)  add(id[ls],id[p],R[p]-R[ls]),add(id[rs],id[p],0);
        if(typ==3)  add(id[ls],id[p],0),add(id[rs],id[p],L[rs]-L[p]);
    }
    void build(setpos){id[p]=++tot;if(l==r)return L[p]=R[p]=a[l],rnk[l][typ]=tot,void();setmid;build(lson);build(rson);pu(p);}
    void query(setpos,int pl,int pr,bool o){if(l>=pl&&r<=pr)return vec[o].eb(p),void();setmid;if(pl<=mid)query(lson,pl,pr,o);if(pr>mid)query(rson,pl,pr,o);}
}T[4];
bool vis[maxn*20];
ll dp[maxn*20];
// priority_queue<pli,vector<pli>,greater<pli>> q;
queue<int> q;
void dijkstra(){
    mems(dp,0x3f);dp[rnk[1][0]]=0;q.ep(rnk[1][0]);
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[u]=false;
        go(u,i){
            int t=e[i].to;ll w=e[i].w;
            if(dp[t]>dp[u]+w){
                dp[t]=dp[u]+w;
                if(!vis[t]){vis[t]=true;q.ep(t);}
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    T[0].typ=0;T[0].build(all);T[1].typ=1;T[1].build(all);T[2].typ=2;T[2].build(all);T[3].typ=3;T[3].build(all);
    for(int i=1;i<=n;i++){add(rnk[i][0],rnk[i][1],0);add(rnk[i][1],rnk[i][2],0);add(rnk[i][2],rnk[i][3],0);add(rnk[i][3],rnk[i][0],0);}
    while(m--){
        int l,r,L,R;ll c;
        scanf("%d%d%d%d%lld",&l,&r,&L,&R,&c);
        vec[0].clear();vec[1].clear();
        if(r<L){
            T[2].query(all,l,r,0);T[1].query(all,L,R,1);
            tot++;
            for(int i:vec[0])   add(T[2].id[i],tot,c-T[2].R[i]);
            for(int i:vec[1])   add(tot,T[1].id[i],T[1].L[i]);
        }
        else{
            T[3].query(all,l,r,0);T[0].query(all,L,R,1);
            tot++;
            for(int i:vec[0])   add(T[3].id[i],tot,c+T[3].L[i]);
            for(int i:vec[1])   add(tot,T[0].id[i],-T[0].R[i]);
        }
    }
    dijkstra();
    for(int i=2;i<=n;i++){
        // debug("%d %d %d %d\n",rnk[i][0],rnk[i][1],rnk[i][2],rnk[i][3]);
        ll res=min({dp[rnk[i][0]],dp[rnk[i][1]],dp[rnk[i][2]],dp[rnk[i][3]]});
        printf("%lld ",res==0x3f3f3f3f3f3f3f3f?-1:res);
    }
}