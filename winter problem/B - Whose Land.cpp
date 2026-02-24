#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10,maxk=25,inf=1e9;
int n,K,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].mx;i;i=e[i].nxt,t=e[i].mx)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,mx;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void upd(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int tot;
int fa[maxn],bfsn[maxn],ans[maxn];
pii p[maxn][maxk];
vector<pii> seg[maxn],Q[maxn];
queue<int> que;
set<piii> s;
set<piii>::iterator split(int x){
    auto it=--s.upper_bound(piii(pii(x,inf),inf));
    auto [l,r]=it->fi;int k=it->se;
    if(r<x) return s.end();
    if(l==x)    return it;
    s.erase(it);
    s.ep(pii(l,x-1),k);
    return s.ep(pii(x,r),k).fi;
}
inline void upd(int x){
    for(auto [l,r]:seg[x]){
        auto itr=split(r+1),itl=split(l);
        for(auto i=itl;i!=itr;i++)  if(i->se)T.upd(i->se,-(i->fi.se-i->fi.fi+1));
        s.erase(itl,itr);
        s.ep(pii(l,r),x);
        T.upd(x,r-l+1);
    }
    seg[x].clear();
}
void dfs(int u){
    p[u][0].fi=p[u][0].se=bfsn[u];
    for(int i=1;i<=K;i++)   p[u][i]=pii(inf,0);
    go(u,_)if(t^fa[u]){
        dfs(t);
        for(int i=1;i<=K;i++)   gmn(p[u][i].fi,p[t][i-1].fi),gmx(p[u][i].se,p[t][i-1].se);
    }
}
void matt(int _cases){
    rebuild();tot=0;T.clear();for(int i=0;i<=n;i++)fa[i]=0;
    scanf("%d%d%d",&n,&K,&q);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    que.ep(1);
    while(!que.empty()){
        int u=que.front();que.pop();
        bfsn[u]=++tot;
        go(u,i)if(t^fa[u])  fa[t]=u,que.ep(t);
    }
    // for(int i=1;i<=n;i++)   debug("%d ",bfsn[i]);debug("\n");
    dfs(1);
    for(int i=1;i<=n;i++){
        int u=i,x=K;
        while(u){
            for(int j=0;j<=x;j++)   seg[i].eb(p[u][j]);
            u=fa[u];if(!x)break;x--;
        }
        sort(seg[i].begin(),seg[i].end());
        vector<pii> tmp;tmp.clear();
        int L=0,R=0;
        for(auto [l,r]:seg[i]){
            if(r<=R)    continue;
            if(l<=R)    R=r;
            else{
                if(L)tmp.eb(L,R);
                L=l,R=r;
            }
        }
        tmp.eb(L,R);
        seg[i].swap(tmp);
        // for(pii j:seg[i])   debug("%d %d\n",j.fi,j.se);debug("\n");
    }
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
    s.clear();s.ep(pii(1,n),0);
    for(int i=1;i<=n;i++){
        upd(i);
        for(auto [l,id]:Q[i])   ans[id]=T.query(l,i);
        Q[i].clear();
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}