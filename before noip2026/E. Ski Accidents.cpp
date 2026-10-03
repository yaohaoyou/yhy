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
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};deg[v]++;head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){cnt=1;for(int i=1;i<=n;i++)head[i]=deg[i]=0;}
}
using namespace Graph;
int typ[maxn];
queue<int> q;
void bfs(){
    for(int i=1;i<=n;i++)   typ[i]=0;
    for(int i=1;i<=n;i++)
        if(!deg[i]){
            typ[i]=1;
            q.ep(i);
        }
    while(!q.empty()){
        int u=q.front();q.pop();
        printf("%d\n",u);
        go(u,i){
            int t=e[i].to;
            if(typ[t]^3){
                if(typ[u]==1)   typ[t]=2;
                else if(typ[u]==2)  typ[t]=3;
                else if(!typ[t])    typ[t]=1;
            }
            if(!(--deg[t])) q.ep(t);
        }
    }
}
int t,T;
void matt(){
    rebuild();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    bfs();
    int tot=0;
    for(int i=1;i<=n;i++)
        if(typ[i]==3)   tot++;
    printf("%d\n",tot);
    for(int i=1;i<=n;i++)
        if(typ[i]==3)   printf("%d ",i);
    puts("");
    // for(int i=1;i<=n;i++)   printf("%d ",typ[i]);
}
int main(){scanf("%d",&T);for(t=1;t<=T;t++)matt();}