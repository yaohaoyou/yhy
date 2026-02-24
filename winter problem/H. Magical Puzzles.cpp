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
int n,m,tot;
bool cut[maxn];
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
int dfn[maxn];
ll dep[maxn];
namespace st_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
inline int getfa(int i){int x=e[i<<1].to,y=e[i<<1|1].to;return dep[x]<dep[y]?x:y;}
inline int getson(int i){int x=e[i<<1].to,y=e[i<<1|1].to;return dep[x]>dep[y]?x:y;}
void dfs(int u,int ft){
    dfn[u]=++tot;st_LCA::st[0][tot]=ft;
    go(u,i)if(t^ft)dep[t]=dep[u]+w,dfs(t,u);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    dfs(1,0);st_LCA::build();
    while(m--){
        int k,x,lca=0;scanf("%d",&k);
        vector<int> v,E;
        while(k--){
            scanf("%d",&x);E.eb(x);
            v.eb(getfa(x));v.eb(getson(x));
            lca=lca?LCA(lca,getfa(x)):getfa(x);
        }
        sort(v.begin(),v.end(),[&](int x,int y){return dfn[x]<dfn[y];});
        bool flag=true;
        for(int i=0;i+1<v.size();i++){
            int l=LCA(v[i],v[i+1]);
            if((l^v[i])&&(l^v[i+1])&&(l^lca)){flag=false;break;}
        }
        if(flag){
            
        }
        else{for(int j:E)cut[j]=true;}
    }
}