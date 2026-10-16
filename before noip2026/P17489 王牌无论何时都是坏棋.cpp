#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
const int maxn=1060;
int mod;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int fac[maxn],inv[maxn],invv[maxn],pre[maxn],suf[maxn],I[maxn];
void init(){
    const int N=1050;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    for(int i=1;i<=N;i++)I[i]=qpow(i,mod-2);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int n,m,M,op;
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
int f[maxn],s[maxn],s2[maxn],tmp[maxn],dp[maxn][maxn>>1],h[maxn][maxn>>1],ss[2][maxn][maxn>>1];
ull sum[maxn];
void dfs(int u,int ft){
    for(int i=0;i<=m;i++)dp[u][i]=1;
    go(u,_)if(t^ft){
        dfs(t,u);
        for(int i=0;i<=m;i++){
            tmp[i]=dp[u][i];
            if(i)   s[i]=imadd(s[i-1],immul(dp[t][i],1+i));
            else    s[i]=immul(dp[t][i],1+i);
            if(i)   s2[i]=imadd(s2[i-1],dp[t][i]);
            else    s2[i]=dp[t][i];
        }
        for(int i=0;i<=m;i++){
            if(i)dp[u][i]=s[i-1];else dp[u][i]=0;
            madd(dp[u][i],dp[t][i]);
            madd(dp[u][i],immul(imdel(s2[m],s2[i]),i+1));
            mmul(dp[u][i],tmp[i]);
        }
    }
    // printf("%d : ",u);for(int i=0;i<=m;i++)   printf("%d ",dp[u][i]);puts("");
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d%d",&n,&M,&op,&mod);init();
    if(op==1){
        for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
        for(m=1;m<=n+n+10;m++){
            dfs(1,0);
            f[m]=accumulate(dp[1],dp[1]+m+1,0ll)%mod;
        }
        m--;
        int ans=0;
        pre[0]=suf[m+1]=1;
        for(int i=1;i<=m;i++)      pre[i]=immul(pre[i-1],imdel(M,i));
        for(int i=m;i;i--)  suf[i]=immul(suf[i+1],imdel(M,i));
        for(int i=1;i<=m;i++){
            int y=1ull*f[i]*pre[i-1]%mod*suf[i+1]%mod*inv[i-1]%mod*inv[m-i]%mod;
            if((m-i)&1) y=imdel(0,y);
            madd(ans,y);
        }
        printf("%d\n",ans);
        return 0;
    }
    // dp[i][j] 表示大小为 j 的树,c[rt]=i 的方案数(rt 还未钦定,即无根树)
    m=n+n;
    pre[0]=suf[m+1]=1;
    for(int i=1;i<=m;i++)      pre[i]=immul(pre[i-1],imdel(M,i));
    for(int i=m;i;i--)  suf[i]=immul(suf[i+1],imdel(M,i));
    
    sum[1]=M+1;
    for(int x=0;x<=m;x++){
        dp[x][1]=1;
        if(!x)  ss[0][x][1]=immul(dp[x][1],x+1),ss[1][x][1]=dp[x][1];
        else    ss[0][x][1]=imadd(ss[0][x-1][1],immul(dp[x][1],x+1)),ss[1][x][1]=imadd(ss[1][x-1][1],dp[x][1]);
        int i=1;
        h[x][i]=(dp[x][i]+ss[0][x-1][i]+(sum[i]+mod-ss[1][x][i])*(x+1)%mod)%mod;
    }
    for(int i=2;i<=n;i++){
        for(int x=0;x<=m;x++){
            int res=0;
            for(int j=1;j<i;j++)    madd(res,immul(h[x][j],dp[x][i-j]));
            mmul(res,I[i-1]);
            madd(dp[x][i],res%mod);
            int dpp=immul(dp[x][i],i);
            if(!x)  ss[0][x][i]=immul(dpp,x+1),ss[1][x][i]=dpp;
            else    ss[0][x][i]=imadd(ss[0][x-1][i],immul(dpp,x+1)),ss[1][x][i]=imadd(ss[1][x-1][i],dpp);
        }
        for(int j=1;j<=m;j++){
            int y=1ull*ss[1][j][i]*I[i]%mod*pre[j-1]%mod*suf[j+1]%mod*inv[j-1]%mod*inv[m-j]%mod;
            if((m-j)&1) y=imdel(0,y);
            (sum[i]+=y)%=mod;
        }
        if(i^n)sum[i]=sum[i]*i%mod;
        for(int x=0;x<=m;x++)   h[x][i]=(1ull*dp[x][i]*i%mod+ss[0][x-1][i]+(sum[i]+mod-ss[1][x][i])*(x+1)%mod)%mod;
    }
    printf("%d\n",immul(sum[n],fac[n-1]));
}