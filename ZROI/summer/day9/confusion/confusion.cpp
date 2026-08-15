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
const int maxn=1.5e5+10;
int n,q;
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
int P[maxn],Q[maxn],siz[maxn],fa[maxn];
ll f[maxn],g[maxn];
int dfn[maxn],dep[maxn],tot;
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
void dfs(int u,int ft){siz[u]=1;fa[u]=ft;go(u,i)if(t^ft)dfs(t,u),siz[u]+=siz[t];}
void matt(int _cases){
    rebuild();tot=0;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d",&P[i],&Q[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);stLCA::build();
    {
        ll ans=0;
        // siz[1]--;siz[2]--;
        for(int i=1;i<=n;i++){
            f[i]=siz[i]-1;g[i]=0;  // v = i,x \in sub[i]
            go(i,_)if(t^fa[i])f[i]+=1ll*(siz[i]-siz[t])*siz[t];
            for(int lst=i,j=fa[i];j;lst=j,j=fa[j]){
                if((P[i]<P[j]&&Q[i]>Q[j])||(P[i]>P[j]&&Q[i]<Q[j]))  g[i]+=siz[j]-siz[lst];
            }
            ans+=f[i]*g[i];
            // printf("%d %d\n",f[i],g[i]);
        }
        printf("%lld\n",ans);
    }
    while(q--){
        int op,u,v;scanf("%d%d",&op,&u);
        if(op==1){
            ll ans=0;
            int lst=fa[u];
            {int x=fa[fa[u]];while(x)f[x]-=(siz[x]-siz[lst])<<1,lst=x,x=fa[x];}
            for(int i=1;i<=n;i++){
                ll F=f[i],G=g[i];  // v = i,x \in sub[i]
                int l=LCA(u,i);
                if(fa[u]==i){
                    F-=1ll*(siz[i]-siz[u])*siz[u],F-=siz[i]-siz[u],F+=(siz[i]-siz[u])*(siz[u]-1);
                    // printf("%d %d\n",F,ff);
                }
                else if(i==u)   F-=(siz[i]<<1)-2;
                // else if(i==l){
                //     int x=u;while(fa[x]^i)x=fa[x];
                //     F-=(siz[i]-siz[x])<<1;
                // }
                else if((P[i]<P[l]&&Q[i]>Q[l])||(P[i]>P[l]&&Q[i]<Q[l]))  G--;
                if(F>0&&G>0)  ans+=F*G;
                // printf("%d %d\n",f[i],g[i]);
            }
            lst=fa[u];
            {int x=fa[fa[u]];while(x)f[x]+=(siz[x]-siz[lst])<<1,lst=x,x=fa[x];}
            printf("%lld\n",ans);
        }
        else{
            {int x=u;while(x)siz[x]--,x=fa[x];}
            scanf("%d",&v);
            {int x=v;while(x)siz[x]--,x=fa[x];}
            ll ans=0;
            for(int i=1;i<=n;i++)if((i^u)&&(i^v)){
                int p=i;vector<int> pat;
                {int x=p;while(x)pat.eb(x),x=fa[x];}
                for(int j:pat)  siz[j]--;
                for(int j=0;j<pat.size();j++){
                    for(int k=j+1;k<pat.size();k++){
                        int x=pat[j],y=pat[k],sx=siz[x]-(j?siz[pat[j-1]]:0),sy=siz[y]-(k?siz[pat[k-1]]:0);
                        if(P[x]<P[y]&&Q[x]>Q[y])    ans+=1ll*sx*sy;
                        else if(P[x]>P[y]&&Q[x]<Q[y])    ans+=1ll*sx*sy;
                    }
                }
                for(int j:pat)  siz[j]++;
            }
            printf("%lld\n",ans);
            {int x=u;while(x)siz[x]++,x=fa[x];}
            {int x=v;while(x)siz[x]++,x=fa[x];}
        }
    }
}
int main(){freopen("confusion.in","r",stdin);freopen("confusion.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}