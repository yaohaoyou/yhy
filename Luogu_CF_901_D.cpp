#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n,m;
int a[maxn];
map<pii,int> id;
pii E[maxn];
ll ans[maxn];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;bool istr;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v,false};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
ll f[maxn];
bool vis[maxn];
int dep[maxn];
namespace Finish{
    void Yes(){puts("YES");for(int i=1;i<=m;i++){int u=E[i].fi,v=E[i].se;if(e[i<<1].istr||e[i<<1|1].istr)printf("%lld\n",f[dep[u]>dep[v]?u:v]);else printf("%lld\n",ans[i]);}exit(0);}
    void No(){exit(puts("NO")&0);}
}
void dfs(int u){
    vis[u]=true;
    f[u]=0;
    go(u,i){
        int t=e[i].to;
        if(vis[t])  continue;
        e[i].istr=true;
        dep[t]=dep[u]+1;
        dfs(t);
        f[u]+=f[t];
    }
    f[u]=a[u]-f[u];
}
void dfs2(int u){
    go(u,i){
        if(e[i].istr)   continue;
        int t=e[i].to;
        if(!((dep[u]-dep[t])&1)){
            ll tmp=f[1];
            a[u]--;a[t]--;
            mems(vis,0);dfs(1);
            ll k=tmp/(f[1]-tmp);
            a[u]++;a[t]++;
            ans[i>>1]=-k;
            a[u]+=k;a[t]+=k;
            mems(vis,0);dfs(1);
            Finish::Yes();
        }
    }
    go(u,i)if(e[i].istr)dfs2(e[i].to);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1,u,v;i<=m;i++){scanf("%d%d",&u,&v);adde(u,v);id[{u,v}]=id[{v,u}]=i;E[i]=pii(u,v);}
    dfs(1);
    if(!f[1])   Finish::Yes();
    if(f[1]&1)   Finish::No();
    dfs2(1);
    Finish::No();
}