#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int maxn=1e3+10,dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int n,m,k;
bool f[maxn][maxn];
char s[maxn][maxn];
void dfs(int x,int y,int d,int stp){
    f[x][y]=true;
    if(stp==k)  return;
    int xx=x+dir[d][0],yy=y+dir[d][1];
    if(xx>0&&xx<=n&&yy>0&&yy<=m&&s[xx][yy]!='x')    return dfs(xx,yy,d,stp+1);
    return dfs(x,y,(d+1)%4,stp+1);
}
void solve(){
    int x,y,d;
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d%d",&x,&y,&d);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)f[i][j]=0;
    for(int i=1;i<=n;i++)   scanf("%s",s[i]+1);
    dfs(x,y,d,0);
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans+=f[i][j];
    printf("%d\n",ans);
}
int main(){
    // freopen("explore.in","r",stdin);freopen("explore.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)solve();
}
