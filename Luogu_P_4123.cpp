#include<bits/stdc++.h>
#define pii pair<int,int>
#define piii pair<int,pii>
#define eb emplace_back
using namespace std;
const int maxn=1e4+10;
const int maxm=maxn*100;
int n,m;
struct Tree{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}Tr;
namespace Graph{
    piii g[maxn];
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void rebuild(){cnt=1;memset(head,0,sizeof(head));for(int i=1;i<=m;i++){add(g[i].first,g[i].second.first,g[i].second.second);add(g[i].second.first,g[i].first,g[i].second.second);}}
}
using namespace Graph;
int S,T;
namespace DINIC{
    const int inf=0x3f3f3f3f;
    int d[maxn],now[maxn];
    queue<int> q;
    inline bool bfs(){
        while(!q.empty())   q.pop();
        memset(d,0x3f,sizeof(d));
        memcpy(now,head,sizeof(head));
        d[S]=0;
        q.push(S);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(d[t]!=inf||!e[i].w)  continue;
                d[t]=d[u]+1;
                q.push(t);
                if(t==T)    return true;
            }
        }
        return false;
    }
    int dfs(int u,int flw){
        if(u==T)    return flw;
        int res=0;
        for(int i=now[u];i&&flw;i=e[i].nxt){
            now[u]=i;
            int t=e[i].to;
            if(d[t]!=d[u]+1||!e[i].w)    continue;
            int k=dfs(t,min(e[i].w,flw));
            if(!k)  d[t]=inf;
            e[i].w-=k;e[i^1].w+=k;
            res+=k;flw-=k;
        }
        return res;
    }
    inline int dinic(){
        rebuild();
        int res=0;
        while(bfs())    res+=dfs(S,inf);
        return res;
    }
}
using namespace DINIC;
namespace DFS{
    int w[20][maxn],f[20][maxn],dep[maxn];
    void dfs(int u,int fa){
        dep[u]=dep[f[0][u]=fa]+1;w[0][u]=inf;
        for(int i=Tr.head[u];i;i=Tr.e[i].nxt){
            int t=Tr.e[i].to;
            if(t==fa)   continue;
            dfs(t,u);
            w[0][t]=Tr.e[i].w;
        }
    }
    inline void init_LCA(){for(int i=1;i<=19;i++)for(int j=1;j<=n;j++){w[i][j]=min(w[i-1][j],w[i-1][f[i-1][j]]);f[i][j]=f[i-1][f[i-1][j]];}}
    inline int LCA(int x,int y){  // O(nlogn) - O(logn) 倍增（not LCA!!!）
        int res=inf;
        if(dep[x]<dep[y])   swap(x,y);
        for(int i=19;~i;i--){
            if(dep[f[i][x]]>=dep[y]){
                res=min(res,w[i][x]);
                x=f[i][x];
            }
        }
        if(x==y)    return res;
        for(int i=19;~i;i--){
            if(f[i][x]^f[i][y]){
                res=min(res,w[i][x]);res=min(res,w[i][y]);
                x=f[i][x];y=f[i][y];
            }
        }
        res=min(res,w[0][x]);res=min(res,w[0][y]);
        return res;
    }
}
vector<int> v,v1,v2;
void divide(int l,int r){
    v1.clear();v2.clear();
    if(l>=r)    return;
    S=v[l];T=v[l+1];
    int res=dinic();
    Tr.add(S,T,res);Tr.add(T,S,res);
    for(int i=l;i<=r;i++){
        // printf("%d\n",v[i]);
        if(d[v[i]]!=inf)   v1.eb(v[i]);
        else    v2.eb(v[i]);
    }
    for(int i=0;i<v1.size();i++)    v[i+l]=v1[i];
    for(int i=0;i<v2.size();i++)    v[i+l+v1.size()]=v2[i];
    int siz=v1.size();
    divide(l,l+siz-1);divide(l+siz,r);
}
vector<int> ans;
void AbsInit(){
    Tr.cnt=1;
    memset(Tr.head,0,sizeof(Tr.head));
    ans.clear();v.clear();
}
void AbsMatt(){
    AbsInit();
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d%d",&g[i].first,&g[i].second.first,&g[i].second.second);
    }
    for(int i=0;i<=n;i++)   v.eb(i);
    divide(1,n);
    DFS::dfs(1,0);
    DFS::init_LCA();
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)    ans.eb(DFS::LCA(i,j));
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    printf("%d\n",ans.size());
}
int main(){
    int t=1;
    while(t--)  AbsMatt();
}