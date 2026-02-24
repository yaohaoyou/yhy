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
const int maxn=2e5+10;
int n;
int fa[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
bool on[maxn];
int dep[maxn];
priority_queue<pii> pq;
void dfs(int u,int ft){
    fa[u]=ft;dep[u]=dep[ft]+1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
    }
}
void matt(int _cases){
    rebuild();    
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   on[i]=false;
    for(int i=2;i<=n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dep[0]=-1;
    dfs(1,0);
    {
        int x=n;
        while(x){
            on[x]=true;
            x=fa[x];
        }
    }
    for(int i=1;i<=n;i++)if(!on[i])pq.ep(dep[i],i);
    vector<pii> ans;ans.clear();
    int cnt=0;
    while(!pq.empty()){
        int u=pq.top().se;pq.pop();
        if((cnt&1)==(dep[u]&1))  ans.eb(1,0),cnt++;
        else ans.eb(1,0),ans.eb(1,0),cnt+=2;
        ans.eb(2,u);
    }
    for(int i=1;i<=n;i++)if(on[i])pq.ep(-dep[i],i);
    while(!pq.empty()){
        int u=pq.top().se;pq.pop();
        if(u==n)    break;
        if((cnt&1)==(dep[u]&1))  ans.eb(1,0),cnt++;
        else ans.eb(1,0),ans.eb(1,0),cnt+=2;
        ans.eb(2,u);
    }
    assert(ans.size()<=3*n);
    printf("%d\n",ans.size());
    for(pii i:ans){
        if(i.fi==1) puts("1");
        else printf("%d %d\n",i.fi,i.se);
    }
    puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}