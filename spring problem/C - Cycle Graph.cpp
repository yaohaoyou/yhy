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
const int maxn=2e5+10;
int n,m,deg[maxn];
struct DSU{
    int fa[maxn];
    void init(){for(int i=1;i<=n;i++)fa[i]=i;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void merge(int x,int y){fa[find(y)]=find(x);}
}U;
int main(){
    scanf("%d%d",&n,&m);
    U.init();
    if(n^m)exit(puts("No")&0);
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);deg[u]++;deg[v]++;
        U.merge(u,v);
    }
    for(int i=1;i<=n;i++)
        if(deg[i]!=2)   exit(puts("No")&0);
    for(int i=1;i<=n;i++)
        if(U.find(i)!=U.find(1))    exit(puts("No")&0);
    puts("Yes");
}