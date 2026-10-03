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
const int maxn=1e5+10,maxm=2e5+10,mod=998244353;
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
int n,m,k;
bool vis[maxn];
queue<int> st;
vector<pii> son[maxn];
vector<int> g[maxn];
queue<int> q;
stack<int> stk;bool ins[maxn],in[maxn];
int dfsn[maxn],low[maxn],scc[maxn],sz[maxn],tot,cscc;
int fac[maxn],inv[maxn];
void init(){
    const int N=1e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void tarjan(int u){
    stk.ep(u);ins[u]=true;
    dfsn[u]=low[u]=++tot;
    for(auto [t,_]:son[u]){
        if(!dfsn[t]){tarjan(t);low[u]=min(low[u],low[t]);}
        else if(ins[t]) low[u]=min(low[u],dfsn[t]);
    }
    if(dfsn[u]==low[u]){
        int p=0;
        cscc++;
        do{
            p=stk.top();stk.pop();
            ins[p]=false;scc[p]=cscc;
            sz[cscc]++;
        }while(p^u);
    }
}
ll ans;
bool mem2;
void dfs(int x,ll w,int s){
    if(x>n){
        // if(w)printf("%lld\n",w);
        q=st;
        mems(vis,0);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int t:g[u])if(!vis[t])vis[t]=true,q.ep(t);
        }
        if(count(vis+1,vis+n+1,1)==n-k)ans=w;
        return;
    }
    if(s&(1<<x-1)) return dfs(x+1,w,s);
    // dfs(x+1,w*(int)son[x].size(),s);
    for(pii i:son[x])if(w+i.se<ans)g[i.fi].eb(x),dfs(x+1,w+i.se,s),g[i.fi].pop_back();
}
void data(){
    n=15;m=30;k=10;
    srand(time(0));
    printf("%d %d %d\n",n,m,k);
    for(int i=1;i<=n;i++)printf("%d %d %d\n",i,rand()%n+1,rand());
    for(int i=1;i<=m-n;i++)printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand());
    exit(0);
}
int main(){
    // freopen("station.in","r",stdin);freopen("station.out","w",stdout);
    init();
    // data();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&k);
    if(k==n)    return puts("0"),0;
    bool W1=1;
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);son[u].eb(v,w);g[v].eb(u);W1&=(w==1);}
    {
        for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
        for(int u=1;u<=n;u++){
            for(int t:g[u])if(scc[u]^scc[t])in[scc[t]]=true;
            g[u].clear();
        }
        int mn=1e9;
        for(int i=1;i<=cscc;i++)if(!in[i])gmn(mn,sz[i]);
        printf("%d\n",n-mn+1);
        if(k<n-mn+1)    return puts("-1"),0;
    }
    debug("nboj\n");
    if(W1)  return printf("%d\n",n-k),0;
    int out=0,cnt=0;
    for(int i=0;i<(1<<n);i++){
        if(__builtin_popcount(i)!=k)    continue;
        while(!st.empty())st.pop();
        for(int j=1;j<=n;j++)if(i&(1<<j-1))st.ep(j);
        ans=1e18;
        dfs(1,0,i);
        if(ans==1e18)    return puts("-1"),0;
        // printf("%d : %d\n",i,ans);
        cnt++;madd(out,ans%mod);
    }
    printf("%d\n",immul(out,qpow(cnt,mod-2)));
}