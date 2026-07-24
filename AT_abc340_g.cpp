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
const int maxn=4e5+10,mod=998244353;
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
int n;
int a[maxn],b[maxn];
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
int dep[maxn],dfn[maxn],tot;
vector<int> v[maxn];
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
int ans;
vector<int> son[maxn];
int f[maxn][2];
void dfs(int u,int col){
    f[u][0]=f[u][1]=0;
    for(int t:son[u]){
        dfs(t,col);
        int x=f[u][0],y=f[u][1];
        madd(f[u][0],imadd(f[t][0],f[t][1]));
        madd(f[u][1],immul(x+y,f[t][0]+f[t][1]));
    }
    if(a[u]==col)    madd(f[u][0],1),madd(ans,f[u][0]);
    madd(ans,f[u][1]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[a[i]].eb(i);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    stLCA::build();
    for(int i=1;i<=n;i++){
        if(v[i].empty())    continue;
        int m=0;
        b[++m]=1;
        for(int j:v[i])b[++m]=j;
        auto cmp=[&](int x,int y){return dfn[x]<dfn[y];};
        sort(b+1,b+m+1,cmp);
        for(int j=1;j<m;j++)    b[j+m]=LCA(b[j],b[j+1]);m+=m-1;
        sort(b+1,b+m+1,cmp);
        m=unique(b+1,b+m+1)-b-1;
        for(int j=2;j<=m;j++){
            int l=LCA(b[j-1],b[j]);
            son[l].eb(b[j]);
        }
        dfs(1,i);
        for(int j=2;j<=m;j++)son[LCA(b[j-1],b[j])].clear();
    }
    printf("%d\n",ans);
}