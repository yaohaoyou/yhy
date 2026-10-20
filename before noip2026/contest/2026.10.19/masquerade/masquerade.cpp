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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e6+10;
int n,S,rt;
int son[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;son[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int tot;
int a[maxn],dep[maxn],s[maxn],fa[maxn],dfn[maxn];
namespace stLCA{
    int Log[maxn],st[22][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs1(int u,int ft){
        dep[u]=dep[fa[u]=ft]+1;
        st[0][dfn[u]=++tot]=ft;
        go(u,i)if(t^ft)dfs1(t,u);
    }
    void build(){
        dfs1(rt,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
bool bk[maxn];
int f[maxn];
void dfs(int u,int ft){
    if(u^rt)    s[u]=s[ft]+son[u]-1+(u==S);
    if(LCA(u,S)==u)    bk[u]=true;
    pii mx=pii(0,0);
    go(u,i)if(t^ft){
        dfs(t,u);
        if(f[t]>mx.fi)  mx.se=mx.fi,mx.fi=f[t];
        else    gmx(mx.se,f[t]);
    }
    f[u]=mx.se+son[u];
}
bool check(int x){
    int cnt=1;
    for(int u=S;u;u=fa[u],cnt++){
        int w=0;
        go(u,_)if(!bk[t]){
            if(s[u]+f[t]>x){
                cnt--;w++;
                if(cnt<0)return false;
            }
        }
        x-=w;
    }
    return x>=0;
}
bool mem2;
int main(){
    freopen("masquerade.in","r",stdin);freopen("masquerade.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&rt,&S);
    if(rt==S)   return puts("0"),0;
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)if(i^rt)son[i]--;
    stLCA::build();dfs(rt,0);
    int l=0,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else    l=mid+1;
    }
    printf("%d\n",ans);
}