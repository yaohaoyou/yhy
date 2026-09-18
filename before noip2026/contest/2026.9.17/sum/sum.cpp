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
bool mem1;
const int maxn=5010;
int n,m;
int a[maxn],b[maxn];
int f[maxn][maxn],g[maxn][maxn];  // f[i][j] 表示前 i 个数达到 b 还有 j 步的最小删除个数，g[i][j] 表示 [i,n] 达到 j 的最小选择个数
bool mem2;
int main(){
    freopen("sum.in","r",stdin);freopen("sum.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    mems(f,0x3f);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]),f[0][b[i]]=0;
    m=5000;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)   f[i][j]=min(f[i-1][j]+1,j+a[i]<=m?f[i-1][j+a[i]]:f[0][0]);
    mems(g,0x3f);
    g[n+1][0]=0;
    for(int i=n;i;i--)
        for(int j=0;j<=m;j++)   g[i][j]=min(g[i+1][j],j>=a[i]?(g[i+1][j-a[i]]+1):f[0][0]);
    int ans=f[0][0];
    for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)gmn(ans,max(f[i][j],g[i+1][j]));
    printf("%d\n",ans==f[0][0]?-1:ans);
}