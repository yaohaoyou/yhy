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
const int maxn=2e4+10,maxm=2e5+10;
int n,m;
namespace Graph{
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int tot;
int dfsn[maxn],low[maxn];
bool cut[maxn];
void tarjan(int u,int fr){
    dfsn[u]=low[u]=++tot;
    int son=0;
    go(u,i){
        if(i==(fr^1))   continue;
        if(!dfsn[t]){
            son++;
            tarjan(t,i);
            gmn(low[u],low[t]);
            if(low[t]>=dfsn[u])   cut[u]=true;
        }
        else    gmn(low[u],dfsn[t]);
    }
    if(!fr) cut[u]=son>1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i,0);
    printf("%d\n",count(cut+1,cut+n+1,true));
    for(int i=1;i<=n;i++)if(cut[i])printf("%d ",i);
}