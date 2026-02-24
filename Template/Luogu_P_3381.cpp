//  P3381 【模板】最小费用最大流
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+10,maxm=5e4*2+10,inf=0x3f3f3f3f;
int n,m;
namespace Graph{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w,co;}e[maxm];
    inline void add(int u,int v,int w,int co){e[++cnt]={head[u],v,w,co};head[u]=cnt;}
}
using namespace Graph;
int d[maxn],pre[maxn],ipre[maxn],flw[maxn];
int S,T;
queue<int> q;
bool inque[maxn];
inline bool bfs(){
    memset(d,0x3f,sizeof(d));
    memset(flw,0x3f,sizeof(flw));
    memset(inque,0,sizeof(inque));
    d[S]=pre[T]=0;
    inque[S]=true;
    q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();inque[u]=false;
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to,w=e[i].w,c=e[i].co;
            if(!w||d[t]<=d[u]+c)  continue;
            d[t]=d[u]+c;pre[t]=u;ipre[t]=i;
            flw[t]=min(flw[u],w);
            if(!inque[t]){inque[t]=true;q.push(t);}
        }
    }
    return pre[T];
}
void MCMF(){  // min cost max flow
    int ans=0,cost=0;
    while(bfs()){
        ans+=flw[T];cost+=(flw[T]*d[T]);
        for(int p=T;p!=S;p=pre[p]){
            e[ipre[p]].w-=flw[T];e[ipre[p]^1].w+=flw[T];
        }
    }
    printf("%d %d\n",ans,cost);
}
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1,u,v,w,c;i<=m;i++){
        scanf("%d%d%d%d",&u,&v,&w,&c);
        add(u,v,w,c);add(v,u,0,-c);
    }
    MCMF();
}