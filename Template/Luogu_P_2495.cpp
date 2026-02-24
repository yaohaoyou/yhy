//  P2495 [SDOI2011] 消耗战/虚树
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int maxn=2.5e5+10,maxm=5e5+10,inf=2e9;
int n,q,k;
int a[maxm];
namespace Graph{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxn<<1];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    basic_string<pii> son[maxn];
    inline void addedge(int u,int v,int w){son[u]+=pii(v,w);}
}
using namespace Graph;
bool usef[maxn];
int dfsn[maxn];
int fa[19][maxn],w[19][maxn],dep[maxn];
int tot;
inline void init_LCA(){for(int i=1;i<19;i++)for(int u=1;u<=n;u++){fa[i][u]=fa[i-1][fa[i-1][u]];w[i][u]=min(w[i-1][u],w[i-1][fa[i-1][u]]);}}
void dfs(int u,int f){
    dfsn[u]=++tot;
    dep[u]=dep[fa[0][u]=f]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==f)   continue;
        w[0][t]=e[i].w;
        dfs(t,u);
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y])   swap(x,y);
    for(int i=18;~i;i--) if(dep[fa[i][x]]>dep[y])x=fa[i][x];
    if(dep[x]!=dep[y])  x=fa[0][x];
    if(x==y)    return x;
    for(int i=18;~i;i--)
        if(fa[i][x]!=fa[i][y]){x=fa[i][x];y=fa[i][y];}
    return fa[0][x];
}
inline void getmn(int &x,int y){(x>y)&&(x=y);}
inline int wLCA(int x,int y){
    int res=inf;
    if(dep[x]<dep[y])   swap(x,y);
    for(int i=18;~i;i--)
        if(dep[fa[i][x]]>dep[y]){getmn(res,w[i][x]);x=fa[i][x];}
    return min(res,w[0][x]);
}
int len;
int v[maxm*2];
inline void build_virtual_tree(){
    len=0;
    sort(a+1,a+k+1,[&](int x,int y){return dfsn[x]<dfsn[y];});
    for(int i=1;i<k;i++){v[++len]=a[i];v[++len]=LCA(a[i],a[i+1]);}
    v[++len]=a[k];
    sort(v+1,v+len+1,[&](int x,int y){return dfsn[x]<dfsn[y];});
    len=unique(v+1,v+len+1)-v-1;
    for(int i=1;i<len;i++){
        int l=LCA(v[i],v[i+1]);
        if(l==v[i+1])   continue;
        addedge(l,v[i+1],wLCA(l,v[i+1]));
    }
}
ll dp[maxn];
void DP(int u){
    dp[u]=0;
    for(auto [t,w]:son[u]){
        DP(t);
        if(usef[t]) dp[u]+=w;
        else    dp[u]+=min(dp[t],1ll*w);
    }
    son[u].clear();
}
namespace IO{
    char buf[1000000],*p1=buf,*p2=buf,obuf[100000000],*p3=obuf,cc[20];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) *p3++=x
    #define Fwrite fwrite(obuf,p3-obuf,1,stdout);
    int x,f;char c;
    inline int read(){
        x=0;f=1;c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
        while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline void print(ll x){ 
        int l=0;
        if(x<0)x=-x,putchar('-');
        while(x)cc[l++]=x%10+'0',x/=10;
        while(l--)putchar(cc[l]);
    }
}
using namespace IO;
int main(){
    n=read();
    for(int i=1,u,v,w;i<n;i++){
        u=read();v=read();w=read();
        add(u,v,w);add(v,u,w);
    }
    dfs(1,0);
    init_LCA();
    q=read();
    while(q--){
        k=read();
        for(int i=1;i<=k;i++){
            a[i]=read();
            usef[a[i]]=true;
        }
        a[++k]=1;
        build_virtual_tree();
        DP(1);
        print(dp[1]);putchar('\n');
        for(int i=1;i<=k;i++)usef[a[i]]=false;
    }
    Fwrite;
}