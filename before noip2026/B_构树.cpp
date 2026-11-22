#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define pii pair<int,int>
#define piii pair<pii,int>
#define pll pair<ll,ll>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
namespace OIMATT{
    const int maxn=3e5+10;
    int n;
    namespace Graph{
        const int maxm=maxn<<1;
        #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
        int cnt=1;
        int head[maxn];
        struct edge{int nxt,to,w;}e[maxm];
        inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
        inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
        void rebuild(){fll(head,0,n);cnt=1;}
    }
    using namespace Graph;
    struct DSU{
        int fa[maxn];
        inline void init(){iota(fa,fa+n+1,0);}
        int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
        inline void merge(int x,int y){fa[find(y)]=find(x);}
        int operator[](int x){return find(x);}
    }U;
    int lm,RT;
    ll dep[maxn],mxd[maxn],D;
    int fw[maxn];
    pll mxx[maxn];
    vector<piii> ans;
    vector<pii> son[maxn];
    vector<int> Q[maxn];
    unordered_map<int,vector<int>> nw[maxn];
    bool vis[maxn];
    void dfs(int u,int ft){
        mxd[u]=0;
        for(auto [t,w]:son[u])if(t^ft){
            dep[t]=dep[u]+w;
            dfs(t,u);
            gmx(D,mxd[u]+mxd[t]+w);
            gmx(mxd[u],mxd[t]+w);
        }
    }
    vector<int> V;
    int dfs1(int u,int ft){
        V.eb(u);
        int mx=0;
        go(u,i)if((t^ft)&&(w<lm)){
            gmx(mx,w);
            gmx(mx,dfs1(t,u));
        }
        return mx;
    }
    void dfs2(int u,int ft){
        vis[u]=true;
        go(u,i)if((t^ft)&&(w<lm))dfs2(t,u);
    }
    void dfs3(int u,int ft){
        mxx[u]=pll(0,0);mxd[u]=0;
        for(auto [t,w]:son[u])if(t^ft){
            dep[t]=dep[u]+w;fw[t]=w;
            dfs3(t,u);
            gmx(mxd[u],mxd[t]+w);
            if(mxd[t]+w>mxx[u].fi)  mxx[u].se=mxx[u].fi,mxx[u].fi=mxd[t]+w;
            else    gmx(mxx[u].se,mxd[t]+w);
        }
    }
    void dfs4(int u,int ft){
        if(ft){
            ll len=(mxd[u]+fw[u]==mxx[ft].fi)?mxx[ft].se:mxx[ft].fi;
            len+=fw[u];
            if(len>mxx[u].fi)   mxx[u].se=mxx[u].fi,mxx[u].fi=len;
            else    gmx(mxx[u].se,len);
        }
        if(!RT||mxx[u].fi<mxx[RT].fi)   RT=u;
        for(pii t:son[u])if(t.fi^ft)dfs4(t.fi,u);
    }
    int dvd(int rt,int lim){
        lm=lim;
        V.clear();
        int mx=Q[rt].back();Q[rt].pop_back();
        if(!mx)return mxd[rt]=0,rt;
        vector<int> nw=OIMATT::nw[rt][mx];
        int p=0;
        for(int &i:nw){
            i=dvd(i,mx);
            if(!p||mxd[i]>mxd[p])   p=i;
        }
        for(int i:nw)if(p^i){
            ans.eb(pii(p,i),mx);
            son[p].eb(i,mx);son[i].eb(p,mx);
            gmx(mxd[p],mxd[i]+mx);
        }
        return p;
    }
    map<int,vector<pii>> E;
    void matt(int _c){
        D=0;rebuild();ans.clear();for(int i=1;i<=n;i++)son[i].clear(),nw[i].clear(),Q[i].clear();E.clear();
        cin>>n;
        for(int i=1;i<n;i++){int u,v,w;cin>>u>>v>>w;adde(u,v,w);E[w].eb(u,v);}
        for(int i=1;i<=n;i++)   Q[i].eb(0);
        U.init();
        for(auto [w,ve]:E){
            unordered_set<int> s,st;
            for(auto [u,v]:ve)  s.ep(U[u]),s.ep(U[v]);
            for(auto [u,v]:ve)  U.merge(u,v);
            for(int i:s)    nw[U[i]][w].eb(i),st.ep(U[i]);
            for(int i:st)   Q[i].eb(w);
        }
        dvd(U[1],1e9+10);
        dfs(1,0);
        cout<<D<<'\n';
        for(auto [ed,w]:ans)    cout<<ed.fi<<' '<<ed.se<<' '<<w<<'\n';
        // printf("%lld\n",D);
        // for(auto [ed,w]:ans)    printf("%d %d %d\n",ed.fi,ed.se,w);
    }
}
bool mem2;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=1;cin>>T;for(int i=1;i<=T;i++)OIMATT::matt(i);
}