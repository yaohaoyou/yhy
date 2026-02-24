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
const int maxn=5e5+10,maxm=4e6+10;
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
stack<int> stk;
int cdcc;
vector<int> vdcc[maxn];
void tarjan(int u,int fr){
    dfsn[u]=low[u]=++tot;stk.ep(u);
    go(u,i){
        if(i==(fr^1))   continue;
        if(!dfsn[t]){
            tarjan(t,i);
            gmn(low[u],low[t]);
        }
        else    gmn(low[u],dfsn[t]);
    }
    if(low[u]==dfsn[u]){
        cdcc++;
        int p=0;
        do{
            p=stk.top();stk.pop();
            vdcc[cdcc].eb(p);
        }while(p^u);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i,0);
    printf("%d\n",cdcc);
    for(int i=1;i<=cdcc;i++){
        printf("%d ",vdcc[i].size());
        for(int j:vdcc[i])  printf("%d ",j);
        puts("");
    }
}