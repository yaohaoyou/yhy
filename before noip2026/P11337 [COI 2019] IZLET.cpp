#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3010;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n;
int a[maxn][maxn],c[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
namespace Graph{
    const int maxm=maxn*maxn*2;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int tot;
vector<int> son[maxn];
vector<pii> ans;
ull H[maxn];
bool vis[maxn];
void dfs(int u){
    vis[u]=1;
    go(u,i)if(!vis[t]){
        ans.eb(u,t);son[u].eb(t);son[t].eb(u);
        dfs(t);
    }
}
void dfs3(int u,int ft,int x,int y){
    if(a[u][x]==a[u][y])    return c[u]=c[y],void();
    for(int t:son[u])if(t^ft)dfs3(t,u,x,y);
}
void dfs2(int u,int ft){
    if(!c[u])   c[u]=++tot;
    for(int t:son[u])dfs3(t,u,t,u);
    for(int t:son[u])if(t^ft)dfs2(t,u);
}
void slv(int x){
    vector<int> v;v.eb(x);
    for(int i=1;i<=n;i++)if(U[i]==i){
        bool fl=true;
        for(int j:v)if(a[i][j]^2){fl=false;break;}
        if(fl)  v.eb(i);
    }
    for(int i:v)    adde(x,i),vis[i]=true;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    const int bs=1141241;
    read();n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)a[i][j]=read(),H[i]=H[i]*bs+a[i][j];
    U.init();
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)if(H[i]==H[j]&&(U[i]^U[j]))ans.eb(i,j),U.merge(i,j);
    // printf("%llu %llu\n",H[1],H[3]);
    int rt=0;
    for(int i=1;i<=n;i++)if(U[i]==i){
        if(!rt) rt=i;
        for(int j=i+1;j<=n;j++)if(U[j]==j&&a[i][j]==2)adde(i,j);
    }
    dfs(rt);
    dfs2(rt,0);
    for(int i=1;i<=n;i++)   printf("%d ",c[U[i]]);puts("");
    // printf("1 2 3 2\n");
    for(auto [i,j]:ans) printf("%d %d\n",i,j);
}