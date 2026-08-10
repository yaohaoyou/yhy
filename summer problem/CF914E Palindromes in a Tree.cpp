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
const int maxn=2e5+10,V='t'-'a';
int n;
char s[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
bool vis[maxn];
int all,rt;
int siz[maxn];
int w[maxn];
void dfs(int u,int ft){w[u]=w[ft]^(1<<s[u]-'a');go(u,i)if(t^ft)dfs(t,u);}
void getWC(int u,int ft){
    siz[u]=1;
    int mx=0;
    go(u,i){
        if(t==ft||vis[t])   continue;
        getWC(t,u);
        siz[u]+=siz[t];mx=max(mx,siz[t]);
    }
    mx=max(mx,all-siz[u]);
    if(mx<=all/2)   rt=u;
}
int mp[1<<V+1];
ll f[maxn],ans[maxn];
vector<int> subtr,clr;
void dfs1(int u,int ft,int fr){
    subtr.eb(u);clr.eb(w[u]);
    f[u]=0;
    for(int i=0;i<=V;i++)f[u]+=mp[w[u]^w[fr]^(1<<i)];
    f[u]+=mp[w[u]^w[fr]];
    go(u,i)if((t^ft)&&!vis[t])  dfs1(t,u,fr),f[u]+=f[t];
    ans[u]+=f[u];
}
vector<int> son;
void calc(int u){
    son.clear();go(u,i)if(!vis[t])son.eb(t);
    mp[w[u]]++;
    for(int t:son){dfs1(t,u,u);ans[u]+=f[t];for(int i:subtr)mp[w[i]]++;subtr.clear();}
    for(int i:clr)  mp[i]=0;clr.clear();mp[w[u]]=0;
    reverse(son.begin(),son.end());
    for(int t:son){dfs1(t,u,u);for(int i:subtr)mp[w[i]]++;subtr.clear();}
    for(int i:clr)  mp[i]=0;clr.clear();
}
void dfs2(int u,int ft){
    siz[u]=1;
    w[u]=w[ft]^(1<<s[u]-'a');
    go(u,i){
        if(t==ft||vis[t])   continue;
        dfs2(t,u);
        siz[u]+=siz[t];
    }
}
void divide(int u){
    vis[u]=true;
    dfs2(u,0);
    calc(u);
    // printf("u = %d,%d\n",u,n);
    // for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
    go(u,i){if(vis[t])continue;all=siz[t];rt=0;getWC(t,0);assert(rt);divide(rt);}
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    scanf("%s",s+1);
    dfs(1,0);
    all=n;getWC(1,0);divide(rt);
    for(int i=1;i<=n;i++)   printf("%lld ",ans[i]+1);
}