#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
const int maxn=1010,maxm=2e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
    inline int sqr(int x){return immul(x,x);}
}
using namespace FastMod;
int n,m,k,K;
int a[maxn],c[maxn],suf[maxn],pq[maxm];
int f[8][maxn],g[7][7][maxn][maxn];
piii b[maxm];
void slv(piii x){for(int i=x.fi.fi;i<=x.fi.se;i++)a[i]^=x.se;}
void solve(){
    int ans=0;
    for(int i=0;i<(1<<m);i++){
        for(int j=1;j<=m;j++)if(i&(1<<j-1))c[b[j].fi.fi]^=b[j].se,c[b[j].fi.se+1]^=b[j].se;
        for(int j=1;j<=n;j++)   c[j]^=c[j-1],a[j]^=c[j];
        // for(int j=1;j<=n;j++)for(int k=j;k<=n;k++)madd(ans,sqr(accumulate(a+j,a+k+1,0)));
        for(int j=1;j<=n;j++)   madd(ans,1ull*j*(n-j+1)%mod*sqr(a[j])%mod);
        for(int j=n;j;j--)  suf[j]=imadd(suf[j+1],immul(n-j+1,a[j]));
        for(int j=1;j<=n;j++)   madd(ans,2ull*j*a[j]%mod*suf[j+1]%mod);
        for(int j=1;j<=n;j++)   a[j]^=c[j],c[j]=0;
    }
    printf("%d\n",ans);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),k=max(k,__lg(a[i])+1);
    pq[0]=1;for(int i=1;i<=maxm-10;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    K=(1<<k)-1;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)   scanf("%d%d%d",&b[i].fi.fi,&b[i].fi.se,&b[i].se);
    for(int o=1;o<=m;o++){
        int l=b[o].fi.fi,r=b[o].fi.se,xx=b[o].se;
        for(int i=0;i<k;i++)if(xx&(1<<i)){
            for(int j=0;j<k;j++)if(xx&(1<<j)){
                g[i][j][l][l]++;g[i][j][r+1][r+1]++;
                g[i][j][l][r+1]--;g[i][j][r+1][l]--;
            }
            f[i][l]++;f[i][r+1]--;
        }
    }
    for(int o=0;o<k;o++)for(int i=1;i<=n;i++)f[o][i]+=f[o][i-1];
    for(int o=0;o<k;o++)for(int _=0;_<k;_++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[o][_][i][j]+=g[o][_][i-1][j]+g[o][_][i][j-1]-g[o][_][i-1][j-1];
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            for(int x=0;x<k;x++){
                bool i0=a[i]&(1<<x);
                for(int y=0;y<k;y++){
                    bool j0=a[j]&(1<<y);
                    int c[4]={0,f[y][j]-g[x][y][i][j],f[x][i]-g[x][y][i][j],g[x][y][i][j]};
                    c[0]=m-c[1]-c[2]-c[3];
                    int res=0;
                    for(int o=0;o<8;o++){
                        if((bool(o&2)^bool(o&4))==i0)   continue;
                        if(((o&1)^bool(o&4))==j0)   continue;
                        if(!c[1]&&(o&1))    continue;
                        if(!c[2]&&(o&2))    continue;
                        if(!c[3]&&(o&4))    continue;
                        madd(res,1ull*pq[max(0,c[1]-1)]*pq[max(0,c[2]-1)]%mod*pq[max(0,c[3]-1)]%mod);
                    }
                    if(i^j) madd(ans,2ull*i*(n-j+1)%mod*pq[x+y+c[0]]%mod*res%mod);
                    else    madd(ans,1ull*i*(n-j+1)%mod*pq[x+y+c[0]]%mod*res%mod);
                }
            }
        }
    }
    printf("%d\n",ans);
}