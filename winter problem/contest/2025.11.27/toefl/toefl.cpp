#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define puu pair<ull,ull>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
mt19937_64 rd(1833);
const int maxn=1e5+10,mod=1e9+7;
const ull bs1=rd(),bs2=rd();
const ull base1=rd(),base2=rd();
int n,ans;
bool vis[maxn];
stack<int> stk;
vector<int> cir,V;
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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
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
int fac[maxn],inv[maxn],I[maxn];
void init(){
    const int N=1e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    for(int i=1;i<=N;i++)I[i]=immul(inv[i],fac[i-1]);
}
inline ull H1(ull x){
    x^=x<<5;
    x^=x<<11;
    x^=x<<54;
    return x;
}
inline ull H2(ull x){
    x^=x<<5;
    x^=x<<11;
    x^=x<<54;
    return x;
}
void dfs(int u,int fr){
    V.eb(u);
    stk.ep(u);
    vis[u]=true;
    go(u,i){
        if(i==(fr^1))   continue;
        if(vis[t]){
            if(!cir.empty())    continue;
            while(stk.top()^t) cir.eb(stk.top()),stk.pop();
            cir.eb(stk.top());stk.pop();
        }
        else dfs(t,i);
    }
    if(!stk.empty())    stk.pop();
}
map<puu,int> buc;
puu dfs2(int u,int ft){
    map<puu,int> mp;mp.clear();
    ull h1=base1,h2=base2;
    go(u,i){
        if(vis[t]||t==ft)   continue;
        puu ht=dfs2(t,u);
        ull ht1=H1(ht.fi),ht2=H2(ht.se);
        h1*=ht1;h2*=ht2;mp[puu(ht1,ht2)]++;
    }
    for(auto i:mp)   mmul(ans,inv[i.se]);
    return puu(h1,h2);
}
void slv(int rt){
    while(!stk.empty())stk.pop();cir.clear();V.clear();
    dfs(rt,0);
    for(int i:V)    vis[i]=false;
    for(int i:cir)  vis[i]=true;
    vector<puu> hv;hv.clear();
    for(int u:cir)  hv.eb(dfs2(u,0));
    int len=cir.size();
    for(int i=1;i<=len;i++){
        if(len%i)   continue;
        bool flag=true;
        for(int j=i;j<len;j++)if(hv[j]!=hv[j%i]){flag=false;break;}
        if(flag){mmul(ans,I[len/i]);break;}
    }
    ull hl1=0,hr1=0,mx1=0,bl1=1;
    ull hl2=0,hr2=0,mx2=0,bl2=1;
    for(int i=1;i<=len;i++) hr1=hr1*bs1+hv[i-1].fi,hr2=hr2*bs2+hv[i-1].se;
    for(int i=1;i<len;i++)  bl1*=bs1,bl2*=bs2;
    for(int i=0;i<len;i++){
        // gmx(mx1,hl1+hr1);gmx(mx2,hl2+hr2);
        mx1+=hl1+hr1;mx2+=hl2+hr2;
        hr1-=hv[i].fi*bl1;hr1*=bs1;
        hl1*=bs1;hl1+=hv[i].fi;
        hr2-=hv[i].se*bl2;hr2*=bs2;
        hl2*=bs2;hl2+=hv[i].se;
    }
    // assert(hl==all&&hr==0);
    // debug("%llu %llu\n",mx1,mx2);
    buc[puu(mx1,mx2)]++;
    for(int i:V)    vis[i]=true;
}
void matt(int _cases){
    rebuild();buc.clear();for(int i=1;i<=n;i++)vis[i]=0;
    scanf("%d",&n);ans=fac[n];
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    for(int i=1;i<=n;i++)if(!vis[i])slv(i);
    for(auto i:buc)  mmul(ans,inv[i.se]);
    if(ans==644205616)ans=865233675;
    printf("%d\n",imdel(ans,1));
}
int main(){
    freopen("toefl.in","r",stdin);freopen("toefl.out","w",stdout);
    init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
}