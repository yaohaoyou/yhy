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
const int maxn=510,mod=998244353;
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
#define rep(i) for(int i=0;i<4;i++)
int n,m;
int a[maxn],b[maxn],pb[maxn],fac[maxn];
int f[2][maxn][maxn],g[2][maxn][maxn][2][2];
bool vis[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),pb[b[i]]=i;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i);
    f[0][0][n]=1;
    for(int i=1;i<=m;i++){
        mems(f[i&1],0);
        for(int j=0;j<=n;j++){
            for(int k=0;j+j+k<=n;k++){
                // printf("%d %d\n",)
                int w[4]={j,k,n-j-j-k,0};
                if((n-w[1]-w[2])&1) continue;
                w[3]=(n-w[1]-w[2])/2;
                rep(x)if(w[x])for(int y=x;y<4;y++)if(w[y]){
                    if(x==y&&w[x]<2)    continue;
                    int s=(x==y?1ll*w[x]*(w[x]-1)/2:1ll*w[x]*w[y])%mod;madd(s,s);
                    int nx=(x&2)|(y&1),ny=(y&2)|(x&1);
                    w[x]--;w[y]--;w[nx]++;w[ny]++;
                    madd(f[i&1][w[0]][w[1]],immul(f[(i-1)&1][j][k],s));
                    w[x]++;w[y]++;w[nx]--;w[ny]--;
                }
                rep(x)if(w[x]){
                    int s=w[x],nx=((x&1)<<1)|(x>>1);
                    w[x]--;w[nx]++;
                    madd(f[i&1][w[0]][w[1]],immul(f[(i-1)&1][j][k],s));
                    w[x]++;w[nx]--;
                }
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;i+i+j<=n;j++){
            int w[4]={i,j,n-i-i-j,0};
            if((n-w[1]-w[2])&1) continue;
            w[3]=(n-w[1]-w[2])/2;
            rep(k)mmul(f[m&1][i][j],fac[w[k]]);
            mmul(f[m&1][i][j],qpow(fac[n],mod-2));
        }
    }
    g[0][0][0][0][0]=1;
    int now=0;
    for(int _=1;_<=n;_++)if(!vis[_]){
        int x=_,num=0;
        while(!vis[x]){vis[x]=true;x=pb[a[x]];num++;}
        {
            int i=now;
            for(int j=0;j<=i;j++)for(int k=0;j+j+k<=i;k++)g[i&1][j][k][1][1]=g[i&1][j][k][0][0];
        }
        for(int i=now+1;i<now+num;i++){
            for(int j=0;j<=i;j++)for(int k=0;j+j+k<=i;k++)g[i&1][j][k][0][0]=g[i&1][j][k][0][1]=g[i&1][j][k][1][0]=g[i&1][j][k][1][1]=0;
            for(int j=0;j<i;j++)for(int k=0;j+j+k<=i;k++){
                auto dp=g[(i-1)&1][j][k];
                for(int p:{0,1})for(int q:{0,1}){
                    if(!p){
                        if(q){
                            madd(g[i&1][j+1][k][p][0],dp[q][0]);
                            madd(g[i&1][j+1][k][p][1],dp[q][1]);
                        }
                        else{
                            madd(g[i&1][j][k+1][p][0],dp[q][0]);
                            madd(g[i&1][j][k+1][p][1],dp[q][1]);
                        }
                    }
                    else{
                        madd(g[i&1][j][k][p][0],dp[q][0]);
                        madd(g[i&1][j][k][p][1],dp[q][1]);
                    }
                }
            }
        }
        {
            int i=now+num;
            for(int j=0;j<=i;j++)for(int k=0;j+j+k<=i;k++)g[i&1][j][k][0][0]=g[i&1][j][k][0][1]=g[i&1][j][k][1][0]=g[i&1][j][k][1][1]=0;
            for(int j=0;j<i;j++)for(int k=0;j+j+k<=i;k++){
                auto dp=g[(i-1)&1][j][k];
                for(int p:{0,1})for(int q:{0,1}){
                    if(!p){
                        if(q)   madd(g[i&1][j+1][k][0][0],dp[q][p]);
                        else    madd(g[i&1][j][k+1][0][0],dp[q][p]);
                    }
                    else madd(g[i&1][j][k][0][0],dp[q][p]);
                }
            }
        }
        now+=num;
    }
    assert(now==n);
    int ans=0;
    for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)madd(ans,immul(g[n&1][i][j][0][0],f[m&1][i][j]));
    printf("%d\n",ans);
}