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
bool mem1;
const int maxn=2e5+10;
int n,m,siz[maxn];
vector<int> son[maxn],g[maxn],A[2],path;
inline void adde(int u,int v){son[u].eb(v);son[v].eb(u);}
void ins(int u,vector<int>&v){v.eb(u);for(int t:g[u])ins(t,v);}
void dfs(int u,int ft){
    siz[u]=1;
    for(int t:son[u])if((t^ft)&&!siz[t]){
        dfs(t,u);siz[u]+=siz[t];
        g[u].eb(t);
    }
}
void dfs2(int u){
    path.eb(u);
    sort(g[u].begin(),g[u].end(),[&](int x,int y){return siz[x]<siz[y];});
    if(!g[u].empty()){
        for(int t:g[u])if(t^g[u].back())ins(t,A[A[0].size()>A[1].size()]);
        int t=g[u].back();
        if(min(A[0].size(),A[1].size())+siz[t]==max(A[0].size(),A[1].size()))   ins(t,A[A[0].size()>A[1].size()]);
        else dfs2(t);
    }
}
bool mem2;
int main(){
    freopen("find.in","r",stdin);freopen("find.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);dfs2(1);
    printf("%d %d\n",path.size(),A[0].size());
    for(int i:path) printf("%d ",i);puts("");
    if(!A[0].empty()){for(int i:A[0]) printf("%d ",i);puts("");}
    if(!A[1].empty()){for(int i:A[1]) printf("%d ",i);puts("");}
}