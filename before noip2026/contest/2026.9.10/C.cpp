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
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=6010,mod=998244353;
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
int n;
pii a[maxn];
int f[maxn][maxn],g[maxn][maxn],h[maxn][maxn],s[maxn][maxn],w[maxn][maxn];
int fac[maxn],inv[maxn],I[maxn];
vector<int> vl[maxn],vr[maxn];
void init(){
    const int N=6000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    I[0]=1;for(int i=1;i<=N;i++)I[i]=qpow(i,mod-2);
}
inline int A(int x,int y){return x<y?0:1ull*fac[x]*inv[x-y]%mod;}
int main(){
    init();
    scanf("%d",&n);
    int LL=n,RR=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].fi,&a[i].se);
        vl[a[i].fi].eb(a[i].se);vr[a[i].se].eb(a[i].fi);
        gmn(LL,a[i].fi);gmx(RR,a[i].se);
        madd(f[a[i].fi][a[i].se],1);
    }
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++){
        w[i][j]=w[i][j-1];
        for(int k:vr[j])w[i][j]+=k>=i;
    }
    for(int len=1;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){
            for(int i:vr[r])if(i>=l){
                if(i==l){
                    // for(int x=l;x<=r;x++)for(int y=x;y<=r;y++)if((x^l)||(y^r))madd(f[l][r],f[x][y]);
                    madd(f[l][r],imdel(imadd(s[l+1][r],s[l][r-1]),s[l+1][r-1]));
                }
                else{
                    madd(f[l][r],imdel(g[l][r-1],g[l][i-1]));
                    // for(int x=i;x<r;x++)    madd(f[l][r],f[l][x]);
                }
            }
            for(int i:vl[l])if(i<r){
                madd(f[l][r],imdel(h[l+1][r],h[i+1][r]));
                // for(int x=l+1;x<=i;x++)   madd(f[l][r],f[x][r]);
            }
            mmul(f[l][r],I[n-w[l][r]]);
            g[l][r]=imadd(g[l][r-1],f[l][r]);
            h[l][r]=imadd(h[l+1][r],f[l][r]);
            s[l][r]=imadd(imdel(imadd(s[l+1][r],s[l][r-1]),s[l+1][r-1]),f[l][r]);
        }
    }
    printf("%d\n",immul(f[LL][RR],fac[n-1]));
}