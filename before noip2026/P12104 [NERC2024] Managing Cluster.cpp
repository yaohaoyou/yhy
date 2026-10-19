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
const int maxn=2e5+10;
bool mem1;
int n;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int f[maxn][2],nx[maxn],bel[maxn],c[maxn];
bool used[maxn];
pii b[maxn];
vector<pii> vec;
void dfs(int u,int ft){
    f[u][0]=f[u][1]=0;
    pii mx=pii(-1e9,0);
    go(u,i)if(t^ft){
        dfs(t,u);
        f[u][0]+=max(f[t][0],f[t][1]);
        mx=max(mx,pii(f[t][0]-max(f[t][0],f[t][1]),t));
    }
    f[u][1]=f[u][0]+mx.fi+1;
    nx[u]=mx.se;
}
void dfs2(int u,int ft,bool o){
    if(o&&nx[u]){
        vec.eb(u,nx[u]);
        bel[u]=bel[nx[u]]=vec.size();
        dfs2(nx[u],u,0);
    }
    go(u,i)if(t^ft){
        if(o&&(t==nx[u]))   continue;
        dfs2(t,u,1);
    }
}
set<int> C1;
vector<pii> ans;
inline int oth(int x){return b[a[x]].fi==x?b[a[x]].se:b[a[x]].fi;}
void swp(int u,int v){
    if(u^v){
        // printf("swp %d %d\n",u,v);
        if(c[a[u]]==1){if(!bel[u])C1.erase(u);else C1.erase(oth(u));}
        if(c[a[v]]==1){if(!bel[v])C1.erase(v);else C1.erase(oth(v));}
        if(bel[u])c[a[u]]--;if(bel[v])c[a[v]]--;
        ans.eb(u,v);
        if(b[a[u]].fi==u)   b[a[u]].fi=v;
        else    b[a[u]].se=v;
        if(b[a[v]].fi==v)   b[a[v]].fi=u;
        else    b[a[v]].se=u;
        swap(a[u],a[v]);
        if(bel[u])c[a[u]]++;if(bel[v])c[a[v]]++;
        if(c[a[u]]==1){if(!bel[u])C1.ep(u);else C1.ep(oth(u));}
        if(c[a[v]]==1){if(!bel[v])C1.ep(v);else C1.ep(oth(v));}
    }
}
bool mem2;
void matt(int _cases){
    rebuild();vec.clear();ans.clear();C1.clear();for(int i=1;i<=n;i++)b[i]=pii(0,0),c[i]=bel[i]=0;
    scanf("%d",&n);n<<=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(!b[a[i]].fi) b[a[i]].fi=i;
        else    b[a[i]].se=i;
    }
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    dfs2(1,0,f[1][0]<f[1][1]);
    // if(_cases==87)  printf("# %d\n",max(f[1][1],f[1][0]));
    // for(auto [i,j]:vec)printf("%d %d\n",i,j);
    for(auto [i,j]:vec) c[a[i]]++,c[a[j]]++;
    for(int i=1;i<=n;i++)if(c[a[i]]==1&&!bel[i])C1.ep(i);
    int i=0,j=0;
    while(i<vec.size()){
        // printf("! %d %d\n",i,j);
        // for(int i:C1)   printf("%d ",i);puts("");
        // for(int k=1;k<=n;k++)   printf("%d ",a[k]);puts("");
        int u=vec[i].fi,v=vec[i].se;
        int x=oth(u);
        if(x^v){
            swp(x,v);
            if(bel[x]){
                i=bel[x]-1;
                if(vec[i].se==x)    swap(vec[i].fi,vec[i].se);
                continue;
            }
            int y=oth(x);
            if(bel[y]){
                assert(C1.size()>=2);
                int k=*C1.begin();if(k==x)k=*prev(C1.end());
                i=bel[y]-1;
                if(vec[i].se==y)    swap(vec[i].fi,vec[i].se);
                swp(y,k);
                continue;
            }
        }
        while(j<vec.size()&&a[vec[j].fi]==a[vec[j].se])j++;
        i=j;
    }
    for(int i=0;i<vec.size();i++)   assert(a[vec[i].fi]==a[vec[i].se]);
    printf("%d\n",ans.size());for(auto [i,j]:ans)printf("%d %d\n",i,j);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}