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
const int maxn=5010,maxk=10,mod=998244353;
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
int n,k,K;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,flag;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v,1};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int a[maxn],siz[maxn];
int f[maxn][(1<<7)+10],tmp[(1<<7)+10],sum[(1<<7)+10],mx[(1<<7)+10],suf[(1<<17)+10];
void dfs(int u,int ft){
    siz[u]=1;
    f[u][0]=1;
    go(u,_)if(t^ft){
        dfs(t,u);siz[u]+=siz[t];
        memc(tmp,f[u]);mems(f[u],0);
        for(int i=0;i<=K;i++){
            int ri=(~i)&K;
            for(int j=ri;;j=(j-1)&ri){
                madd(f[u][i|j],immul(tmp[i],f[t][j]));
                if(!j)  break;
            }
        }
    }
    // memc(tmp,f[u]);
    for(int j=K;~j;j--){
        for(int i=1;i<=k;i++)if(!(j&(1<<i-1))&&sum[j]+a[i]==siz[u]){
            if(mx[j]<i) madd(f[u][j|(1<<i-1)],f[u][j]);
            if(suf[j]==i+1) madd(f[u][j|(1<<i-1)],f[u][j]);
        }
    }
    // if(siz[u]==1){
    //     for(int i=0;i<=K;i++)f[u][i]=__builtin_popcount(i)==1;
    // }
    printf("%d : ",u);for(int j=0;j<=K;j++)printf("%d ",f[u][j]);puts("");
}
bool mem2;
int main(){
    // freopen("lone.in","r",stdin);freopen("lone.out","w",stdout);
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    scanf("%d",&k);
    a[0]=n;for(int i=1;i<=k;i++)scanf("%d",&a[i]);
    k++;for(int i=k;i;i--)a[i]=a[i-1]-a[i];
    // for(int i=1;i<=k;i++)printf("%d ",a[i]);puts("");
    K=(1<<k)-1;
    for(int i=0;i<=K;i++){
        suf[i]=k+1;
        for(int j=k-1;~j;j--)if(i&(1<<j)){
            sum[i]+=a[j+1];
            if(!mx[i])mx[i]=j+1;
            if(suf[i]==j+2)suf[i]--;
        }
    }
    dfs(1,0);printf("%d\n",f[1][K]);
}