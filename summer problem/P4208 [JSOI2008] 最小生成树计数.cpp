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
const int maxn=110,maxm=1010;
int n,m;
map<int,vector<pii>> mp;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int tmp[maxn];
vector<pii> vv;
int main(){
    scanf("%d%d",&n,&m);
    U.init();
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);mp[w].eb(u,v);U.merge(u,v);}
    for(int i=1;i<=n;i++)if(U[i]^U[1])return puts("0"),0;
    U.init();
    int ans=1;
    for(auto [_,vec]:mp){
        vv.clear();
        for(auto [u,v]:vec)if(U[u]==U[v])continue;else vv.eb(u,v);
        if(vv.empty())  continue;
        memc(tmp,U.fa);
        int nd=0;for(auto [u,v]:vec)if(U[u]^U[v])nd++,U.merge(u,v);
        int res=0;
        for(int i=0;i<(1<<vv.size());i++){
            int edg=0;memc(U.fa,tmp);
            for(int j=0;j<vv.size();j++)if(i&(1<<j)){
                auto [u,v]=vv[j];
                if(U[u]^U[v])   U.merge(u,v),edg++;
                else{edg=0;break;}
            }
            if(edg==nd)    res++;
        }
        for(auto [u,v]:vec)U.merge(u,v);
        assert(res);
        (ans*=res)%=31011;
    }
    printf("%d\n",ans);
}