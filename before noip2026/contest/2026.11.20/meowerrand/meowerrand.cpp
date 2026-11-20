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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1.5e4+10,maxk=35;
int n,k;
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
int ans[maxn];
int siz[maxn];
int f[maxn][maxk][2],F[maxk][2],g[maxn][maxk][2],fw[maxn],mt[maxk][2],pr[maxn][maxk][2],sf[maxn][maxk][2],tmp[maxk][2],FF[maxk][2];
inline void mrg(int (*a)[2],int (*b)[2],int (*c)[2],int w){
    for(int i=0;i<=k;i++)c[i][0]=c[i][1]=1e9;
    for(int i=0;i<=k;i++){
        for(int j=1;j<=k&&i+j-1<=k;j++){
            gmn(c[i+j][0],a[i][0]+b[j][0]+j*w);
            gmn(c[i+j-1][0],a[i][1]+b[j][0]+j*w);
            gmn(c[i+j][1],a[i][1]+b[j][0]+j*w);
            if(i+j-1>=1){
                gmn(c[i+j-1][0],a[i][0]+b[j][1]+j*w+w);
                gmn(c[i+j-1][1],a[i][1]+b[j][1]+j*w+w);
            }
        }
    }
}
void getans(int u){
    ans[u]=1e9;
    for(int i=1;i<=k;i++)gmn(ans[u],min(f[u][i][0],f[u][i][1]));
}
void dfs(int u,int ft){
    mems(f[u],0);
    siz[u]=1;
    f[u][0][1]=1e9;
    vector<int> son;son.clear();
    go(u,_)if(t^ft){
        son.eb(t);
        fw[t]=w;
        dfs(t,u);
        memc(F,f[u]);
        mrg(F,f[t],f[u],w);
        siz[u]+=siz[t];
    }
    if(!son.empty()){
        int lst=0;
        for(int t:son){
            if(!lst)  memc(pr[t],mt);
            else    mrg(pr[lst],f[lst],pr[t],fw[lst]);
            lst=t;
        }
        reverse(son.begin(),son.end());
        lst=0;
        for(int t:son){
            if(!lst)  memc(sf[t],mt);
            else    mrg(sf[lst],f[lst],sf[t],fw[lst]);
            lst=t;
        }
    }
    // for(int t:son){
    //     memc(F,f[t]);mrg(pr[t],sf[t],f[t],0);
    //     memc(tmp,f[t]);mrg(tmp,mt,f[t],fw[t]);
    //     printf("t = %d\n",t);
    //     for(int i=1;i<=k;i++)printf("%d %d\n",F[i][0],F[i][1]);puts("");
    //     for(int i=1;i<=k;i++)printf("%d %d\n",f[t][i][0],f[t][i][1]);
    //     puts("\n");
    // }
}
void dfs2(int u,int ft){
    if(ft){
        // mrg(mt,g[ft],g[u],fw[u]);
        mrg(pr[u],sf[u],tmp,0);
        memc(F,tmp);mrg(F,g[ft],tmp,0);

        memc(F,f[u]);memc(FF,tmp);mrg(F,FF,f[u],fw[u]);
        mrg(mt,tmp,g[u],fw[u]);
    }
    else    memc(g[u],mt);
    getans(u);
    go(u,i)if(t^ft)dfs2(t,u);
}
bool mem2;
int main(){
    // freopen("meowerrand.in","r",stdin);freopen("meowerrand.out","w",stdout);
    mt[0][1]=1e9;
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    dfs(1,0);
    // for(int i=1;i<=k;i++)printf("%d %d\n",f[1][i][0],f[1][i][1]);
    dfs2(1,0);
    for(int i=1;i<=n;i++)   printf("%d\n",ans[i]);
    // for(int rt=1;rt<=n;rt++){
    //     dfs(rt,0);
    //     int ans=1e9;
    //     for(int i=1;i<=k;i++)gmn(ans,min(f[rt][i][0],f[rt][i][1]));
    //     printf("%d\n",ans);
    // }
}