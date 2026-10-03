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
const int maxn=110;
bool mem1;
int n,m;
ll a[maxn];
ll f[40][maxn][maxn];  // f[i][j] 表示前 i 层处理了 j 种字母，有 k 个位置的答案
ll g[maxn][maxn*3];
bool mem2;
void matt(int _cases){
    scanf("%d%d",&n,&m);
    if(!n&&!m)  exit(0);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;i++)   a[i]+=a[i-1];
    mems(f,0x3f);f[0][0][1]=0;
    for(int i=1;i<=m;i++){
        mems(g,0x3f);
        for(int j=0;j<=n;j++)for(int k=0;k<=n+n;k++)
            gmn(g[j][j+k*2],f[i-1][j][k]-a[j]*i);
        for(int j=1;j<=n;j++)for(int k=0;k<=n+n;k++)gmn(g[j][k],g[j-1][k]);
        for(int j=0;j<=n;j++)
            for(int k=0;k<=n&&k<=(1<<i);k++){
                f[i][j][k]=g[j][j+k]+a[j]*i;
            }
    }
    printf("%lld\n",*min_element(f[m][n],f[m][n]+n+1));
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);for(int i=1;;i++)matt(i);}