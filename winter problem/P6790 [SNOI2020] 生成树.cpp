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
const int maxn=6e5+10,mod=998244353;
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
int n,m;
int tot;
unordered_set<int> son[maxn];
unordered_map<int,int> mp[maxn];
int f[maxn],g[maxn];  // f[i] 表示连 i 这条边的方案数，g[i] 表示不连 i 这条边的方案数
queue<int> q;
inline pii get(int u,int v){if(u>v)swap(u,v);return pii(f[mp[u][v]],g[mp[u][v]]);}
inline void add(int u,int v){son[u].ep(v);son[v].ep(u);}
inline void adde(int u,int v,int ff,int gg){
    if(u>v)swap(u,v);
    if(mp[u].find(v)==mp[u].end()){
        add(u,v);add(v,u);
        mp[u][v]=++tot;
        f[tot]=ff;g[tot]=gg;
    }
    else{
        int x=mp[u][v];
        int fx=f[x],gx=g[x];
        f[x]=imadd(immul(fx,gg),immul(gx,ff));
        g[x]=immul(gx,gg);
    }
}
int ans=1;
void bfs(){
    for(int u=1;u<=n;u++)if(son[u].size()<3)q.ep(u);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(son[u].size()==1){
            int v=*son[u].begin();
            pii x=get(u,v);
            mmul(ans,x.fi);
        }
        if(son[u].size()==2){
            int x=*son[u].begin(),y=*next(son[u].begin());
            pii a=get(u,x),b=get(u,y);
            adde(x,y,immul(a.fi,b.fi),imadd(immul(a.fi,b.se),immul(a.se,b.fi)));
        }
        for(int t:son[u]){son[t].erase(u);if(son[t].size()==2)q.ep(t);}
        son[u].clear();
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v,1,1);}
    bfs();
    printf("%d\n",ans);
}