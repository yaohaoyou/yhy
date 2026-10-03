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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3e5+10,maxm=maxn<<1;
int n;
#define go(o,x,i) for(int i=T[o].head[x],t=T[o].e[i].to;i;i=T[o].e[i].nxt,t=T[o].e[i].to)
struct Graph{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}T[2];
int ans;
int L[maxn],R[maxn],rnk[maxn],tot;
set<pii> st;
void dfs(int u,int ft){
    rnk[L[u]=++tot]=u;
    go(1,u,i)if(t^ft)dfs(t,u);
    R[u]=tot;
}
void dfs2(int u,int ft){
    auto it=st.lower_bound(pii(L[u],0));
    bool ins=false;pii era=pii(0,0);
    if(it==st.end()||it->fi>R[u]){
        it=st.lower_bound(pii(L[u],1e9));
        if(it!=st.begin()&&(--it)->se>=R[u])era=*it,st.erase(it);
        st.ep(L[u],R[u]);ins=true;
    }
    gmx(ans,st.size());
    go(0,u,i)if(t^ft)dfs2(t,u);
    if(ins){
        st.erase(pii(L[u],R[u]));
        if(era.fi)  st.ep(era);
    }
}
void matt(int _cases){
    T[0].rebuild();T[1].rebuild();st.clear();ans=tot=0;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);T[0].add(x,i);}
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);T[1].add(x,i);}
    dfs(1,0);dfs2(1,0);
    printf("%d\n",ans);
}
bool mem2;
int main(){debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}