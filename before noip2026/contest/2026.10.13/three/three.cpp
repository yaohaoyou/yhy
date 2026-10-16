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
const int maxn=1e4+10,maxm=1e3+10,V=1e3;
bool mem1;
int n,m;
int a[maxn],b[maxn];
ll f[maxn][2],g[(V+10)<<1];
bool mem2;
#define pli pair<ll,int>
priority_queue<pli,vector<pli>,greater<pli>> q;
bool vis[maxn];
void dijkstra(){
    mems(vis,0);mems(g,0x3f);q.ep(g[V]=0,V);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        for(int i=1;i<=m;i++){
            int t=u+a[i];
            if(t<=V+V&&g[t]>g[u]+b[i]){g[t]=g[u]+b[i];q.ep(g[t],t);}
            t=u-a[i];
            if(t>=0&&g[t]>g[u]+b[i]){g[t]=g[u]+b[i];q.ep(g[t],t);}
        }
    }
}
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    dijkstra();
    for(int i=2;i<=n;i++){
        mems(f[i],0x3f);
        if(i==2)    f[i][1]=0;
        for(int j=1;j<=V&&j<i;j++)    gmn(f[i][1],max(f[j][0],f[i-j][1])+g[-j+V]);
        for(int j=1;j<=V&&j<i;j++)    gmn(f[i][0],max(f[j+1][1],f[i-j][0])+g[j+V]);
        // printf("%d %d\n",f[i][0],f[i][1]);
    }
    if(f[n][0]==0x3f3f3f3f3f3f3f3f) puts("-1");
    else    printf("%lld\n",f[n][0]);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int c,T;scanf("%d%d",&c,&T);for(int i=1;i<=T;i++)matt(i);}