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
const int maxn=3e5+10;
bool mem1;
int n;
int ls[maxn],rs[maxn],fa[maxn];
ll f[maxn],g[maxn];
void dfs(int u){
    if(!ls[u])  return f[u]=0,void();
    dfs(ls[u]);dfs(rs[u]);
    f[u]=f[ls[u]]+f[rs[u]]+4;
}
void dfs2(int u){g[u]=f[u]+1+g[fa[u]];if(!ls[u])return;dfs2(ls[u]);dfs2(rs[u]);}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&ls[i],&rs[i]);
        fa[ls[i]]=fa[rs[i]]=i;
    }
    dfs(1);dfs2(1);
    for(int i=1;i<=n;i++)printf("%lld ",g[i]);puts("");
}
int main(){freopen("lost.in","r",stdin);freopen("lost.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}