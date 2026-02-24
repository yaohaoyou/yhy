#pragma GCC optimize(2,3,"Ofast")
#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<random>
#include<cstdio>
#include<vector>
#include<cassert>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define ep emplace
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char ch=getchar();int f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+10,maxq=3e5+10,mod=998244353;
int n,m,q,B,d[N],vis[N];
vector<int> g[N];
pii Q[maxq];
vector<int> vq[N];
vector<int> vec[N];
int bel[N];
bool ans[maxq];
int lst[N];
mt19937 rd(time(0));
void dfs(int u,int x){
    bel[u]=x;
    vis[u]=true;vec[x].eb(u);
    for(int t:g[u]){
        if(vis[t])  continue;
        dfs(t,x);
    }
}
void misaka(int _ID){
    double sta=clock();
    n=read(),m=read(),q=read();
    rep(i,1,m){
        int u=read(),v=read();
        g[u].eb(v);g[v].eb(u);
    }
    int cur=0;
    for(int i=1;i<=n;i++)if(!vis[i])dfs(i,++cur),lst[cur]=vec[cur].size();
    for(int i=1;i<=q;i++){
        int u=read(),v=read();
        Q[i]=pii(u,v);
        if(bel[u]!=bel[v])  ans[i]=0;
        else vq[bel[u]].eb(i);
    }
    for(int i=1;i<=n;i++)   vis[i]=false;
    while((clock()-sta)/CLOCKS_PER_SEC<2.25){
        for(int o=1;o<=cur;o++){
            if(!lst[o]||vq[o].empty()) continue;
            lst[o]--;
            int y=rd()%vec[o].size(),x=vec[o][y];
            while(vis[x])   y=rd()%vec[o].size(),x=vec[o][y];
            vis[x]=1;
            rep(j,1,n) d[j]=1e9;
            d[x]=0;queue<int> q;q.ep(x);
            while(q.size()){
                int u=q.front();q.pop();
                for(int v:g[u])if(d[v]==1e9)
                d[v]=d[u]+1,q.ep(v);
            }
            vector<int> nw;nw.clear();
            for(int i:vq[o])if(d[Q[i].fi]+d[Q[i].se]<=20000)ans[i]=true;else nw.eb(i);
            vq[o].swap(nw);
        }
    }
    for(int i=1;i<=q;i++)   puts(ans[i]?"NO":"YES");
}
bool __ed;
signed main(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    rep(i,1,T) misaka(i);
    return 0;
}