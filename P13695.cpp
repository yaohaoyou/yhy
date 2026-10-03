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
const int maxn=1e4+10;
namespace Graph{
    const int maxm=1e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int dep[maxn],siz[maxn];
vector<int> v[maxn];
queue<int> q;
vector<int> label(int n,vector<pii> E,int T){
    for(auto [u,v]:E)   adde(u,v);
    q.ep(T);dep[T]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i)if(!dep[t]){
            dep[t]=dep[u]+1;
            q.ep(t);
        }
    }
    for(int i=1;i<=n;i++)   v[dep[i]].eb(i);
    fill(siz+1,siz+n+1,1);
    vector<int> ret(E.size());
    for(int i=n;i;i--){
        sort(v[i].begin(),v[i].end(),greater<int>());
        for(int u:v[i]){
            vector<pii> son;go(u,_)son.eb(t,(_>>1)-1);
            sort(son.begin(),son.end(),greater<pii>());
            for(auto [t,_]:son){
                if(dep[t]<dep[u])   ret[_]=u<t,siz[t]+=siz[u],siz[u]=0;
                else if(dep[t]==dep[u]&&u>t){
                    if(siz[t]>=siz[u])  ret[_]=0,siz[t]+=siz[u],siz[u]=0;
                    else    ret[_]=1,siz[u]+=siz[t],siz[t]=0;
                }
            }
        }
    }
    return ret;
}
int travel(int n,int u,vector<pii> son){
    int mx=0;
    for(auto [t,c]:son)if((u<t)==c)gmx(mx,t);
    return mx;
}
int main() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    std::vector<std::vector<std::pair<int,int>>> graph(n + 1);
    std::vector<std::pair<int, int>> edges(m);
    for(auto &[x, y] : edges) {
        std::cin >> x >> y;
    }
    std::vector<int> labels = label(n, edges, t);
    for(int i = 0; i < m; i++) {
        auto [x, y] = edges[i];
        graph[x].emplace_back(y, labels[i]);
        graph[y].emplace_back(x, labels[i]);
    }
    int curr_node = s;
    int moves = 0;
    while(curr_node != t) {
        moves++;
        int next_node = travel(n, curr_node, graph[curr_node]);
        std::cout << "Moving from " << curr_node << " to " << next_node << "\n";
        std::cout << "dep :  " << dep[curr_node]-1 << " to " << dep[next_node]-1 << "\n";
        curr_node = next_node;
    }
    std::cout << "Path length: " << moves << "\n";
    return 0;
}
