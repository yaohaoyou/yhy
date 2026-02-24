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
const int maxm=maxn<<1;
int n,m;
struct Graph{
    #define go(o,x,i) for(int i=G[o].head[x];i;i=G[o].e[i].nxt)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}G[2];
queue<int> q;vector<int> top;
int f[maxn],g[maxn],tp[maxn];
char ans[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);G[0].add(u,v);G[1].add(v,u);}
    for(int i=1;i<=n;i++)
        if(!G[0].deg[i])    q.ep(i);
    iota(f+1,f+n+1,1);iota(g+1,g+n+1,1);
    while(!q.empty()){
        int u=q.front();q.pop();top.eb(u);
        go(0,u,i){
            int t=G[0].e[i].to;
            if(!(--G[0].deg[t]))    q.ep(t);
        }
    }
    if(top.size()^n)    return puts("-1"),0;
    for(int u:top){
        go(1,u,i){
            int t=G[1].e[i].to;
            f[u]=min(f[u],f[t]);
        }
    }
    reverse(top.begin(),top.end());
    for(int u:top){
        go(0,u,i){
            int t=G[0].e[i].to;
            g[u]=min(g[u],g[t]);
        }
    }
    for(int i=1;i<=n;i++)   ans[i]='E';
    // for(int i=1;i<=n;i++)   printf("%d %d %d\n",i,f[i],g[i]);
    for(int i=1;i<=n;i++)
        if(f[i]==g[i]&&f[i]==i) ans[i]='A';
    printf("%d\n",count(ans+1,ans+n+1,'A'));
    for(int i=1;i<=n;i++)   printf("%c",ans[i]);
}