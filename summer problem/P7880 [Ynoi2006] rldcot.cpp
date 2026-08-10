#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define plii pair<ll,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
unordered_map<ll,int> mp;
int tot;
ll dep[maxn];
int siz[maxn],son[maxn],dfsn[maxn],rnk[maxn],ans[maxn];
set<int> st[maxn];
vector<pli> v[maxn];vector<pii> Q[maxn];
void dfs(int u,int ft){
    dfsn[u]=++tot;rnk[tot]=u;
    siz[u]=1;
    go(u,i){
        if(t==ft)   continue;
        dep[t]=dep[u]+w;
        dfs(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs1(int u,int ft){
    if(son[u]){
        dfs1(son[u],u);
        st[u].swap(st[son[u]]);
    }
    v[u].eb(dep[u],u);
    st[u].ep(u);
    go(u,i){
        if(t==ft||t==son[u])   continue;
        dfs1(t,u);
        for(int k=dfsn[t];k<=dfsn[t]+siz[t]-1;k++){
            int j=rnk[k];
            auto it=st[u].lower_bound(j);
            if(it!=st[u].end()) v[*it].eb(dep[u],j);
            if(it!=st[u].begin())   v[j].eb(dep[u],*prev(it));
        }
        for(int j:st[t])    st[u].ep(j);
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
    dfs(1,0);dfs1(1,0);
    int cur=0;
    for(int i=1;i<=n;i++){
        for(auto [j,k]:v[i]){
            if(mp[j]>=k) continue;
            if(mp[j])   T.add(mp[j],-1);
            mp[j]=k;
            T.add(mp[j],1);
        }
        for(auto [j,k]:Q[i])    ans[k]=T.query(j,i);
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}