//  树上启发式合并
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10,maxm=maxn<<1,maxr=23,inf=1e9;
int n;
int xo[maxn],f[1<<maxr];
int ans[maxn];
namespace Graph{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}
using namespace Graph;
int dep[maxn],son[maxn],siz[maxn];
// xo[u] ^ xo[v] = 0 或 2^k
void dfs1(int u,int fa){
    siz[u]=1;dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        xo[t]=xo[u]^e[i].w;
        dfs1(t,u);
        siz[u]+=siz[t];
        if(siz[son[u]]<siz[t])  son[u]=t;
    }
}
inline void getmx(int &x,int y){(x<y)&&(x=y);}
void count(int u,int fa,bool typ){
    if(typ) getmx(f[xo[u]],dep[u]);
    else    f[xo[u]]=-inf;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        count(t,u,typ);
    }
}
void dfs3(int u,int fa,int rt){
    for(int i=0;i<maxr;i++)
        getmx(ans[rt],f[xo[u]^(1<<i)]+dep[u]-(dep[rt]<<1));
    getmx(ans[rt],f[xo[u]]+dep[u]-(dep[rt]<<1));
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs3(t,u,rt);
    }
}
void dfs2(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa||t==son[u])   continue;
        dfs2(t,u);
        getmx(ans[u],ans[t]);
        count(t,u,0);
    }
    if(son[u]){dfs2(son[u],u);getmx(ans[u],ans[son[u]]);}
    for(int j=0;j<maxr;j++)
        getmx(ans[u],f[xo[u]^(1<<j)]-dep[u]);
    getmx(ans[u],f[xo[u]]-dep[u]);
    getmx(f[xo[u]],dep[u]);
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa||t==son[u])   continue;
        dfs3(t,u,u);
        count(t,u,1);
    }
}
int main(){
    memset(f,-0x3f,sizeof(f));
    cin>>n;
    for(int i=1,x;i<n;i++){
        char cx;
        cin>>x>>cx;
        add(x,i+1,1<<(cx-'a'));add(i+1,x,1<<(cx-'a'));
    }
    dfs1(1,0);
    // for(int i=1;i<=n;i++)   printf("%d ",xo[i]);puts("");
    dfs2(1,0);
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);
}