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
#define NO exit(puts("NO")&0)
using namespace std;
bool mem1;
const int maxn=3e5+10;
int n,m,k;
int G[maxn],p[maxn],q[maxn];
vector<int> son[maxn],v[maxn],sub[maxn];
unordered_set<int> B[maxn];
list<int> st;
bool vis[maxn];
int deg[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
bool chk(int rt){
    mems(deg,0);
    int siz=0;
    queue<int> q;
    for(int i=1;i<=n;i++)if(i^rt)deg[p[i]]++;
    for(int i=1;i<=n;i++)if(!deg[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        siz++;
        if(p[u]&&!(--deg[p[u]]))  q.ep(p[u]);
    }
    return siz^n;
}
bool mem2;
int main(){
    freopen("garbage.in","r",stdin);freopen("garbage.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&k);
    U.init();
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);u++;v++;if(G[u])NO;G[u]=v;p[u]=v;U.merge(v,u);}
    for(int i=1;i<=k;i++){int u,v;scanf("%d%d",&u,&v);u++;v++;B[u].ep(v);}
    if(chk(0))NO;
    list<int> RT;for(int i=1;i<=n;i++)if(!G[i])RT.eb(i),v[i].eb(i);
    queue<int> q;for(int i:RT)q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(v[u].empty())  continue;
        int bef=v[u].size();
        for(auto i=RT.begin();i!=RT.end();){
            int t=*i;
            if(u==t){i++;continue;}
            if(U[t]==u)  i=RT.erase(i);
            else{
                bool fl=false;
                for(int x:v[u]){for(int y:v[t])
                if(!B[y].count(x)&&!B[x].count(y)){
                // printf("# %d %d\n",x,y);
                    son[x].eb(y);son[y].eb(x);
                    fl=true;
                    i=RT.erase(i);
                    break;
                }if(fl)break;}
                if(fl){
                    U.merge(u,t);
                    if(v[u].size()<v[t].size())swap(v[u],v[t]);
                    for(int x:v[t])v[u].eb(x);
                    v[t].clear();
                }
                else    i++;
            }
        }
        if(v[u].size()^bef)q.ep(u);
    }
    function<void(int,int)> dfs=[&](int u,int ft){
        for(int t:son[u])if(t^ft){
            p[t]=u;
            dfs(t,u);
        }
    };
    for(int i=1;i<=n;i++)sub[U[i]].eb(i);
    for(int rt:RT){
        fll(vis,0,n);st.clear();
        for(int i:RT)if(i^rt)st.eb(i);
        queue<int> q;vis[rt]=true;::q[rt]=rt;
        for(int i:sub[rt])q.ep(i);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto it=st.begin();it!=st.end();){
                int x=*it;
                for(int i:v[x]){
                    if(!B[i].count(u)){
                        p[i]=u;::q[x]=i;vis[x]=true;it=st.erase(it);
                        for(int j:sub[x])q.ep(j);
                        break;
                    }
                }
                if(!vis[x]) it++;
            }
        }
        if(count(vis+1,vis+n+1,1)==RT.size()){
            for(int i:RT)   dfs(::q[i],0);
            for(int i=1;i<=n;i++)if(i^rt)printf("%d %d\n",i-1,p[i]-1);
            exit(0);
        }
    }
    NO;
}