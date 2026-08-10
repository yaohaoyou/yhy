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
const int maxn=1e6+10;
int n,m,K,tot;
int a[maxn],id[maxn][20];
namespace Graph{
    const int maxm=maxn<<2;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=tot;i++)head[i]=0;tot=0;cnt=1;}
}
using namespace Graph;
pii E[maxn];
bool bk[maxn][20];
char s[20];
int deg[maxn];
bool hasCycle(){
    for(int i=1;i<=tot;i++)deg[i]=0;
    for (int u=1;u<=tot;u++)
        go(u,i) ++deg[t];
    queue<int> q;
    for (int i=1;i<=tot;i++)if(!deg[i])q.ep(i);
    int cur=0;
    while (!q.empty()){
        int u=q.front();
        q.pop();
        ++cur;
        go(u,i)if(!(--deg[t]))q.ep(t);
    }
    return cur!=tot;
}
void matt(){
    rebuild();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&E[i].fi,&E[i].se);
    scanf("%d",&K);
    tot=0;for(int i=1;i<=n;i++)for(int j=1;j<=K;j++)id[i][j]=++tot;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=K;j++)bk[i][j]=s[j]=='o';
        for(int j=1;j<K;j++){
            if(bk[i][j]&&bk[i][j+1])add(id[i][j],id[i][j+1]);
        }
        if(bk[i][K]&&bk[i][1])add(id[i][K],id[i][1]);
    }
    for(int i=1;i<=m;i++){
        auto [u,v]=E[i];
        for(int j=1;j<K;j++){
            if(bk[u][j]&&bk[v][j+1])    add(id[u][j],id[v][j+1]);
            if(bk[v][j]&&bk[u][j+1])    add(id[v][j],id[u][j+1]);
        }
        if(bk[u][K]&&bk[v][1])    add(id[u][K],id[v][1]);
        if(bk[v][K]&&bk[u][1])    add(id[v][K],id[u][1]);
    }
    puts(hasCycle()?"Yes":"No");
}
int main(){int T;cin>>T;while(T--)matt();}