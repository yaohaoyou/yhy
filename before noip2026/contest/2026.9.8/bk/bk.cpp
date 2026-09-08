#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
const int maxn=1510,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,K;
int a[maxn],b[2][maxn],d[2][maxn];
int f[2][maxn][maxn];
bool mem2;
int nixu(int s){
    vector<int> v;
    for(int i=0;i<n;i++)v.eb(bool(s&(1<<i)));
    int res=0;
    for(int i=0;i<v.size();i++){
        if(v[i]){
            for(int j=i+1;j<v.size();j++)res+=(!v[j]);
        }
    }
    return res;
}
int main(){
    freopen("bk.in","r",stdin);freopen("bk.out","w",stdout);
    // freopen("D:\\yhy\\before noip2026\\contest\\2026.9.8\\bk\\bk8.in","r",stdin);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&K);
    int c=0;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    c=count(a+1,a+n+1,0);
    if(c>n-c){
        for(int i=1;i<=n;i++)   a[i]^=1;
        c=count(a+1,a+n+1,0);
    }
    for(int i=1,c0=0,c1=0;i<=n;i++){
        if(!a[i])   b[0][++c0]=i;
        else    b[1][++c1]=i;
    }
    for(int i=1;i<=n-c;i++){
        for(int j=1;j<=c;j++)d[0][i]+=(b[0][j]<=b[1][i]);
    }
    for(int i=1;i<=c;i++){
        for(int j=1;j<=n-c;j++)d[1][i]+=(b[1][j]<=b[0][i]);
    }
    f[0][0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=max(0,i-1-n+c);j<=c&&j<i;j++)mems(f[(i+1)&1][j],0);
        for(int j=max(0,i-n+c);j<=c&&j<=i;j++){
            for(int k=0;k<=K;k++)if(f[i&1][j][k]){
                // printf("%d %d %d : %d\n",i,j,k,f[i&1][j][k]);
                // 0
                int nk=k+abs(i+1-b[0][j+1]);
                if(nk<=K) madd(f[(i+1)&1][j+1][nk],f[i&1][j][k]);
                // 1
                if(i-j+1<=n-c) madd(f[(i+1)&1][j][k],f[i&1][j][k]);
            }
        }
    }
    int ans=0;
    for(int i=K;i>=0;i-=2)madd(ans,f[n&1][c][i]);
    printf("%d\n",ans);
    debug("%.0fms\n",double(clock())/CLOCKS_PER_SEC*1000);
}