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
const int maxn=510;
bool mem1;
int n;
ll a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
bool mem2;
void matt(int _cases){
    for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)a[i][j]=b[i][j]=c[i][j]=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%lld",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            b[i][j]=1e18;
            if(j^1) b[i][j]=(j>1?a[i][j-2]:0)+b[i-1][j-1];
            if(j^n) gmn(b[i][j],(j<n-1?a[i][j+2]:0)+b[i-1][j+1]);
            b[i][j]+=a[i][j];
        }
    for(int i=n;i;i--)
        for(int j=1;j<=n;j++){
            c[i][j]=1e18;
            if(j^1) c[i][j]=(j>1?a[i][j-2]:0)+c[i+1][j-1];
            if(j^n) gmn(c[i][j],(j<n-1?a[i][j+2]:0)+c[i+1][j+1]);
            c[i][j]+=a[i][j];
        }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++){
        ll ans=1e18;
        if(j^1) ans=c[i+1][j-1]+b[i-1][j-1]+(j>1?a[i][j-2]:0);
        if(j^n) gmn(ans,c[i+1][j+1]+b[i-1][j+1]+(j<n-1?a[i][j+2]:0));
        ans+=a[i][j];
        printf("%lld ",ans);
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}