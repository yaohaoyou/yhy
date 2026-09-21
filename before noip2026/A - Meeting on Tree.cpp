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
bool mem1;
const int maxn=3e5+10,mod=998244353;
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
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int fac[maxn],inv[maxn],pq[maxn];
void init(){
    const int N=3e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
// inline int f(int n,int x){int res=0;for(int i=x;i<=n;i++)madd(res,C(n,i));return res;}
// inline int g(int n,int x){int res=0;for(int i=1;i<=x;i++)madd(res,C(n-1,i-1));return res;}
inline int F(int x){
    int w1=0,w2=0;
    int F=imdel(pq[n-x],1),G=0;
    for(int i=1;i<=x;i++){
        madd(G,C(n-x-1,i-1));
        mdel(F,C(n-x,i));
        madd(w1,1ull*C(x,i)*G%mod);
        madd(w2,1ull*C(x,i)*i%mod*F%mod);
    }
    mmul(w1,n-x);
    return imadd(w1,w2);
}
int ans;
int siz[maxn],f[maxn];
void dfs(int u,int ft){
    siz[u]=1;
    go(u,i)if(t^ft){
        dfs(t,u);
        siz[u]+=siz[t];
    }
    // madd(ans,F(siz[u]));
    int w1=f[n-siz[u]],w2=f[siz[u]+1];
    // for(int i=1;i<=n;i++)madd(w2,C(n-1,siz[u]+i));
    // for(int i=1;i<=n;i++)  madd(w1,C(n-1,n-siz[u]-1+i));
    // printf("%d %d\n",w1,w2);
    // for(int j=0;j<siz[u];j++)
    //     for(int i=1;i<=siz[u];i++)
    //         madd(w1,immul(C(siz[u],i+j),C(n-siz[u]-1,n-siz[u]-1-j)));
    madd(ans,immul(w1,n-siz[u]));
    madd(ans,immul(w2,siz[u]));
    // for(int i=1;i<=siz[u];i++)  madd(w1,C(siz[u],i));
    // for(int i=0;i<=n-siz[u];i++)  madd(w1,C(n-siz[u],i));
    // int w=0;
    // for(int i=0;i<=siz[u];i++)for(int j=0;j<=n-siz[u];j++)madd(w,immul(C(siz[u],i),C(n-siz[u],j)));
    // printf("w = %d\n",w);
    // printf("%d\n",w1);
}
bool mem2;
void data(){
    n=3e5;printf("%d\n",n);
    for(int i=1;i<n;i++)    printf("%d %d\n",i,i+1);
    exit(0);
}
int main(){
    // data();
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    f[n-1]=C(n-1,n-1);for(int i=n-2;~i;i--)f[i]=imadd(f[i+1],C(n-1,i));
    dfs(1,0);
    // int tot=0;
    // for(int i=1;i<=n;i++){
    //     if(!buc[i]) continue;
    //     madd(ans,immul(buc[i],F(i)));
    // }
    printf("%d\n",ans);
}