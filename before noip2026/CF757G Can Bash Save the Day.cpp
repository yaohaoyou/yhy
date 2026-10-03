// 边分树节点数量为 4n！！！
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
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
bool mem1;
const int maxn=2e5*5+10,maxm=maxn<<1,U=(1<<30)-1;
int n,m,q,tot,root;
struct Graph{
    #define go(o,x,i) for(int i=T[o].head[x],t=T[o].e[i].to,w=T[o].e[i].w;i;i=T[o].e[i].nxt,t=T[o].e[i].to,w=T[o].e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}T[2];
int a[maxn];
ll dep[maxn],f[maxn*20];
int g[maxn*20];
int dfn[maxn];
int siz[maxn],lc[maxn],rc[maxn],fa[maxn];
int ls[maxn*20],rs[maxn*20],rt[maxn];
int sta[maxn],d[maxn];
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){st[0][dfn[u]=++tot]=ft;go(1,u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=2;i<=tot;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[tot];i++)for(int j=1;j+(1<<i)-1<=tot;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline ll dis(int x,int y,int l=0){return (dep[x]+dep[y])-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
void dfs1(int u,int ft){
    int son=0;
    go(0,u,i)if(t^ft)dep[t]=dep[u]+w,dfs1(t,u),son++;
    int p=u;
    go(0,u,i)if(t^ft){
        if(son<=2)  T[1].adde(p,t,0);
        else{
            T[1].adde(p,t,0);T[1].adde(p,++m,0);
            dep[m]=dep[u];
            p=m;
        }
        son--;
    }
}
pii mn;int all;
void dfs2(int u,int ft){
    siz[u]=1;
    go(1,u,i)if(!w&&(t^ft)){
        dfs2(t,u);
        siz[u]+=siz[t];
        mn=min(mn,pii(max(siz[t],all-siz[t]),i>>1));
    }
}
int dvd(int u){
    dfs2(u,0);
    all=siz[u];mn=pii(1e9,0);
    dfs2(u,0);
    if(mn.fi==1e9)return m-1+u;
    int p=mn.se;
    T[1].e[p<<1].w=T[1].e[p<<1|1].w=1;
    int x=T[1].e[p<<1].to,y=T[1].e[p<<1|1].to;
    lc[p]=dvd(x);rc[p]=dvd(y);
    fa[lc[p]]=fa[rc[p]]=p;
    return p;
}
int merge(int p,int q){
    if(!p||!q)  return p|q;
    f[p]+=f[q];g[p]+=g[q];
    ls[p]=merge(ls[p],ls[q]);
    rs[p]=merge(rs[p],rs[q]);
    return p;
}
ll query(int r,int x){
    int p=rt[r],q=root;ll res=0;
    for(int i=1;i<=d[x];i++){
        bool o=sta[x]&(1<<i-1);
        if(!o&&rs[p])   res+=1ll*g[rs[p]]*dis(x,T[1].e[q<<1].to)+f[rs[p]];
        else if(o&&ls[p])   res+=1ll*g[ls[p]]*dis(x,T[1].e[q<<1].to)+f[ls[p]];
        p=o?rs[p]:ls[p];q=o?rc[q]:lc[q];if(!p)break;
    }
    return res;
}
void build(int i){
    sta[a[i]]=d[a[i]]=0;
    int u=m-1+a[i];tot++;
    while(fa[u]){
        f[tot]=dis(a[i],T[1].e[fa[u]<<1].to);g[tot]=1;
        tot++;
        sta[a[i]]<<=1;d[a[i]]++;
        if(lc[fa[u]]==u)    ls[tot]=tot-1;
        else    rs[tot]=tot-1,sta[a[i]]++;
        u=fa[u];
    }
    rt[i]=merge(tot,rt[i-1]);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=m=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<n;i++){int u=read(),v=read(),w=read();T[0].adde(u,v,w);}
    dfs1(1,0);root=dvd(1);stLCA::build();
    tot=0;
    for(int i=1;i<=n;i++)   build(i);
    ll lst=0;
    while(q--){
        int op=read(),l=read()^lst;
        if(op==1){
            int r=read()^lst,x=read()^lst;
            printf("%lld\n",lst=query(r,x)-query(l-1,x));
            lst&=U;
        }
        else{
            swap(a[l],a[l+1]);
            build(l);
        }
    }
}