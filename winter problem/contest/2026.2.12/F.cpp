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
const int maxn=2e5+10;
bool mem1;
int n,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=deg[i]=0;cnt=1;}
}
using namespace Graph;
int tot;
int dfn[maxn],fa[20][maxn],dep[maxn],sum[maxn];
ll siz[maxn];
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
bool mem2;
void dfs1(int u,int ft){
    fa[0][u]=st_LCA::st[0][dfn[u]=++tot]=ft;dep[u]=dep[ft]+1;
    siz[u]=1;
    sum[u]=sum[ft]+(deg[u]>2);
    go(u,i)if(t^ft)dfs1(t,u),siz[u]+=siz[t];
}
inline int jump(int x,int d){while(d){x=fa[__lg(d&-d)][x];d^=(d&-d);}return x;}
inline ll slr(int l,int r){return l>r?0:1ll*(l+r)*(r-l+1)/2;}
void matt(int _cases){
    tot=0;rebuild();
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);st_LCA::build();
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    while(q--){
        int u,v;scanf("%d%d",&u,&v);
        if(fa[0][v]==u){
            ll ans=1ll*n*(n-1);
            ans-=siz[v]*(n-siz[v])*2;
            ans-=n-siz[v]-1;
            printf("%lld\n",ans);
            continue;
        }
        if(fa[0][u]==v){
            ll ans=1ll*n*(n-1);
            ans-=siz[u]*(n-siz[u])*2;
            ans-=siz[u]-1;
            printf("%lld\n",ans);
            continue;
        }
        int l=LCA(u,v);
        int dd;
        if(u==1)    dd=sum[fa[0][v]]-sum[u];
        else if(v==1)    dd=sum[fa[0][u]]-sum[v];
        else dd=sum[fa[0][u]]+sum[fa[0][v]]-(sum[l]<<1)+(deg[l]>2);
        debug("dd = %d\n",dd);
        ll ans=1ll*n*(n-1);
        if(!dd){
            int len=dep[u]+dep[v]-(dep[l]<<1)+1;
            if(l==u){
                int jp=jump(v,dep[v]-dep[u]-1);
                ans-=siz[v]*(siz[u]-siz[jp])*2;
                ans-=n-siz[v]-1;
                ans-=(len-2)*(siz[u]-siz[jp]);
            }
            else if(l==v){
                int jp=jump(u,dep[u]-dep[v]-1);
                ans-=siz[u]*(siz[v]-siz[jp])*2;
                ans-=n-1-(siz[v]-siz[jp]);
                ans-=(len-2)*(siz[v]-siz[jp]);
            }
            else{
                ans-=siz[u]*siz[v];
                ans-=n-1-siz[v];
                // puts("nboj");
            }
            // [2,len/2]
            // printf("len = %d %lld\n",len,slr(1,len-(len+1)/2+1));
            ans-=slr(1,len-1-(len+1)/2+1);
            printf("%lld\n",ans);
            continue;
        }
        puts("-1");
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}