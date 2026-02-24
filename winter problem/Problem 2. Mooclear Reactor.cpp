#include<bits/stdc++.h>
#define db double
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
const int maxn=4e5+10;
int n,m;
bool _return;
int rt;
int l[maxn],r[maxn],a[maxn];
bool vis[maxn];
vector<int> v[maxn];
unordered_map<int,int> mp[maxn];
map<int,int> M;
pii k[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
void dfs(int x){
    vis[x]=true;
    for(auto [t,s]:mp[x]){
        pii nd=pii(-k[x].fi,s-k[x].se);
        if(!k[t].fi){
            k[t]=nd;
            if(!vis[t])dfs(t);
        }
        else if(k[t].fi==nd.fi&&k[t]!=nd)   return _return=true,void();
        else if(k[t].fi+nd.fi==0){
            if(nd.fi==1)    swap(nd,k[t]);
            if((nd.se-k[t].se)&1)   return _return=true,void();
            a[t]=(nd.se-k[t].se)/2;
            rt=t;
        }
    }
}
void dfs2(int x){
    vis[x]=true;
    for(auto [t,s]:mp[x]){
        if(!vis[t]){
            a[t]=s-a[x];
            dfs2(t);
        }
        else if(a[t]+a[x]!=s)   return _return=true,void();
    }
}
void matt(int _cases){
    for(int i=1;i<=n;i++)mp[i].clear(),v[i].clear(),k[i]=pii(0,0),a[i]=0;
    mems(vis,0);_return=false;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&l[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&r[i]);
    U.init();
    for(int i=1;i<=m;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        if(mp[x].find(y)!=mp[x].end()&&(mp[x][y]^z))    _return=true;
        mp[x][y]=z;mp[y][x]=z;
        U.merge(x,y);
    }
    if(_return) return puts("-1"),void();
    for(int i=1;i<=n;i++)   v[U[i]].eb(i);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(U[i]^i)  continue;
        k[i]=pii(1,0);rt=0;dfs(i);
        if(_return) return puts("-1"),void();
        if(rt){
            for(int j:v[i])vis[j]=false;
            a[i]=a[rt];
            dfs2(i);
            // for(int j:v[i]) printf("%.1f %d\n",a[j],j);
            if(_return)   return puts("-1"),void();
            for(int j:v[i]) ans+=(a[j]>=l[j]&&a[j]<=r[j]);
            continue;
        }
        M.clear();
        for(int j:v[i]){
            if(k[j].fi==1)  M[l[j]-k[j].se]++,M[r[j]-k[j].se+1]--;
            else M[k[j].se-r[j]]++,M[k[j].se-l[j]+1]--;
        }
        int now=0,res=0;
        for(auto [j,k]:M)   now+=k,res=max(res,now);
        ans+=res;
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}