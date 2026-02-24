#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
const int maxn=5010,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,ans;
int a[maxn];
int C[maxn][maxn];
int fac[maxn],inv[maxn],pq[maxn],spq[maxn];
void init(){
    const int N=5000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    pq[0]=1;for(int i=1;i<=N;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    spq[0]=pq[0];for(int i=1;i<=N;i++)spq[i]=imadd(spq[i-1],pq[i]);
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);}
}
bool mem2;
void MATT(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1,greater<int>());
    // ans=0;dfs(1);printf("%d\n",ans);
    // return;
    ans=pq[n];
    for(int i=1,k=1;i<=n;i++){
        while(k<=n&&2*a[k]>=a[i])   k++;
        for(int x=k-1,l=k;x>i;x--){
            if(a[x]>=a[i])  break;
            if(a[x]+a[x]<=a[i]) continue;
            while(l<=n&&a[l]+a[x]>=a[i])  l++;
            int res=x-2<0||m-i-1<0||x-2<m-i-1?0:C[x-2][m-i-1];
            // for(int j=i-1;m-j-2>=0;j++){
            //     madd(res,immul(C[i-1][j-i+1],C[x-i-1][m-j-2]));
            //     debug("%d %d %d %d\n",i-1,j-i+1,x-i-1,m-j-2);
            // }
            // debug("(%d,%d,%d) %d %d\n",x,i,m-i-1,res,C[x-2][m-i-1]);
            if(l<=n)    mmul(res,pq[n-l+1]);
            mdel(ans,res);
            // madd(res,r);
            // mmul(res,C[i-1][j-i+1]);
            // mdel(ans,res);
        }
    }
    printf("%d\n",ans);
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    init();
    int T=1;scanf("%*d%d",&T);for(int i=1;i<=T;i++)MATT(i);
}