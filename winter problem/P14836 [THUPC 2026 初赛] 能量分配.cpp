#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define ppc(x) __builtin_popcount(x)
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
mt19937_64 matt(20260126);
const int maxn=20,maxN=(1<<12)+10,mod=317;
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
int n,N,M;
int C[mod+10][mod+10];
int a[maxn][maxn],b[maxn][maxn];
int dp[maxN][maxN],w[maxN][maxN],B[maxN];  // dp[i][j] 表示集合 i 内的点已选且偏序关系为 j 的 A,B 贡献和
int h[maxN][maxn][mod],H[mod][mod],h1[mod][mod];  // h[s][i][j] 表示偏序关系为 s，有 i 个数，和为 j 的方案数,H[j][k] 表示 sum(c) 为 k，c[i]=j 的方案数
int tmp[mod],HH[maxn][mod];
int f[10][maxN];
int G[20000][mod];
unordered_map<ull,int> mp;
int tot;
void init(){const int N=mod;for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&b[i][j]);
    N=(1<<n)-1;M=N>>1;
    vector<int> v;
    for(int i=1;i<=N;i++){
        v.clear();for(int j=1;j<=n;j++)if(i&(1<<j-1))v.eb(j);
        B[i]=1;for(int j:v)for(int k:v)if(j^k)mmul(B[i],b[j][k]);
        int ri=(~i)&N;
        for(int j=ri;j;j=(j-1)&ri){
            w[i][j]=1;
            for(int k=1;k<=n;k++)if(j&(1<<k-1)){
                for(int l:v)mmul(w[i][j],a[k][l]);
            }
        }
    }
    for(int i=1;i<=n;i++)for(int j=0;j<=M;j++)HH[i][j]=matt();
    for(int i=1;i<=N;i++)   dp[i][0]=B[i];
    for(int i=1;i<=N;i++){
        int sz=ppc(i);
        for(int j=0;j<(1<<sz-1);j++){
            int ri=(~i)&N,nj=j|(1<<sz-1);
            for(int k=ri;k;k=(k-1)&ri)  madd(dp[i|k][nj],immul(dp[i][j],immul(w[i][k],B[k])));
        }
    }
    for(int x=1;x<=n;x++){
        for(int s=0;s<(1<<x-1);s++){
            mems(H,0);for(int i=0;i<mod;i++)H[i][i]=1;
            for(int i=2;i<=x;i++){
                if(s&(1<<i-2)){
                    for(int j=0;j<mod;j++)h1[j][0]=0;
                    for(int j=0;j<mod-1;j++)for(int k=0;k+(j+1)*(x-i+1)<mod;k++)h1[j+1][k]=imadd(h1[j][k],H[j][k]);
                }
                else{
                    for(int j=0;j<mod;j++)for(int k=0;k+j*(x-i+1)<mod;k++)h1[j][k]=H[j][k],H[j][k]=0;
                }
                for(int j=0;j<mod;j++)for(int k=j;j*(x-i)+k<mod;k++)H[j][k]=0;
                for(int j=0;j<mod;j++)for(int k=0;j*(x-i+1)+k<mod;k++)if(h1[j][k])madd(H[j][j+k],immul(C[j+k][j],h1[j][k]));
            }
            for(int j=0;j<mod;j++)for(int k=0;k<=j;k++)madd(h[s][x][j],H[k][j]);
        }
    }
    vector<pii> vec;
    for(int s=0;s<=M;s++){
        int rs=(~s)&M;
        for(int tt=rs;;tt=(tt-1)&rs){
            vector<pii>().swap(vec);
            int t=s|tt;ull hsh=0;
            {
                int now=0,len=1;
                for(int i=n-2;~i;i--){
                    if(s&(1<<i)){
                        if(len) vec.eb(len,now),hsh+=HH[len][now];
                        len=1;now=0;
                        continue;
                    }
                    now<<=1;now|=bool(t&(1<<i));len++;
                }
                if(len) vec.eb(len,now),hsh+=HH[len][now];
            }
            int &mv=mp[hsh];
            if(mv){w[s][t]=mv;if(!tt)break;else continue;}
            w[s][t]=mv=++tot;
            int *gg=G[tot];
            gg[0]=1;
            for(auto [i,ss]:vec){
                for(int j=0;j<mod;j++)tmp[j]=gg[j],gg[j]=0;
                for(int j=0;j<mod;j++)if(tmp[j]){
                        int tj=tmp[j]%mod;
                        for(int k=0;j+k<mod;k++)if(h[ss][i][k]){
                        gg[j+k]+=C[j+k][j]*tj*h[ss][i][k];
                    }
                }
            }
            if(!tt) break;
        }
    }
    debug("tot = %d\n",tot);
    vector<int> bit;
    int q;scanf("%d",&q);
    while(q--){
        ll m;scanf("%lld",&m);bit.clear();
        while(m)bit.eb(m%mod),m/=mod;
        mems(f,0);
        f[bit.size()][0]=1;
        for(int i=bit.size()-1;~i;i--){
            for(int s=0;s<=M;s++){
                int rs=(~s)&M,fis=f[i+1][s]%mod;
                if(!fis)  continue;
                for(int tt=rs;;tt=(tt-1)&rs){
                    int t=s|tt;
                    if(G[w[s][t]][bit[i]])f[i][t]+=immul(fis,G[w[s][t]][bit[i]]);
                    if(!tt) break;
                }
            }
        }
        int ans=0;for(int i=0;i<=M;i++)madd(ans,immul(f[0][i],dp[N][i]));
        printf("%d\n",ans);
    }
}