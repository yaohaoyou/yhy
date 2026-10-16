#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=410,maxq=3e5+10;
bool mem1;
int n,m,q;
int f[maxn][maxn],ans[maxq];
vector<pii> Q[maxn][maxn];
piii E[maxn*maxn];
map<int,vector<pii>> mp;
bool mem2;
void matt(int _cases){
    mp.clear();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)Q[i][j].clear();
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=i==j?0:1e9;
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);E[i]=piii(w,pii(u,v));f[u][v]=f[v][u]=1;}
    for(int i=1;i<=q;i++){int u,v,k;scanf("%d%d%d",&u,&v,&k);Q[u][v].eb(k,i);}
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(!Q[i][j].empty())sort(Q[i][j].begin(),Q[i][j].end());
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)gmn(f[j][k],f[j][i]+f[i][k]);
    sort(E+1,E+m+1);
    for(int _=1,k=1;_<=m;_++){
        int w=E[_].fi,u=E[_].se.fi,v=E[_].se.se;
        // gmx(k,_);while(k<=m&&E[k].fi==w)k++;
        if(f[u][v]){
            f[u][v]=f[v][u]=0;
            for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
                gmn(f[i][j],min(f[i][u]+f[v][j],f[i][v]+f[u][j]));
                while(!Q[i][j].empty()&&Q[i][j].back().fi>f[i][j]){
                    ans[Q[i][j].back().se]=w;Q[i][j].pop_back();
                }
            }
        }
    }
    for(int i=1;i<=q;i++)   printf("%d ",ans[i]);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}