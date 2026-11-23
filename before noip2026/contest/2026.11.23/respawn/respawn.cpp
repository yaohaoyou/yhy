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
const int maxn=3010;
int n,T;
int u[maxn],v[maxn],d[maxn],e[maxn],w[maxn];
ll f[maxn][maxn],g[maxn],h[maxn];
bool mem2;
int main(){
    // freopen("respawn.in","r",stdin);freopen("respawn.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;i++)   scanf("%d%d%d%d",&u[i],&v[i],&d[i],&e[i]),w[i]=min(u[i]+v[i],d[i]+e[i]);
    // for(int i=1;i<=n;i++)   printf("%d ",w[i]);puts("");
    for(int i=1;i<=n;i++)   w[i]+=w[i-1];
    mems(f,0x3f);f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int k=0;k<=n;k++){
            g[k]=f[i-1][k]+(2*k+1)*T-(v[i]+d[i])*k;
            if(k)   gmn(g[k],g[k-1]);
        }
        for(int k=n;k;k--){
            h[k]=f[i-1][k]+(1+2*k)*T+(u[i]+e[i])*k;
            if(k^n) gmn(h[k],h[k+1]);
        }
        for(int j=0;j<=n;j++){
            if(j^n) gmn(f[i][j],h[j+1]-(u[i]+e[i])*j);
            // for(int k=j+1;k<=n;k++)  gmn(f[i][j],f[i-1][k]+(1+2*k)*T+(u[i]+e[i])*k-(u[i]+e[i])*j);
            // for(int k=0;k<j;k++) gmn(f[i][j],f[i-1][k]+(2*k+1)*T-(v[i]+d[i])*k+(v[i]+d[i])*j);
            if(j){
                gmn(f[i][j],g[j-1]+(v[i]+d[i])*j);
                gmn(f[i][j],f[i-1][j]+(2*j+1)*T+d[i]+e[i]);
            }
            gmn(f[i][j],f[i-1][j]+(2*j+1)*T+u[i]+v[i]);
        }
    }
    printf("%lld\n",f[n][0]+T);
}