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
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int siz[maxn],buc[maxn];
void dfs(int u,int fa){
    siz[u]=1;
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
    }
    buc[siz[u]]++;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    for(int i=n-1;i;i--){
        if(n%i)  continue;
        int cnt=0;
        for(int j=i;j<=n;j+=i)  cnt+=buc[j];
        if(cnt==n/i)    printf("%d ",n/i-1);
    }
}