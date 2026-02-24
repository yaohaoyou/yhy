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
const int maxn=8e5+10,V=2e5;
int n;
int now[maxn],deg[maxn];
bool ans[maxn];
vector<pii> son[maxn];
inline void adde(int u,int v,int id){son[u].eb(v,id);son[v].eb(u,id);}
void dfs(int u,int fr){
    deg[u]=0;
    for(int i=now[u];i<son[u].size();i=now[u]){
        now[u]=i+1;
        int t=son[u][i].fi,w=son[u][i].se;if(t==fr)continue;
        ans[w]=t>V; 
        dfs(t,u);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int u,v;scanf("%d%d",&u,&v);
        adde(u,v+V,i);deg[u]++;deg[v+V]++;
    }
    int edg=n;
    for(int i=1;i<=V+V;i++)if(deg[i]&1)adde(0,i,++edg);
    for(int i=1;i<=V+V;i++)if(deg[i])dfs(i,0);
    for(int i=1;i<=n;i++)   putchar(ans[i]?'b':'r');
}