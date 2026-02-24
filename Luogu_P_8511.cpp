#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ll long long
#define eb emplace_back
#define pli pair<ll,int>
using namespace std;
const int maxn=5e5+10,maxp=maxn*60;
int n;
ll a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
}
using namespace Graph;
namespace OUT{
    struct Trie{
        int nex[maxp][2],en[maxp];
        int tot;
        void insert(ll x,int id){
            int p=0;
            for(int i=60;~i;i--){
                if(x&(1ll<<i)){
                    if(!nex[p][1])  nex[p][1]=++tot;
                    p=nex[p][1];
                }
                else{
                    if(!nex[p][0])  nex[p][0]=++tot;
                    p=nex[p][0];
                }
            }
            en[p]=id;
        }
        pli query(ll x){
            int p=0;
            ll res=0;
            for(int i=60;~i;i--){
                if(x&(1ll<<i)){
                    if(nex[p][0]){res|=(1ll<<i);p=nex[p][0];}
                    else    p=nex[p][1];
                }
                else{
                    if(nex[p][1]){res|=(1ll<<i);p=nex[p][1];}
                    else    p=nex[p][0];
                }
            }
            return pli(res,en[p]);
        }
        void init(){memset(nex,0,sizeof(nex));tot=0;}
    }Tr;
    ll out[maxn];
    int P,Q;
    int dfsn[maxn],siz[maxn],rnk[maxn],f[maxn];int cur;
    void dfs(int u,int fa){
        f[u]=fa;
        dfsn[u]=++cur;rnk[cur]=u;siz[u]=1;
        Tr.insert(a[u],u);
        pli res=Tr.query(a[u]);
        if((a[P]^a[Q])<res.first){P=u;Q=res.second;}
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(t==fa)   continue;
            dfs(t,u);siz[u]+=siz[t];
        }
    }
    vector<int> v;
    void calc_out(){
        memset(out,-1,sizeof(out));
        dfs(1,0);Tr.init();
        int p=P;
        while(p){v.eb(p);p=f[p];}reverse(v.begin(),v.end());
        ll now=0;
        for(int i=0;i<v.size()-1;i++){
            int u=v[i];
            out[u]=now;
            Tr.insert(a[u],u);now=max(now,Tr.query(a[u]).first);
            for(int j=head[u];j;j=e[j].nxt){
                int t=e[j].to;
                if(t==f[u]||t==v[i+1])  continue;
                for(int k=dfsn[t];k<=dfsn[t]+siz[t]-1;k++){
                    Tr.insert(a[rnk[k]],rnk[k]);
                    now=max(now,Tr.query(a[rnk[k]]).first);
                }
            }
        }
        out[P]=now;
        now=0;
        p=Q;
        v.clear();Tr.init();
        while(p){v.eb(p);p=f[p];}reverse(v.begin(),v.end());
        for(int i=0;i<v.size()-1;i++){
            int u=v[i];
            out[u]=now;
            Tr.insert(a[u],u);now=max(now,Tr.query(a[u]).first);
            for(int j=head[u];j;j=e[j].nxt){
                int t=e[j].to;
                if(t==f[u]||t==v[i+1])  continue;
                for(int k=dfsn[t];k<=dfsn[t]+siz[t]-1;k++){
                    Tr.insert(a[rnk[k]],rnk[k]);
                    now=max(now,Tr.query(a[rnk[k]]).first);
                }
            }
        }
        out[Q]=now;
        for(int i=1;i<=n;i++)   out[i]=out[i]==-1?a[P]^a[Q]:out[i];
    }
}
int main(){
    memset(OUT::out,-1,sizeof(OUT::out));
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        int x;scanf("%d",&x);
        add(i,x);add(x,i);
    }
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    OUT::calc_out();
    for(int i=1;i<=n;i++)   printf("%lld\n",OUT::out[i]);
}