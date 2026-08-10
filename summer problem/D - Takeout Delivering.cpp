#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=3e5+10,maxm=1e6+10;
piii ee[maxm];
int n,m,k;
int f[2][maxn];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm<<1];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(int s,int o){
    mems(f[o],0x7f);q.ep(0,s);f[o][s]=0;
    while(!q.empty()){
        int u=q.top().se;q.pop();
        go(u,i){
            int t=e[i].to;
            if(f[o][t]>max(e[i].w,f[o][u])) f[o][t]=max(e[i].w,f[o][u]),q.ep(f[o][t],t);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);ee[i]=piii(pii(u,v),w);adde(u,v,w);}
    int ans=2e9;
    dijkstra(1,0);dijkstra(n,1);
    for(int i=1;i<=m;i++){
        auto [u,v]=ee[i].fi;
        if(max(f[0][u],f[1][v])!=f[0][0]&&max(f[0][u],f[1][v])<=ee[i].se)   ans=min(ans,max(f[0][u],f[1][v])+ee[i].se);
        if(max(f[1][u],f[0][v])!=f[0][0]&&max(f[1][u],f[0][v])<=ee[i].se)   ans=min(ans,max(f[1][u],f[0][v])+ee[i].se);
    }
    printf("%d\n",ans);
}