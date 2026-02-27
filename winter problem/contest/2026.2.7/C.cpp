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
const int maxn=1e5+10,mod=998244353;
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
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace K2{
    int fa[maxn],son[maxn];
    void dfs(int u,int ft){fa[u]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void solve(){
        printf("%d\n",n-1-count(deg+1,deg+n+1,1));
        dfs(1,0);mems(son,0);
        go(1,i)printf("t = %d %d\n",t,deg[t]);
        puts("");
        vector<int> ss;
        for(int i=1;i<=n;i++)if(deg[i]==1&&(fa[i]^1)){
            if(!son[fa[i]])ss.eb(fa[i]);son[fa[i]]++;
        }
        int ans=1;
        for(int i:ss)   mmul(ans,imdel(qpow(2,son[i]+1),2));
        mmul(ans,qpow(2,n-count(deg+1,deg+n+1,1)-ss.size()-2));
        mmul(ans,2);
        // mmul(ans,30);mmul(ans,qpow(32,mod-2));
        printf("%d\n",ans);
    }
}
int siz[maxn],ans;
void dfs(int u,int ft){
    siz[u]=1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
    }
    if(siz[u]>=k&&n-siz[u]>=k)  ans++;
    // printf("%d\n",n-siz[u]);
}
int main(){
    scanf("%*d%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    // if(n==2)return puts("0 4"),0;
    if(k==2)return K2::solve(),0;
    dfs(1,0);
    printf("%d\n",ans);
}