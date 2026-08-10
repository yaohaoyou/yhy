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
const int maxn=210;
int n;
int a[maxn][maxn],p[maxn],mp[maxn][maxn];
bool vis[maxn];
queue<int> q[maxn][maxn];
pii b[maxn][maxn];
bool dfs(int u){
    for(int i=1;i<=n;i++)if(mp[u][i]&&!vis[i]){
        vis[i]=true;
        if(!p[i]||dfs(p[i]))   return p[i]=u,true;
    }
    return false;
}
void matt(int _cases){
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)mp[i][j]=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
        int x;scanf("%d",&x);
        q[i][x].ep(j);
        mp[i][x]++;
    }
    for(int i=1;i<=n;i++){
        fill(p+1,p+n+1,0);
        for(int j=1;j<=n;j++)   fill(vis+1,vis+n+1,0),dfs(j);
        for(int j=1;j<=n;j++){
            mp[p[j]][j]--;
            b[p[j]][i]=pii(j,q[p[j]][j].front());
            q[p[j]][j].pop();
        }
    }
    printf("%d\n",n*(n-1)/2);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            printf("%d %d %d %d\n",i,b[i][j].se,j,b[j][i].se);
    // for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%d ",b[i][j].fi);puts("");
    // for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%d ",b[i][j].se);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}