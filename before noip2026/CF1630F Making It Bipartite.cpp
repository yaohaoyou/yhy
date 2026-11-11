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
const int maxn=2e5+10,inf=1e9;
bool mem1;
int n,tot,S,T;
int a[maxn],b[maxn];
int I[maxn],O[maxn],L[maxn],R[maxn];  // I : 没有入边，O : 没有出边
namespace Graph{
    const int maxm=maxn*200;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    #define gonow(x,i) for(int i=now[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn],now[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
    inline void rebuild(){for(int i=0;i<=tot;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
bool ntp[maxn];
int fac[maxn];
void init(){
    n=2e5;
    vector<int> p;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) p.eb(i),fac[i]=i;
        for(int j:p){
            if(i*j>n)   break;
            ntp[i*j]=true;fac[i*j]=j;
            if(i%j==0)  break;
        }
    }
}
inline void ade(int x,int y){adde(L[x],R[y],1);}
ll d[maxn];
queue<int> q;
bool bfs(){
    while(!q.empty())q.pop();
    fll(d,-1,tot);cpy(now,head,tot);
    d[S]=0;q.ep(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i)if(w&&!(~d[t])){
            d[t]=d[u]+1;
            if(t==T)    return true;
            q.ep(t);
        }
    }
    return ~d[T];
}
int dinic(int u,int flw){
    if(u==T)    return flw;
    int res=flw;
    gonow(u,i)if(w&&d[t]==d[u]+1){
        now[u]=e[i].nxt;
        int fl=dinic(t,min(w,res));
        if(!fl)  d[t]=-1;
        else{
            e[i].w-=fl;e[i^1].w+=fl;res-=fl;
            if(!res)    break;
        }
    }
    if(flw==res)    d[u]=-1;
    return flw-res;
}
int dinic(){
    int fl=0;
    while(bfs())   fl+=dinic(S,inf);
    return fl;
}
int TT;
bool mem2;
void matt(int _cases){
    rebuild();tot=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[a[i]]=i;
        I[i]=(i<<1)-1;O[i]=i<<1;
        L[I[i]]=++tot;R[I[i]]=++tot;
        L[O[i]]=++tot;R[O[i]]=++tot;
        ade(O[i],I[i]);  // 如果是 ade(I[i],O[i]) 会成环
    }
    for(int i=1;i<=n;i++){
        int x=a[i];
        vector<pii> v;
        while(x^1){
            if(!v.empty()&&v.back().fi==fac[x]) v.back().se++;
            else    v.eb(fac[x],1);
            x/=fac[x];
        }
        function<void(int,int)> dfs=[&](int x,int y){
            if(x==v.size()){
                if(y!=a[i]&&b[y]){
                    ade(O[i],I[b[y]]);
                    ade(O[i],O[b[y]]);
                    ade(I[i],I[b[y]]);
                }
                return;
            }
            for(int i=0;i<=v[x].se;i++){
                dfs(x+1,y);
                y*=v[x].fi;
            }
        };
        dfs(0,1);
    }
    S=0;T=++tot;
    for(int i=1;i<=n+n;i++) adde(S,L[i],1),adde(R[i],T,1);
    printf("%d\n",n-(n+n-dinic()));
    for(int i=1;i<=n;i++)   b[a[i]]=0;
}
int main(){init();debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);scanf("%d",&TT);for(int i=1;i<=TT;i++)matt(i);}