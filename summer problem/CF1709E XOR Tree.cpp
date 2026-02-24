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
int a[maxn],dp[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int siz[maxn],son[maxn],dfsn[maxn],rnk[maxn];
bool slv[maxn];
int tot;
vector<int> tmp;
unordered_set<int> st;
void dfs(int u,int ft){
    siz[u]=1;
    dp[u]=dp[ft]^a[u];
    dfsn[u]=++tot;rnk[tot]=u;
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs3(int u,int ft){
    if(slv[u])  return;
    tmp.eb(dp[u]);
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs3(t,u);
    }
}
void dfs2(int u,int ft,bool keep){
    go(u,i){
        int t=e[i].to;
        if(t==ft||t==son[u])   continue;
        dfs2(t,u,false);
    }
    assert(st.empty());
    if(son[u])  dfs2(son[u],u,true);
    if(st.find(dp[u]^a[u])!=st.end()){slv[u]=true;st.clear();return;}
    st.ep(dp[u]);
    go(u,i){
        int t=e[i].to;
        if(t==ft||t==son[u])    continue;
        tmp.clear();
        dfs3(t,u);
        for(int j:tmp)
            if(st.find(j^a[u])!=st.end()){slv[u]=true;st.clear();break;}
        if(slv[u])  break;
        for(int j:tmp)  st.ep(j);
    }
    // printf("slv[%d] = %d\n",u,slv[u]);
    if(!keep)   st.clear();
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);dfs2(1,0,0);
    printf("%d\n",count(slv+1,slv+n+1,true));
}