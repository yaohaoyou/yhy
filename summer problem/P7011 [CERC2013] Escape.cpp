#include<bits/stdc++.h>
#define int long long
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
const ll inf=1e18;
int n,T;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i,t) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)if(t^ft)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=1;i<=n+1;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
ll a[maxn];
set<pii> s[maxn];
inline void ins(int x,int y,int u){
    auto it=s[u].lower_bound(pii(x,y));
    if(it!=s[u].begin()){
        it--;
        if(it->se>=x){
            y=it->se-x+y,x=it->fi;
            it=s[u].erase(it);
        }
        else it++;
    }
    while(it!=s[u].end()&&it->fi<=y){
        auto [x2,y2]=*it;s[u].erase(it);
        y+=y2-x2;
        it=s[u].lower_bound(pii(x,y));
    }
    s[u].ep(x,y);
}
void dfs(int u,int ft){
    s[u].clear();
    go(u,i,t){
        dfs(t,u);
        if(s[u].size()<s[t].size()) s[u].swap(s[t]);
        for(auto [x,y]:s[t])    ins(x,y,u);
    }
    if(a[u]>0)  ins(0,a[u],u);
    else{
        int k=-a[u];
        auto it=s[u].begin();
        while(!s[u].empty()){
            auto [x,y]=*it;
            if(k+x<y){s[u].erase(it);ins(k+x,y,u);break;}
            else    k=k+x-y;
            it=s[u].erase(it);
        }
    }
    // printf("u = %d\n",u);for(auto [x,y]:s[u])printf("%d %lld\n",x,y);puts("");
}
void matt(){
    rebuild();
    scanf("%lld%lld",&n,&T);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);a[n+1]=inf;
    for(int i=1,u,v;i<n;i++){scanf("%lld%lld",&u,&v);adde(u,v);}
    adde(n+1,T);
    dfs(1,0);
    if(!s[1].empty()&&!s[1].begin()->fi&&s[1].begin()->se>=inf) puts("escaped");
    else    puts("trapped");
}
main(){int T;scanf("%lld",&T);while(T--)matt();}