#pragma GCC optimize(2)
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
// inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
// inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
#define gmx(x,y) __builtin_expect(x<y,0)&&(x=y)
using namespace std;
bool mem1;
const int maxn=20,maxN=(1<<17)+10,maxm=1010;
int n,m;
ll a[maxm][maxn];
ll f[maxN],g[maxN],h[maxN],H[maxN];
int _ctz[maxN],_clz[maxN],hs[maxN];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);const int N=(1<<n)-1;
    for(int i=1;i<=m;i++){
        memc(a[i],a[i-1]);
        for(int j=1;j<=n;j++){int x;scanf("%d",&x);a[i][j]+=x;}
    }
    ll ans=accumulate(a[m]+1,a[m]+n+1,0ll);
    for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)a[i][j]=max(0ll,-a[i][j]);
    for(int i=1;i<=N;i++)   _ctz[i]=__builtin_ctz(i)+1,_clz[i]=__builtin_clz(i),hs[i]=i^(1<<_ctz[i]-1);
    for(int i=1;i<=m;i++){
        for(int s=1;s<=N;s++){
            h[s]=h[hs[s]]+a[i][_ctz[s]];
            gmx(H[s],h[s]);
        }
    }
    memc(g,H);
    printf("%lld ",ans+H[N]);
    for(int x=2;x<n-1;x++){
        for(int s=N-3;s>1;s-=4){
            if(__builtin_popcount(s)<x)    continue;
            for(int t=(s-1)&s;t;t=(t-1)&s){
                if(__builtin_clz(s)!=__builtin_clz(t))  break;
                gmx(f[s],g[s^t]+H[t]);

                gmx(f[s|1],g[s^t^1]+H[t]);
                gmx(f[s|1],g[s^t]+H[t|1]);

                gmx(f[s|2],g[s^t^2]+H[t]);
                gmx(f[s|2],g[s^t]+H[t|2]);

                gmx(f[s|3],g[s^t^3]+H[t]);
                gmx(f[s|3],g[s^t^2]+H[t|1]);
                gmx(f[s|3],g[s^t^1]+H[t|2]);
                gmx(f[s|3],g[s^t]+H[t|3]);
            }
            gmx(f[s^1],g[s]+H[1]);
            gmx(f[s^2],g[s]+H[2]);
            gmx(f[s^3],g[s^2]+H[1]);gmx(f[s^3],g[s^1]+H[2]);gmx(f[s^3],g[s]+H[3]);
            g[s]=f[s];g[s^1]=f[s^1];g[s^2]=f[s^2];g[s^3]=f[s^3];
        }
        printf("%lld ",ans+f[N]);
    }
    if(n>1){
        if(n>2){
            for(int t=N;t;t--)gmx(f[N],g[N^t]+H[t]);
            printf("%lld ",ans+f[N]);
        }
        for(int i=1;i<=n;i++){
            ll res=0;
            for(int j=1;j<=m;j++)gmx(res,a[j][i]);
            ans+=res;
        }
        printf("%lld",ans);
    }
}