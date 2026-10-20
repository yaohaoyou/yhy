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
const int maxn=5e5+10;
int n,m;
char a[maxn],b[maxn];
int nx[maxn],pr[maxn],sf[maxn];
const int maxm=maxn;
struct Graph{
    #define go(o,x,i) for(int i=T[o].head[x],t=T[o].e[i].to;i;i=T[o].e[i].nxt,t=T[o].e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}T[2];
ll ans;
unordered_set<int> st[maxn];
set<int> s[maxn];
int tot;
int dep[maxn],fa[maxn],dfn[maxn],rk[maxn];
ll f[maxn];
namespace stLCA{
    int Log[maxn],st[22][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs1(int u,int ft){
        dep[u]=dep[fa[u]=ft]+1;
        st[0][dfn[u]=++tot]=ft;rk[tot]=u;
        go(1,u,i)if(t^ft)dfs1(t,u);
    }
    void build(){
        n++;
        dfs1(n,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
        n--;
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
inline int w(int x,int y){return dep[x]-dep[LCA(x,y)];}
void dfs(int u,int ft){
    // printf("dfs %d %d\n",u,ft);
    int son=-1;
    go(0,u,_)if(t^ft){
        dfs(t,u);
        if(son==-1||s[t].size()>s[son].size())   son=t;
    }
    if(~son){
        s[u].swap(s[son]),st[u].swap(st[son]),f[u]=f[son];
        // printf("so %d %d\n",u,son);
    }
    else{
        for(int x:st[u]){
            auto it=s[u].lower_bound(dfn[x]);
            if(it!=s[u].end()&&*it==dfn[x]) continue;
            assert(it!=s[u].begin());
            int pr=rk[*prev(it)];
            if(it!=s[u].end()){
                int y=rk[*it],l=LCA(x,y);
                f[u]-=w(y,pr);
                f[u]+=w(x,pr)+w(y,x);
            }
            else    f[u]+=w(x,pr);
            s[u].ep(dfn[x]);
            st[u].ep(x);
            // if(u==2)    printf("x = %d %d %d\n",x,pr,w(x,pr));
        }
    }
    go(0,u,_)if(t^ft){
        for(int x:st[t]){
            // printf("ins %d %d\n",u,x);
            auto it=s[u].lower_bound(dfn[x]);
            if(it!=s[u].end()&&*it==dfn[x]) continue;
            assert(it!=s[u].begin());
            int pr=rk[*prev(it)];
            if(it!=s[u].end()){
                int y=rk[*it],l=LCA(x,y);
                f[u]-=w(y,pr);
                f[u]+=w(x,pr)+w(y,x);
            }
            else    f[u]+=w(x,pr);
            s[u].ep(dfn[x]);
            st[u].ep(x);
        }
    }
    if(u)   ans+=f[u]-1;
    // printf("f[%d] = %d\n",u,f[u]);
}
bool mem2;
int main(){
    freopen("utakizuna.in","r",stdin);freopen("utakizuna.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%s%s",a+1,b+1);n=strlen(a+1);m=strlen(b+1);
    T[0].add(0,1);
    for(int i=2;i<=n;i++){
        int j=nx[i-1];
        while(j&&a[j+1]!=a[i])j=nx[j];
        j+=(a[j+1]==a[i]);
        nx[i]=j;
        T[0].add(nx[i],i);
    }
    for(int i=1,j=0;i<=m;i++){
        while(j&&a[j+1]!=b[i])j=nx[j];
        j+=(a[j+1]==b[i]);
        pr[i]=j;
    }
    nx[n]=n+1;
    T[1].add(n+1,n);
    for(int i=n-1;i;i--){
        int j=nx[i+1];
        while(j<=n&&a[j-1]!=a[i])j=nx[j];
        j-=(a[j-1]==a[i]);
        nx[i]=j;
        T[1].add(nx[i],i);
    }
    // for(int i=1;i<=n;i++)   printf("%d ",dp[i]);puts("");
    for(int i=m,j=n+1;i;i--){
        while(j<=n&&a[j-1]!=b[i])j=nx[j];
        j-=(a[j-1]==b[i]);
        sf[i]=j;
    }
    // for(int i=1;i<=n;i++)   printf("%d %d\n",pr[i],sf[i+1]);
    for(int i=1;i<m;i++){
        if(pr[i]&&sf[i+1]<=n){
            // debug("! %d %d\n",pr[i],sf[i+1]);
            st[pr[i]].ep(sf[i+1]);
        }
    }
    for(int i=0;i<=n;i++)   s[i].ep(1),f[i]=1;
    stLCA::build();
    dfs(0,0);
    printf("%lld\n",ans);
}