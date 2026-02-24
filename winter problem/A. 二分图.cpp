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
const int maxn=2e4+10;
int n,m;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
int deg[maxn];
vector<int> v[maxn];
int main(){
    scanf("%d%d",&n,&m);
    U.init();
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        deg[u]++;deg[v+n]++;
        // printf("%d %d\n",u,v+n);
        U.merge(u,v+n);
    }
    for(int i=1;i<=n+n;i++)v[U.find(i)].eb(i);
    int ans=0;bool flag=true;
    int cc[2]={0,0};
    for(int i=1;i<=n+n;i++){
        if(v[i].size()<=1)    continue;
        // int res=0;
        int c[2]={0,0};
        for(int j:v[i])c[j>n]+=(deg[j]&1);
        // printf("%d %d\n",c[0],c[1]);
        if(c[0]>0&&c[1]>0)  flag=false;
        cc[0]+=c[0];cc[1]+=c[1];
        ans+=(max(0,c[0]+c[1]-2)/2)+1;
    }
    if(!cc[0]||!cc[1])  flag=false;
    printf("%d\n",ans-1+flag);
}