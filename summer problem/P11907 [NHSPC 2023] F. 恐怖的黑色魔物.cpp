#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,dir[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
int f,m,n,R;
struct point{int a,b,c;};
vector<vector<int>> id[maxn];
point p[maxn];
int dis[maxn]; 
queue<point> q;
vector<pair<int,pair<point,point>>> E;
int wp[maxn<<1];
namespace Graph{
    const int maxm=maxn<<2;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn<<1];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
struct DSU{
    int fa[maxn<<1];
    void init(){iota(fa+1,fa+f*n*m+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
}U;
void bfs(){
    mems(dis,0x3f);
    for(int i=1;i<=R;i++)   q.ep(p[i]),dis[id[p[i].a][p[i].b][p[i].c]]=0;
    while(!q.empty()){
        auto [i,j,k]=q.front();q.pop();
        for(int l=0;l<6;l++){
            int ii=i+dir[l][0],jj=j+dir[l][1],kk=k+dir[l][2];
            if(ii>0&&ii<=f&&jj>0&&jj<=m&&kk>0&&kk<=n&&dis[id[ii][jj][kk]]>dis[id[i][j][k]]+1){
                dis[id[ii][jj][kk]]=dis[id[i][j][k]]+1;
                q.ep(ii,jj,kk);
            }   
        }
    }
}
void kruskal(){
    int tot=f*m*n;
    for(int i=1;i<=tot;i++) wp[i]=dis[i];
    sort(E.begin(),E.end(),[&](auto x,auto y){return x.fi>y.fi;});
    U.init();
    for(auto [w,tmp]:E){
        // printf("%d (%d,%d,%d) (%d,%d,%d)\n",w,tmp.fi.a,tmp.fi.b,tmp.fi.c,tmp.se.a,tmp.se.b,tmp.se.c);
        int x=id[tmp.fi.a][tmp.fi.b][tmp.fi.c],y=id[tmp.se.a][tmp.se.b][tmp.se.c];
        x=U.find(x);y=U.find(y);if(x==y)continue;
        wp[++tot]=w;U.fa[tot]=U.fa[x]=U.fa[y]=tot;adde(tot,x);adde(tot,y);
    }
    // for(int i=1;i<=tot;i++) printf("%d ",wp[i]);
}
namespace st_LCA{
    int tot;
    int Log[maxn<<1],st[20][maxn<<1];
    int dfsn[maxn<<1];
    inline int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void dfs(int u,int ft){st[0][dfsn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(U.find(1),0);
        for(int i=2;i<=tot;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[tot];i++)
            for(int j=1;j+(1<<i)-1<=tot;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
int main(){
    scanf("%d%d%d%d",&f,&m,&n,&R);
    for(int i=1;i<=R;i++)   scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
    for(int i=1;i<=f;i++)   id[i]=vector<vector<int>>(m+1,vector<int>(n+1,0));
    {
        int tot=0;
        for(int i=1;i<=f;i++)for(int j=1;j<=m;j++)for(int k=1;k<=n;k++)id[i][j][k]=++tot;
    }
    bfs();
    for(int i=1;i<=f;i++)for(int j=1;j<=m;j++)for(int k=1;k<=n;k++){
        for(int l=0;l<6;l++){
            int ii=i+dir[l][0],jj=j+dir[l][1],kk=k+dir[l][2];
            if(ii>0&&ii<=f&&jj>0&&jj<=m&&kk>0&&kk<=n)
                E.eb(min(dis[id[i][j][k]],dis[id[ii][jj][kk]]),mp((point){i,j,k},(point){ii,jj,kk}));
        }
    }
    kruskal();
    st_LCA::build();
    int q;scanf("%d",&q);
    while(q--){
        point x,y;
        scanf("%d%d%d%d%d%d",&x.a,&x.b,&x.c,&y.a,&y.b,&y.c);
        int u=id[x.a][x.b][x.c],v=id[y.a][y.b][y.c];
        printf("%d\n",wp[LCA(u,v)]);
    }
}