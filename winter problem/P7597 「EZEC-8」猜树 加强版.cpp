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
const int maxn=5010;
int n;
random_device rnds;
int a[maxn],fa[maxn],dep[maxn];
bool vis[maxn];
vector<int> tr[maxn];
inline int ask(int u,int v){if(u==v)return 0;printf("? 1 %d %d\n",u,v);fflush(stdout);int x;scanf("%d",&x);return x;}
inline vector<int> ask(int u){printf("? 2 %d\n",u);fflush(stdout);int x;vector<int> ret;scanf("%d",&x);while(x--){scanf("%d",&u);ret.eb(u);}return ret;}
void dfs(int u){
    if(tr[u].size()==1) return;
    for(int i:tr[u])    vis[i]=true;
    vis[u]=false;
    int x=tr[u][rand()%tr[u].size()];
    int son;
    for(int t:tr[u]){
        if(dep[t]^(dep[u]+1))   continue;
        if(ask(t,x)+dep[t]==dep[x]){son=t;break;}
    }
    for(int t:tr[u]){
        if(dep[t]^(dep[u]+1))   continue;
        fa[t]=u;
        if(t==son)  continue;
        tr[t]=ask(t);
        for(int i:tr[t])    vis[i]=false;
    }
    for(int i:tr[u])if(vis[i])tr[son].eb(i),vis[i]=false;
    for(int t:tr[u])if(dep[t]==dep[u]+1)dfs(t);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   tr[1].eb(i);
    shuffle(tr[1].begin(),tr[1].end(),rnds);
    for(int i=1;i<=n;i++)   dep[i]=ask(1,i);
    dfs(1);
    printf("! ");for(int i=2;i<=n;i++)printf("%d ",fa[i]);fflush(stdout);
}