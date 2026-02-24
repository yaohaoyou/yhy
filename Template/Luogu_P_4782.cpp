//  P4782 【模板】2-SAT
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
int cnt=0,head[maxn];
struct edge{
    int nxt,to;
}e[maxn];
void add(int u,int v){
    // printf("%d %d\n",u,v);
    e[++cnt]={head[u],v};
    head[u]=cnt;
}
namespace Tarjan{
int dfsn[maxn],low[maxn],scc[maxn];
int tot,cscc;
bool instk[maxn];
stack<int> stk;
void tarjan(int u){
    dfsn[u]=low[u]=++tot;
    stk.push(u);
    instk[u]=true;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(!dfsn[t]){
            tarjan(t);
            low[u]=min(low[u],low[t]); 
        }
        else if(instk[t])   low[u]=min(low[u],dfsn[t]);
    }
    if(dfsn[u]==low[u]){
        ++cscc;
        int p=-1;
        while(p!=u){
            p=stk.top();
            stk.pop();
            instk[p]=false;
            scc[p]=cscc;
        }
    }
}
}
using namespace Tarjan;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    // printf("%d\n",__gcd(n,m));
    for(int i=1;i<=m;i++){
        int a,x,b,y;
        scanf("%d%d%d%d",&a,&x,&b,&y);
        add(a+x*n,b+(y^1)*n);
        add(b+y*n,a+(x^1)*n);
    }
    for(int i=1;i<=(n<<1);i++){
        if(!dfsn[i])    tarjan(i);
    }
    for(int i=1;i<=n;i++){
        if(scc[i]==scc[i+n]){
            puts("IMPOSSIBLE");
            exit(0);
        }
    }
    puts("POSSIBLE");
    for(int i=1;i<=n;i++){
        if(scc[i]<scc[i+n])  printf("1 ");
        else    printf("0 ");
    }
}