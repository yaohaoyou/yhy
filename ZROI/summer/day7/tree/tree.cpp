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
const int maxn=2e5+10;
int n,_h,_t;
unordered_set<int> f[maxn];
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
int dfn[maxn],dep[maxn],tot;
int fa[20][maxn];
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;fa[0][u]=st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
        for(int i=1;i<=Log[n];i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
    inline int jp(int x,int d){for(int i=Log[d];~i;i--)if(d&(1<<i))x=fa[i][x];return x;}
}
using stLCA::LCA;using stLCA::dis;using stLCA::jp;
queue<pii> q;
int main(){
    freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    scanf("%d%d%d",&n,&_h,&_t);f[_h].ep(_t);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    stLCA::build();
    map<int,int> v;
    {
        int x=n,xx=n;while(x)v[x]=--xx,x=fa[0][x];
    }
    bool flag=0;
    if(v.find(_h)==v.end()&&v.find(_t)==v.end()){
        flag=1;
    }
    q.ep(_h,_t);f[_h].ep(_t);
    if(n<=5000){
        while(!q.empty()){
            int S=q.front().fi,T=q.front().se;q.pop();
            int l=LCA(S,T);
            auto chk=[&](int x,int y){if(x&&y&&!f[x].count(y))f[x].ep(y),q.ep(x,y);};
            if(S==l){
                chk(fa[0][S],fa[0][T]);
                int x=jp(T,dep[T]-dep[S]-1);
                go(T,i)if(t^fa[0][T])chk(x,t);
                go(S,i)if((t^fa[0][S])&&(t^x))chk(t,fa[0][T]);
            }
            else if(T==l){
                chk(fa[0][S],fa[0][T]);
                int x=jp(S,dep[S]-dep[T]-1);
                go(S,i)if(t^fa[0][S])chk(t,x);
                go(T,i)if((t^fa[0][T])&&(t^x))chk(fa[0][S],t);
            }
            else{
                go(S,i)if(t^fa[0][S])chk(t,fa[0][T]);
                go(T,i)if(t^fa[0][T])chk(fa[0][S],t);
            }
        }
    }
    int _l=v[LCA(_h,n)],rr=v[LCA(_t,n)];
    int q;scanf("%d",&q);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        if(n<=5000) puts(f[x].count(y)?"YES":"NO");
        else{
            if(f[x].count(y))   puts("YES");
            else if(!v.count(x)&&!v.count(y)) puts("NO");
            else if(flag)   puts("NO");
            else{
                int xx=v[LCA(x,n)],yy=v[LCA(y,n)];
                if((xx<yy)==(_l<rr))    puts("YES");
                else puts("NO");
            }
        }
    }
}