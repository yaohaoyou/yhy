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
const int maxn=3010,mod=998244353;
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
int n,m;
int f[maxn][maxn][2][2],g[maxn][2][2];
pii a[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   a[i]=pii(abs(i*2-m),i);
    sort(a+1,a+n+1,greater<pii>());
    f[0][0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int x:{0,1})for(int y:{0,1}){
            g[0][x][y]=0;
            for(int j=1;j<=i;j++)g[j][x][y]=imadd(g[j-1][x][y],f[i-1][j][x][y]);
        }
        int x=a[i].se;
        if(x*2<m){  // A
            madd(f[i][0][0][0],immul(f[i-1][0][0][0],i));
            madd(f[i][0][0][1],immul(f[i-1][0][0][1],i));
            for(int j=2;j<=i;j++){
                madd(f[i][j][0][0],immul(f[i-1][j-1][0][0],j-1));
                madd(f[i][j][0][0],immul(f[i-1][j][0][0],i-j));
                madd(f[i][j][0][0],immul(f[i-1][j-1][1][0],2));
                if(j>3)madd(f[i][j][1][0],immul(f[i-1][j-1][1][0],j-3));
                madd(f[i][j][1][0],immul(f[i-1][j][1][0],i-j));

                madd(f[i][j][0][1],immul(f[i-1][j-1][0][1],j-1));
                madd(f[i][j][0][1],immul(f[i-1][j-1][1][1],2));
                if(j>3)madd(f[i][j][1][1],immul(f[i-1][j-1][1][1],j-3));
                madd(f[i][j][0][1],immul(immul(f[i-1][j][0][0],x),i-j));
                madd(f[i][j][1][1],immul(immul(f[i-1][j][1][0],x),i-j));
            }
        }
        else{  // B
            for(int j=2;j==2||j<=i;j++){
                for(bool o:{0,1}){
                    if(j>3)madd(f[i][j][0][o],immul(f[i-1][j-1][0][o],j-3));
                    madd(f[i][j][1][o],f[i-1][j-1][0][o]);
                    if(j>2)madd(f[i][j][1][o],immul(f[i-1][j-1][1][o],j-2));
                }
                // k=0
                if(j==2){
                    madd(f[i][j][1][0],f[i-1][0][0][0]);
                    madd(f[i][j][1][1],f[i-1][0][0][1]);
                    madd(f[i][j][1][1],immul(f[i-1][0][0][0],x));
                }
                else{
                    madd(f[i][j][0][0],f[i-1][0][0][0]);
                    madd(f[i][j][0][1],f[i-1][0][0][1]);
                    madd(f[i][j][0][1],immul(f[i-1][0][0][0],x));
                }
                // for(int k=2;k<j;k++){
                //     madd(f[i][j][0][0],f[i-1][k][0][0]);
                //     madd(f[i][j][1][0],f[i-1][k][1][0]);
                //     madd(f[i][j][0][1],immul(f[i-1][k][0][0],x));
                //     madd(f[i][j][1][1],immul(f[i-1][k][1][0],x));
                // }
                madd(f[i][j][0][0],g[j-1][0][0]);
                madd(f[i][j][1][0],g[j-1][1][0]);
                madd(f[i][j][0][1],immul(g[j-1][0][0],x));
                madd(f[i][j][1][1],immul(g[j-1][1][0],x));
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++)madd(ans,f[n][i][0][1]),madd(ans,immul(f[n][i][1][1],2));
    for(int i=1;i<=n;i++)   mmul(ans,qpow(i,mod-2));
    printf("%d\n",ans);
}