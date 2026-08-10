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
const int maxn=2010;
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){cnt=1;for(int i=0;i<=n;i++)head[i]=deg[i]=0;}
}
using namespace Graph;
int fa[maxn],siz[maxn],ans[maxn];
void dfs(int u,int ft){
    siz[u]=1;fa[u]=ft;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
    }
}
void dfs2(int u,int ft,bool o){ans[u]=o;go(u,i)if(t^ft)dfs2(t,u,o);}
void dfs3(int u,int ft){
    ans[u]=true;k--;if(!k)return;
    go(u,i){
        if(t==ft)   continue;
        dfs3(t,u);
        if(!k)  return;
    }
}
void matt(){
    rebuild();fill(ans+1,ans+n+1,0);
    scanf("%d%d",&n,&k);
    for(int i=1,u,v;i<n;i++){scanf("%d%d",&u,&v);adde(u,v);}
    if(k==0){puts("1");for(int i=1;i<=n;i++)printf("0 ");puts("");return;}
    if(k==n){puts("1");for(int i=1;i<=n;i++)printf("1 ");puts("");return;}
    bool flag=false;
    for(int i=1;i<=n;i++){
        dfs(i,0);
        for(int j=1;j<=n;j++){
            if(siz[j]==k){
                dfs2(j,fa[j],1);
                flag=true;
                break;
            }
            if(siz[j]==n-k){
                fill(ans+1,ans+n+1,1);
                dfs2(j,fa[j],0);
                flag=true;
                break;
            }
        }
        if(flag)    break;
    }
    if(flag){
        puts("2");
        for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
        return;
    }
    puts("3");
    dfs3(1,0);
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}