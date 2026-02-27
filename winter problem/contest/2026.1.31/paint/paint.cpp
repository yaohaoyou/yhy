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
const int maxn=3e5+10;
int n,q;
int a[maxn],b[maxn];
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
void dfs(int u,int ft){
    a[u]=false;
    go(u,i)if(b[t]){a[u]=true;}
    go(u,i)if(t^ft)dfs(t,u);
}
int main(){
    freopen("paint.in","r",stdin);freopen("paint.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    while(q--){
        int op,u;scanf("%d",&op);
        if(op<=1){
            scanf("%d",&u);
            a[u]=op;
        }
        else{
            for(int i=1;i<=n;i++)b[i]=a[i];
            dfs(1,0);
        }
        printf("%d ",accumulate(a+1,a+n+1,0));
    }
}