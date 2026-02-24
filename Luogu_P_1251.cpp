#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=4e3+10,inf=0x3f3f3f3f;
int N,p,m,f,n,s;
int a[maxn];
namespace Graph{
    const int maxm=maxn*10;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w,c;}e[maxm];
    inline void add(int u,int v,int w,int c){e[++cnt]={head[u],v,w,c};head[u]=cnt;}
    inline void adde(int u,int v,int w,int c){add(u,v,w,c);add(v,u,0,-c);}
}
using namespace Graph;
int S,T;
queue<int> q;
bool inque[maxn];
int lst[maxn],lsti[maxn],d[maxn];
ll flw[maxn];
bool bfs(){
    q.push(S);inque[S]=true;
    memset(d,0x3f,sizeof(d));memset(flw,0x3f,sizeof(flw));
    d[S]=lst[T]=0;
    while(!q.empty()){
        int u=q.front();
        inque[u]=false;
        q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(e[i].w&&d[u]+e[i].c<d[t]){
                flw[t]=min(1ll*e[i].w,flw[u]);
                d[t]=d[u]+e[i].c;
                lst[t]=u;lsti[t]=i;
                if(!inque[t]){q.push(t);inque[t]=true;}
            }
        }
    }
    return lst[T];
}
void MFMC(){
    ll cost=0;
    while(bfs()){
        // printf("%d %d\n",flw[T],d[T]);
        cost+=(flw[T]*d[T]);
        for(int p=T;p!=S;p=lst[p]){
            e[lsti[p]].w-=flw[T];e[lsti[p]^1].w+=flw[T];
        }
    }
    printf("%lld\n",cost);
}
int main(){
    scanf("%d",&N);
    T=N<<1|1;
    for(int i=1;i<=N;i++){
        scanf("%d",&a[i]);
        adde(S,i,a[i],0);  // i 为第 i 天的结束点
        adde(i+N,T,a[i],0);  // i+N 为第 i 天的开始点
    }
    scanf("%d%d%d%d%d",&p,&m,&f,&n,&s);
    for(int i=1;i<=N;i++){
        adde(S,i+N,inf,p);
        if(i+1<=N)  adde(i,i+1,inf,0);
        if(i+N+m<=2*N)  adde(i,i+N+m,inf,f);
        if(i+N+n<=2*N)  adde(i,i+N+n,inf,s);
    }
    MFMC();
}