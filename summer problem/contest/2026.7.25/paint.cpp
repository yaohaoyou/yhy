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
const int maxn=3e5+10;
int n,m;
int a[maxn];pii E[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
bool dfs(int x){
    if(x>n){
        U.init();
        for(int i=1;i<=m;i++){
            auto [u,v]=E[i];
            if(a[u]!=a[v])  U.merge(u,v);
        }
        for(int i=2;i<=n;i++)if(U[i]!=U[1])return false;
        int c0=count(a+1,a+n+1,0),c1=count(a+1,a+n+1,1),c2=n-c0-c1;
        if(c0==n/3&&c1==n/3){
            for(int i=1;i<=n;i++)if(!a[i])putchar('R');else if(a[i]==1)putchar('G');else putchar('B');puts("");
            return true;
        }
        if(c0>max(c1,c2)){
            for(int i=1;i<=m;i++){
                auto [u,v]=E[i];
                if(!a[u]&&!a[v])    return false;
            }
            for(int i=1;i<=n;i++)if(!a[i])putchar('R');else if(a[i]==1)putchar('G');else putchar('B');puts("");
            return true;
        }
        if(c1>max(c0,c2)){
            for(int i=1;i<=m;i++){
                auto [u,v]=E[i];
                if(a[u]==1&&a[v]==1)    return false;
            }
            for(int i=1;i<=n;i++)if(!a[i])putchar('R');else if(a[i]==1)putchar('G');else putchar('B');puts("");
            return true;
        }
        if(c2>max(c0,c1)){
            for(int i=1;i<=m;i++){
                auto [u,v]=E[i];
                if(a[u]==2&&a[v]==2)    return false;
            }
            for(int i=1;i<=n;i++)if(!a[i])putchar('R');else if(a[i]==1)putchar('G');else putchar('B');puts("");
            return true;
        }
        return false;
    }
    for(int i=0;i<=2;i++){a[x]=i;if(dfs(x+1))return true;}return false;
}
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&E[i].fi,&E[i].se);
    if(!dfs(1)) puts("-1");
}
int main(){freopen("paint.in","r",stdin);freopen("paint.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}