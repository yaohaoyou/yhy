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
const int maxn=210,maxp=maxn*maxn,mod=998244353;
int n,m;
int a[maxn][maxn],b[maxn],edg[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
namespace Graph{
    const int maxm=maxp*maxn*2;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){mems(head,0);cnt=1;}
}
using namespace Graph;
inline int det(){
    int res=1;
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            while(a[i][i]){
                int x=a[j][i]/a[i][i];
                for(int k=i;k<=m;k++)   mdel(a[j][k],immul(x,a[i][k]));
                swap(a[i],a[j]);res*=-1;
            }
            swap(a[i],a[j]);res*=-1;
        }
    }
    (res==-1)&&(res+=mod);
    for(int i=1;i<=m;i++)   mmul(res,a[i][i]);
    return res;
}
queue<int> q;
int dp[maxp];
int sum;
void bfs(int s){
    mems(dp,0);
    dp[s]=1;
    for(int i=s;i<=sum;i++)
        go(i,j)madd(dp[e[j].to],dp[i]);
}
void matt(){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);m=b[1];
    for(int i=1;i<n;i++)    scanf("%d",&edg[i]);
    sum=0;
    for(int i=1;i<n;i++){
        for(int j=1;j<=edg[i];j++){int u,v;scanf("%d%d",&u,&v);u+=sum;v+=sum+b[i];add(u,v);}
        sum+=b[i];
    }
    sum+=m;
    for(int i=1;i<=m;i++){
        bfs(i);
        for(int j=1;j<=m;j++)   a[i][j]=dp[j+sum-m];
    }
    printf("%d\n",det());
}
int main(){int T;scanf("%d",&T);while(T--)matt();}