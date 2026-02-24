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
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
#define __div(u,s) all=s,findWC(u,0),divide(rt)
int all,rt;
bool bk[maxn];
int siz[maxn],dep[maxn],mx[maxn],c[maxn];
int ans[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void findWC(int u,int ft){
    siz[u]=1;
    int mx=0;
    go(u,i){
        if(t==ft||bk[t])    continue;
        findWC(t,u);
        siz[u]+=siz[t];
        mx=max(mx,siz[t]);
    }
    mx=max(mx,all-siz[u]);
    if(mx*2<=all)   rt=u;
}
void dfs1(int u,int ft){
    dep[u]=dep[ft]+1;siz[u]=1;
    go(u,i){
        if(t==ft||bk[t])    continue;
        dfs1(t,u);
        siz[u]+=siz[t];
    }
}
void dfs2(int u,int ft){
    c[siz[u]]=max(c[siz[u]],dep[u]);
    // gmx(ans[siz[u]<<1],dep[u]);
    go(u,i){
        if(t==ft||bk[t])    continue;
        dfs2(t,u);
    }
}
void divide(int u){
    bk[u]=true;
    dfs1(u,0);
    fill(mx,mx+siz[u]+1,1);
    go(u,_){
        if(bk[t])   continue;
        fill(c,c+siz[t]+1,0);
        all=siz[u]-siz[t];dfs2(t,u);
        for(int i=siz[t]-1;i;i--)   gmx(c[i],c[i+1]);
        for(int i=1;i<=siz[t];i++){
            gmx(ans[i<<1],mx[i]+c[i]-1);
            gmx(mx[i],c[i]);c[i]=0;
        }
    }
    fill(mx,mx+siz[u]+1,0);
    fill(c,c+siz[u]+1,0);
    go(u,_)if(!bk[t])__div(t,siz[t]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    fill(ans+1,ans+n+1,1);
    __div(1,n);
    for(int i=1;i<=n;i++)   printf("%d\n",ans[i]);
}