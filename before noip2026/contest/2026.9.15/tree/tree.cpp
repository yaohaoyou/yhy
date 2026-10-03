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
const int maxn=1e5+10;
int n;
int a[maxn],p[maxn];
bool b[maxn];
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
vector<int> v[maxn],rt[2],all;
bool mem2;
void dfs(int u,int rt){
    go(u,i){
        dfs(t,rt);
        a[u]+=a[t];
        if(!b[u]&&!b[t])    a[u]++,b[u]=b[t]=true;
        if(!b[t])   v[rt].eb(t);
    }
}
int main(){
    freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d",&p[i]);
        if(p[i])    add(p[i],i);
    }
    int ans=0;
    for(int i=n;i;i--)if(!p[i]){
        dfs(i,i);
        if(i^1) rt[b[i]].eb(i);
        else    rt[1].eb(i);
        ans+=a[i];
    }
    for(int i:rt[1]){
        p[i]=1;
        if(!b[i])   all.eb(i);
        for(int j:v[i]) all.eb(j);
    }
    // for(int i:v[1]) printf("%d ",i);puts("");
    // printf("ans = %d\n",ans);
    sort(rt[0].begin(),rt[0].end(),[&](int x,int y){return v[x].size()>v[y].size();});
    for(int u:rt[0]){
        if(!all.empty()){p[u]=all.back();all.pop_back();ans++;}
        else{
            p[u]=1;
            if(!b[u])   all.eb(u);
        }
        for(int i:v[u]) all.eb(i);
    }
    printf("%d\n",ans);
    for(int i=2;i<=n;i++)   printf("%d ",p[i]);
}