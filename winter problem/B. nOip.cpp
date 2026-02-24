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
int n,m;
bool mk[2][maxn];
int deg[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
queue<pii> q;
void matt(int _cases){
    rebuild();
    for(int i=1;i<=n;i++)   mk[0][i]=mk[1][i]=false,deg[i]=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   mk[0][i]=true;
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        if(!w)  mk[0][u]=mk[0][v]=0,deg[u]++,deg[v]++;
        adde(u,v,w);
    }
    for(int i=1;i<=n;i++)if(mk[0][i])q.ep(i,0);
    while(!q.empty()){
        int u=q.front().fi,o=q.front().se;q.pop();
        // printf("%d %d\n",u,o);
        if(!o){
            go(u,i){
                if(!mk[1][t]){
                    mk[1][t]=true;
                    q.ep(t,1);
                }
            }
        }
        else{
            go(u,i){
                if(!w&&!mk[0][t]){
                    if(!(--deg[t])) mk[0][t]=true,q.ep(t,0);
                }
            }
        }
    }
    for(int i=1;i<=n;i++)if(mk[0][i])putchar('0');else putchar('1');
    putchar('\n');
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}