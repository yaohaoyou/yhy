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
bool mem1;
const int maxn=3e5+10;
int n,q;
pii a[maxn];
int ans[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
bool vis[maxn];
int dfn[maxn],rnk[maxn],tot;
int w[maxn],now[maxn];
void dfs(int u){rnk[dfn[u]=++tot]=u;vis[u]=true;go(u,i)if(!vis[t])dfs(t);}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++)   scanf("%d%d",&a[i].fi,&a[i].se),adde(a[i].fi,a[i].se);
    for(int _=1;_<=n;_++)if(!vis[_]){
        tot=0;dfs(_);
        for(int i=tot;i;i--){
            int u=rnk[i],deg=0,d=0,o=0;
            go(u,__)if(!ans[__>>1])deg++;else if(ans[__>>1]==u)o++;
            go(u,__)if(!ans[__>>1]){
                d++;
                if(((o+deg)&1)&&(d==deg))   ans[__>>1]=t;
                else    ans[__>>1]=u;
            }
        }
    }
    for(int i=1;i<=q;i++)   w[ans[i]]++;
    for(int i=1;i<=q;i++){
        if(ans[i]==a[i].fi) putchar('x');
        else putchar('y');
        if(now[ans[i]]>=(w[ans[i]]+1)/2) putchar('-'),now[ans[i]]++;
        else    putchar('+'),now[ans[i]]++;
        puts("");
    }
}