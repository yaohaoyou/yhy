#include<bits/stdc++.h>
#define pii pair<int,int>
#define ui unsigned int
using namespace std;
const int maxn=3e5+10,maxm=3e5+10;
int n,m;
int deg[maxn];
bitset<maxn> to;
pii lin[maxm];
namespace Graph{
    int cnt=0,head[maxn];
    struct edge{
        int nxt,to;
    }e[maxm];
    void add(int u,int v){
        e[++cnt]={head[u],v};
        head[u]=cnt;
    }
}
using namespace Graph;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&lin[i].first,&lin[i].second);
        deg[lin[i].first]++,deg[lin[i].second]++;
    }
    for(int i=1;i<=m;i++){
        int u=lin[i].first,v=lin[i].second;
        if(deg[u]>deg[v])   swap(u,v);
        else if(deg[u]==deg[v]&&u>v)    swap(u,v);
        add(u,v);
        lin[i]=pii(u,v);
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        int u=lin[i].first,v=lin[i].second;
        for(int j=head[u];j;j=e[j].nxt) to.set(e[j].to);
        for(int k=head[v];k;k=e[k].nxt) if(to[e[k].to]) ans++;
        for(int j=head[u];j;j=e[j].nxt) to.reset(e[j].to);
    }
    printf("%d\n",ans);
}