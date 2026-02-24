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
const int maxn=1e5+10,maxm=4e5+10,maxd=100,mod=998244353;
bool mem1;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,q,out;
queue<int> que;
int ans[maxn],pq[maxn],ou[maxm];
struct EDGE{int u,v;stack<int> w;}E[maxm];
pii Q[maxm];
struct Graph{
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int id;
    int head[maxn];
    bool vis[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
    inline void merge(int u,int v){
        add(u,v);
        if(vis[u]&&!vis[v]){
            vis[v]=true;que.ep(v);
            while(!que.empty()){
                int x=que.front();que.pop();
                if(ans[x]<id){
                    mdel(out,immul(ans[x],pq[x]));
                    ans[x]=id;
                    madd(out,immul(ans[x],pq[x]));
                }
                go(x,i)if(!vis[t])vis[t]=true,que.ep(t);
            }
        }
    }
}G[maxd];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=100;i++)G[i-1].vis[1]=true,G[i-1].id=i;
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        E[i]={u,v};E[i].w.ep(w);
    }
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].fi,&Q[i].se),E[Q[i].fi].w.ep(E[Q[i].fi].w.top()-Q[i].se);
    for(int i=1;i<=m;i++){
        int u=E[i].u,v=E[i].v,w=E[i].w.top();
        for(int j=1;j<=w;j++)   G[j-1].merge(u,v);
    }
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    for(int i=2;i<=n;i++){
        for(int j=100;j;j--)if(G[j-1].vis[i]){ans[i]=j;break;}
        madd(out,immul(ans[i],pq[i]));
    }
    for(int i=q;i;i--){
        ou[i]=out;
        int x=Q[i].fi,u=E[x].u,v=E[x].v,lst=E[x].w.top();E[x].w.pop();
        int now=E[x].w.top();
        for(int j=lst+1;j<=now;j++) G[j-1].merge(u,v);
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ou[i]);
}