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
const int maxn=110,maxp=maxn*maxn;
int n,m,k,tot,cur;
int id[maxn][maxn],col[maxp];
pii rk[maxp];
bitset<maxp> ch[maxp];
struct DSU{
    int fa[maxp];
    void init(){iota(fa+1,fa+n*n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
namespace Graph{
    const int maxm=maxn*maxn*maxn*4;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int lim;
void dfss(int x){
    if(x>tot){
        printf("%d\n",lim);
        for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d %d : %d\n",i+j,i-j,col[id[i][j]]);
        exit(0);
    }
    for(int i=0;i<lim;i++){
        col[x]=i;
        bool flag=true;
        go(x,_)if(col[t]==col[x]){flag=false;break;}
        if(flag)    dfss(x+1);
    }
    col[x]=-1;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)rk[id[i][j]=++tot]=pii(i,j);
    U.init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p<=n;p++){
                for(int q=1;q<=m;q++)
                    if(abs(i-p)+abs(j-q)==k)    add(id[i][j],id[p][q]);
            }
        }
    }
    mems(col,-1);
    for(lim=1;;lim++){
        dfss(1);
    }
}