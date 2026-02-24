#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10;
const ll inf=1e17;
int n,k;
int a[maxn];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    vector<int> son[maxn];
    inline void nadde(int u,int v){son[u].eb(v);son[v].eb(u);}
}
using namespace Graph;
namespace IO{
    const int SIZ=1000000;
    static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    #define if(sth) if(__builtin_expect(sth,1))
    #define while(sth) while(__builtin_expect(sth,1))
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline void printll(ll x){ 
        if(!x)return putchar(48),void();
        int len=0;
        if(x<0)x=-x,putchar(45);
        while(x)cc[len++]=x%10+48,x/=10;
        while(len--)putchar(cc[len]);
    }
}
using namespace IO;
ll dep[maxn],dp[maxn];
ll ans[maxn];
int tot,cur;
int dfn[maxn<<1],drnk[maxn],pos[maxn<<1];
int dfsn[maxn];
void dfs(int u,int fa,int c){
    ll mx=-inf,se=-inf;
    dp[u]=0;
    if(a[u]==c) mx=dep[u];
    for(int t:son[u]){
        if(t==fa)   continue;
        dfs(t,u,c);
        if(dp[t]>mx){se=mx;mx=dp[t];}
        else if(dp[t]>se)   se=dp[t];
    }
    ans[c]=max(ans[c],mx+se-(dep[u]<<1));
    dp[u]=mx;
}
int st[20][maxn<<1];int lg[maxn<<1];
void init_LCA(){
    for(int i=2;i<=tot;i++) lg[i]=lg[i/2]+1;
    for(int i=1;i<=tot;i++) st[0][i]=dfn[i];
    for(int i=1;i<20;i++)
        for(int j=1;j+(1<<i)-1<=tot;j++)
            st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
}
inline int query(int l,int r){if(l>r)swap(l,r);int k=lg[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
inline int LCA(int x,int y){return pos[query(drnk[x],drnk[y])];}
void dfs1(int u,int fa){
    dfsn[u]=++cur;
    dfn[tot]=++tot;drnk[u]=tot;pos[tot]=u;
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dep[t]=dep[u]+e[i].w;
        dfs1(t,u);
        dfn[++tot]=drnk[u];
    }
}
vector<int> v[maxn];
int vv[maxn];int len;
inline void build_virtual_tree(int c){
    len=0;
    if(!v[c].size())    return;
    if(a[1]^c) v[c].eb(1);
    sort(v[c].begin(),v[c].end(),[&](int x,int y){return dfsn[x]<dfsn[y];});
    for(int i=0;i<(int)v[c].size()-1;i++) 
    vv[++len]=v[c][i],
    vv[++len]=LCA(v[c][i],v[c][i+1]);
    vv[++len]=v[c][v[c].size()-1];
    sort(vv+1,vv+len+1,[&](int x,int y){return dfsn[x]<dfsn[y];});
    len=unique(vv+1,vv+len+1)-vv-1;
    for(int i=1;i<len;i++){
        int l=LCA(vv[i],vv[i+1]);
        if(l==vv[i+1])  continue;
        nadde(l,vv[i+1]);
    }
}
inline void clear_virtual_tree(){
    for(int i=1;i<len;i++){
        int l=LCA(vv[i],vv[i+1]);
        if(l==vv[i+1])  continue;
        son[l].clear();son[vv[i+1]].clear();
    }
}
int main(){
    // freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    n=read();k=read();
    // if(n==-3) freopen("D:\\yhy\\GDFZ_yhy\\down\\tree\\tree3.in","r",stdin);
    // if(n==-4) freopen("D:\\yhy\\GDFZ_yhy\\down\\tree\\tree4.in","r",stdin);
    // if(n==-5) freopen("D:\\yhy\\GDFZ_yhy\\down\\tree\\tree5.in","r",stdin);
    // if(n<0)freopen("D:\\yhy\\GDFZ_yhy\\tree\\tree.out","w",stdout),n=read(),k=read();
    // for(int i=1;i<=n;i++){a[i]=read();v[a[i]].eb(i);}
    for(int i=1,t;i<=n;i++){
        a[i]=read();t=read();v[a[i]].eb(i);
        if(!t)continue;
        adde(i,t,1);
    }
    dfs1(1,0);init_LCA();
    for(int i=1;i<=k;i++){
        build_virtual_tree(i);
        dfs(1,0,i);
        clear_virtual_tree();
    }
    for(int i=1;i<=k;i++)   printll(ans[i]),putchar('\n');
    flush;
}
