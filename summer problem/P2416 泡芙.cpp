#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=3e5+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
vector<pii> son[maxn];
int tot;
int dfsn[maxn],low[maxn],bel[maxn],s[maxn];
vector<int> bcc[maxn];
set<piii> E;
int cbcc;
stack<int> stk;
void tarjan(int u,int fr){
    stk.ep(u);
    dfsn[u]=low[u]=++tot;
    go(u,i){
        if(!dfsn[t]){tarjan(t,i);low[u]=min(low[u],low[t]);}
        else if(i^fr^1) low[u]=min(low[u],dfsn[t]);
    }
    if(low[u]==dfsn[u]){
        int p=0;
        cbcc++;
        do{p=stk.top();stk.pop();bcc[cbcc].eb(p);bel[p]=cbcc;}while(p^u);
    }
}
int sum[maxn];
namespace st_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void dfs1(int u,int ft,int ss){
        sum[u]+=s[u]+ss;
        st[0][dfsn[u]=++tot]=ft;
        for(auto [t,w]:son[u]){
            if(t==ft)   continue;
            dfs1(t,u,sum[u]+w);
        }
    }
    void build(){
        mems(dfsn,0);tot=0;dfs1(1,0,0);
        for(int i=2;i<=tot;i++) Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[tot];i++)
            for(int j=1;j+(1<<i)-1<=tot;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    tarjan(1,0);
    for(int u=1;u<=n;u++)
        go(u,i)
            if(bel[u]^bel[t])E.ep(bel[u],pii(bel[t],w));
            else    s[bel[u]]+=w;
    for(auto [u,vw]:E)  son[u].eb(vw);
    st_LCA::build();
    // for(int i=1;i<=cbcc;i++,puts("")){
    //     printf("%d %d\n",s[i],sum[i]);
    //     for(int j:bcc[i])   printf("%d ",j);
    // }
    int q;scanf("%d",&q);
    while(q--){
        int u,v;scanf("%d%d",&u,&v);
        u=bel[u];v=bel[v];
        if(sum[u]+sum[v]-2*sum[LCA(u,v)]+s[LCA(u,v)]>0) puts("YES");
        else    puts("NO");
    }
}