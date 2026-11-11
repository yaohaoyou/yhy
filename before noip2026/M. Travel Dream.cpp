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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){if(x>y)x=y;}
inline void gmx(auto &x,auto y){if(x<y)x=y;}
using namespace std;
bool mem1;
const int maxn=610;
int n,m,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int ans=-1;
pii E[maxn];
int G[maxn][maxn];
int c[maxn],f[maxn][maxn];
pii g[maxn][maxn][3];
inline void upd(pii *ar,pii w){
    pii nw[4]={ar[0],ar[1],ar[2],w};
    sort(nw,nw+4,greater<pii>());
    ar[0]=nw[0];
    if(nw[1].se!=ar[0].se){
        ar[1]=nw[1];
        if(nw[2].se!=ar[0].se&&nw[2].se!=ar[1].se)  ar[2]=nw[2];
        else    ar[2]=nw[3];
    }
    else    ar[1]=nw[2],ar[2]=nw[3];
    // if(w>ar[0]){
    //     int c=0;
    //     // if(ar[0].se^w.se)   ar[1]
    //     // if(w.se==ar[0].se)
    //     // ar[2]=ar[1],ar[1]=ar[0],ar[0]=w;
    // }
    // else if(w.se!=ar[0].se){
    //     if(w>ar[1])    ar[2]=ar[1],ar[1]=w;
    //     else if(w.se!=ar[1].se) gmx(ar[2],w);
    // }
}
void solve(){
    for(int i=1;i<=n;i++)   c[i]=rand()&1;
    mems(g,-0x3f);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&c[i]==c[j]){
        go(i,_)if(c[t]==c[i]&&G[t][j])upd(g[i][j],pii(w+G[t][j],t)),upd(g[j][i],pii(w+G[t][j],t));
    }
    mems(f,-0x3f);
    for(bool o:{0,1}){
        int K=(k+o)>>1;
        if(K==1){
            for(int i=1;i<=n;i++)if(c[i]==o)f[i][i]=0;
        }
        else if(K==2){
            for(int i=1;i<=n;i++)if(c[i]==o)for(int j=1;j<=n;j++)if(c[j]==o)f[i][j]=G[i][j];
        }
        else if(K==3){
            for(int i=1;i<=n;i++)if(c[i]==o)for(int j=1;j<=n;j++)if(c[j]==o)f[i][j]=g[i][j][0].fi;
        }
        else if(K==4){
            for(int i=1;i<=m;i++){
                int a=E[i].fi,b=E[i].se;
                if(c[a]!=o||c[b]!=o)    continue;
                for(int j=1;j<=m;j++){
                    int c=E[j].fi,d=E[j].se;
                    if(::c[c]!=o||::c[d]!=o||a==c||a==d||b==c||b==d||!G[b][c])    continue;
                    gmx(f[a][d],G[a][b]+G[b][c]+G[c][d]);
                    gmx(f[d][a],G[a][b]+G[b][c]+G[c][d]);
                }
            }
        }
        else{
            for(int i=1;i<=m;i++){
                int a=E[i].fi,b=E[i].se;
                if(c[a]!=o||c[b]!=o)    continue;
                for(int j=1;j<=m;j++){
                    int c=E[j].fi,d=E[j].se;
                    if(::c[c]!=o||::c[d]!=o||a==c||a==d||b==c||b==d)    continue;
                    for(int l=0;l<3;l++){
                        if(g[b][c][l].se!=a&&g[b][c][l].se!=d){
                            gmx(f[a][d],G[a][b]+g[b][c][l].fi+G[c][d]);
                            gmx(f[d][a],G[a][b]+g[b][c][l].fi+G[c][d]);
                            break;
                        }
                    }
                }
            }
        }
    }
    for(int i=1;i<=m;i++)if(c[E[i].fi]+c[E[i].se]==1){
        int a=E[i].fi,b=E[i].se;
        if(c[a])    swap(a,b);
        for(int j=1;j<=m;j++)if(c[E[j].fi]+c[E[j].se]==1){
            int c=E[j].fi,d=E[j].se;
            if(::c[c])  swap(c,d);
            if(a==c&&b==d)  continue;
            // if(f[a][c]+f[b][d]+G[a][b]+G[c][d]==3)printf("%d %d %d %d %d %d %d : %d\n",a,b,c,d,::c[1],::c[2],::c[3],f[b][d]);
            gmx(ans,f[a][c]+f[b][d]+G[a][b]+G[c][d]);
        }
    }
}
bool mem2;
int main(){
    srand(time(0));
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);gmx(G[u][v],w);gmx(G[v][u],w);}
    m=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(G[i][j])E[++m]=pii(i,j);
    int T=2000;
    while(T--)  solve();
    if(~ans)    printf("%d\n",ans);
    else    puts("impossible");
}