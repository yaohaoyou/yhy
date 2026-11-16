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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e5+10;
int n;
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
inline int lowbit(int x){return x&-x;}
int ban[maxn],a[maxn];
void dfs(int u,int ft){
    int nd=0;
    go(u,i)if(t^ft){
        dfs(t,u);
        // nd|=(ban[u]&ban[t]);
        if(ban[u]&ban[t])   gmx(nd,__lg(ban[u]&ban[t])+1);
        ban[u]|=ban[t];
    }
    a[u]=__lg(lowbit((~ban[u])>>nd))+nd;
    ban[u]=(ban[u]>>a[u])<<a[u];ban[u]|=1<<a[u];
    // printf("a[%d] = %d %d\n",u,a[u],ban[u]);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    printf("%d\n",*max_element(a+1,a+n+1));
}