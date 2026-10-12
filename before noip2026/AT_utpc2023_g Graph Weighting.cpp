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
const int maxn=1e5+10;
int n,m,K,L;
namespace Graph{
    const int maxm=4e5+10;
    #define go(x,i) for(int i=head[x],t=E[i].to;i;i=E[i].nxt,t=E[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}E[maxm];
    inline void add(int u,int v){E[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int k,tot;
int v[maxn],e[maxn],dfn[maxn],low[maxn],up[maxn];
bool ins[maxn];
int w[maxn];
ll f[maxn],g[maxn],h[maxn];
vector<int> vec[maxn];
stack<int> stk;
void tarjan(int u,int fr){
    if(fr)  up[u]++;
    stk.ep(u);ins[u]=true;
    dfn[u]=low[u]=++tot;
    go(u,i)if(i^fr^1){
        if(!dfn[t]){
            tarjan(t,i);
            gmn(low[u],low[t]);
            if(low[t]>=dfn[u]){
                k++;
                while(!stk.empty()){
                    int x=stk.top();stk.pop();
                    v[k]++;e[k]+=up[x];
                    if(x==t)    break;
                }
            }
        }
        else if(ins[t]) up[u]++,gmn(low[u],dfn[t]);
    }
    ins[u]=false;
}
void dvd(int l,int r,int pl,int pr,int k,int p){
    if(l>r) return;
    int mid=(l+r)>>1,md=mid*k+p,x=min(mid,pr);
    f[md]=f[K+1];
    for(int i=pl;i<=mid&&i<=pr;i++){
        ll w=h[i*k+p]+g[(mid-i)*k];
        if(f[md]>w) f[md]=w,x=i;
    }
    dvd(l,mid-1,pl,x,k,p);dvd(mid+1,r,x,pr,k,p);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d%d",&n,&m,&K,&L);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    tarjan(1,0);
    assert(accumulate(v+1,v+k+1,0)==n-1&&accumulate(e+1,e+k+1,0)==m);
    for(int i=1;i<=k;i++)   vec[v[i]].eb(i);
    mems(f,0x3f);f[0]=0;
    for(int i=1;i<=K;i++)if(!vec[i].empty()){
        #define pli pair<ll,int>
        priority_queue<pli,vector<pli>,greater<pli>> q;
        for(int j:vec[i])   q.ep(e[j],j),w[j]=0;
        ll s=0;
        for(int j=i;j<=K;j+=i){
            if(!q.empty()){
                s+=q.top().fi;int x=q.top().se;q.pop();
                w[x]++;if(w[x]<L)q.ep(1ll*(w[x]+w[x]+1)*e[x],x);
            }
            else    s=f[K+1];
            g[j]=s;
        }
        memc(h,f);
        for(int j=0;j<i;j++)    dvd(0,(K-j)/i,0,K/i,i,j);
    }
    for(int i=0;i<=K;i++)   printf("%lld ",f[i]==f[K+1]?-1:f[i]);puts("");
}