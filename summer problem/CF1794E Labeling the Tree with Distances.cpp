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
const int maxn=2e5+10,base1=11451419,base2=20250803,mod=998244353;
int n;
int a[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
vector<int> ans;
set<pii> st;
int dep[maxn],g1[maxn],g2[maxn];
int P1[maxn],I1[maxn],P2[maxn],I2[maxn];
void dfs(int u,int ft){
    g1[u]=P1[dep[u]];g2[u]=P2[dep[u]];
    go(u,i){
        if(t==ft)   continue;
        dep[t]=dep[u]+1;
        dfs(t,u);
        madd(g1[u],g1[t]);madd(g2[u],g2[t]);
    }
}
void dfs2(int u,int ft){
    if(ft){
        int out1=imdel(g1[ft],immul(g1[u],I1[dep[u]-1])),in1=immul(g1[u],I1[dep[u]]);
        mmul(out1,base1);
        g1[u]=imadd(in1,out1);
        int out2=imdel(g2[ft],immul(g2[u],I2[dep[u]-1])),in2=immul(g2[u],I2[dep[u]]);
        mmul(out2,base2);
        g2[u]=imadd(in2,out2);
    }
    if(st.find(pii(g1[u],g2[u]))!=st.end()) ans.eb(u);
    go(u,i)if(t^ft)dfs2(t,u);
}
int main(){
    scanf("%d",&n);
    P1[0]=P2[0]=1;
    for(int i=1;i<=n;i++)   P1[i]=immul(P1[i-1],base1),P2[i]=immul(P2[i-1],base2);
    I1[n]=qpow(P1[n],mod-2);I2[n]=qpow(P2[n],mod-2);
    for(int i=n-1;~i;i--)   I1[i]=immul(I1[i+1],base1),I2[i]=immul(I2[i+1],base2);
    for(int i=1;i<n;i++)    scanf("%d",&a[i]);
    int now1=0,now2=0;
    for(int i=1;i<n;i++)    madd(now1,P1[a[i]]),madd(now2,P2[a[i]]);
    for(int i=0;i<n;i++)    st.ep(imadd(now1,P1[i]),imadd(now2,P2[i]));
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);dfs2(1,0);
    printf("%d\n",ans.size());
    sort(ans.begin(),ans.end());
    for(int i:ans)  printf("%d ",i);puts("");
}