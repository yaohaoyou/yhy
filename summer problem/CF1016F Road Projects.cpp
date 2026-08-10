#include<bits/stdc++.h>
#define ll long long
#define int long long
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
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
int fa[maxn],siz[maxn];
ll dep[maxn];int onlst[maxn];
void dfs(int u,int ft){siz[u]=1;fa[u]=ft;go(u,i)if(t^ft){dep[t]=dep[u]+w;dfs(t,u);siz[u]+=siz[t];}}
main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<n;i++){int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);adde(u,v,w);}
    dfs(1,0);
    vector<int> lst,ss;lst.clear();ss.clear();
    ll res=-4e18,mx=-4e18;
    {
        int u=n;
        while(u){lst.eb(u);res=max(res,fa[fa[u]]?dep[fa[fa[u]]]-dep[u]:mx);if(siz[fa[u]]-siz[u]>=3){while(m--)printf("%lld\n",dep[n]);exit(0);};u=fa[u];}
        reverse(lst.begin(),lst.end());
        for(int i=0;i<lst.size();i++)   onlst[lst[i]]=i+1;
        for(int u:lst)
            go(u,i)if(!onlst[t])ss.eb(t);
    }
    for(int u:ss){
        res=max(res,mx+dep[u]-2*dep[fa[u]]);
        if(fa[u]^1) res=max(res,dep[fa[fa[u]]]+dep[u]-2*dep[fa[u]]);
        if(fa[u]^n) res=max(res,dep[u]-dep[fa[u]]-(dep[lst[onlst[fa[u]]]]-dep[fa[u]]));
        // printf("%lld %lld\n",u,mx+dep[u]-2*dep[fa[u]]);
        // printf("%d %d\n",u,res);
        mx=max(mx,dep[u]);
    }
    // printf("res = %lld\n",res);
    while(m--){
        int x;scanf("%lld",&x);
        printf("%lld\n",dep[n]+min(0ll,res+x));
    }
}