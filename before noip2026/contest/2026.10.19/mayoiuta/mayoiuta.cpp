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
const int maxn=1e5+10,mod=1e9+7;
struct mint{
    int v;
    mint(int _v=0){v=_v;}
    inline void operator+=(mint y){v+=y.v;(v>=mod)&&(v-=mod);}
    inline void operator-=(mint y){v-=y.v;(v<0)&&(v+=mod);}
    inline void operator*=(mint y){v=1ull*v*y.v%mod;}
    inline int operator+(mint y){return v+y.v>=mod?v+y.v-mod:v+y.v;}
    inline int operator-(mint y){return v-y.v<0?v-y.v+mod:v-y.v;}
    inline int operator*(mint y){return 1ull*v*y.v%mod;}
};
int n,q,L,R;
mint a[maxn],b[maxn],c[maxn];
int dep[maxn],dfn[maxn],tot;
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
int fa[maxn],son[maxn],tp[maxn],siz[maxn],rnk[maxn];
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs1(int u,int ft){
        dep[u]=dep[fa[u]=ft]+1;
        siz[u]=1;
        go(u,i)if(t^ft){
            dfs1(t,u);
            siz[u]+=siz[t];
            if(siz[t]>siz[son[u]])  son[u]=t;
        }
    }
    void dfs2(int u,int ft){
        st[0][dfn[u]=++tot]=ft;rnk[tot]=u;
        if(son[u])  tp[son[u]]=tp[u],dfs2(son[u],u);
        go(u,i)if((t^ft)&&(t^son[u]))tp[t]=t,dfs2(t,u);
    }
    void build(){
        dfs1(1,0);tp[1]=1;dfs2(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    mint tr[maxn<<2],sum[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,mint s){tr[p]+=sum[p]*s;tag[p]+=s;}
    inline void pd(int p){if(tag[p].v)pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){if(l==r)return tr[p]=b[rnk[l]]*a[rnk[l]],sum[p]=b[rnk[l]],void();setmid;build(lson);build(rson);pu(p);sum[p]=sum[ls]+sum[rs];}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
}
using namespace SegmentTree;
void U(int x,int y,int w){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])swap(x,y);
        upd(all,dfn[tp[x]],dfn[x],w);
        x=fa[tp[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    upd(all,dfn[x],dfn[y],w);
}
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){x++;while(x<=n+1){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){x++;int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
#define __div(x,s) al=s,findWC(x,0),dvd(rt)
int al,rt;
bool bk[maxn];
int dfsn[maxn],rk[maxn],de[maxn];
void findWC(int u,int ft){
    siz[u]=1;int mx=0;
    go(u,i)if((t^ft)&&!bk[t]){
        findWC(t,u);
        siz[u]+=siz[t];
        gmx(mx,siz[t]);
    }
    gmx(mx,al-siz[u]);
    if(mx<=al/2)    rt=u;
}
void dfs(int u,int ft){siz[u]=1;rk[dfsn[u]=++tot]=u;de[u]=de[ft]+1;go(u,i)if((t^ft)&&!bk[t])dfs(t,u),siz[u]+=siz[t];}
void dfs2(int u,int ft){go(u,i)if((t^ft)&&!bk[t])dfs2(t,u),c[u]+=c[t];b[u]+=c[u];}
void dvd(int u){
    tot=0;dfs(u,0);
    bk[u]=true;
    vector<int> son;
    go(u,i)if(!bk[t])son.eb(t);
    T.add(de[u],1);
    for(int x:son){
        for(int i=dfsn[x];i<=dfsn[x]+siz[x]-1;i++){
            int t=rk[i];
            c[t]=T.query(max(0,L-de[t]),R-de[t]);
        }
        for(int i=dfsn[x];i<=dfsn[x]+siz[x]-1;i++)  T.add(de[rk[i]],1);
    }
    T.add(de[u],-1);for(int x:son)for(int i=dfsn[x];i<=dfsn[x]+siz[x]-1;i++)T.add(de[rk[i]],-1);
    reverse(son.begin(),son.end());
    c[u]=0;
    for(int x:son){
        for(int i=dfsn[x];i<=dfsn[x]+siz[x]-1;i++){
            int t=rk[i],w=T.query(max(0,L-de[t]),R-de[t]);
            c[t]+=w;c[u]-=w;
        }
        for(int i=dfsn[x];i<=dfsn[x]+siz[x]-1;i++)  T.add(de[rk[i]],1);
    }
    for(int x:son)for(int i=dfsn[x];i<=dfsn[x]+siz[x]-1;i++)T.add(de[rk[i]],-1);
    dfs2(u,0);
    go(u,i)if(!bk[t])__div(t,siz[t]);
}
bool mem2;
int main(){
    freopen("mayoiuta.in","r",stdin);freopen("mayoiuta.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();L=read()-1;R=read()-1;
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=2;i<=n;i++)   adde(read(),i);
    stLCA::build();
    de[0]=-1;__div(1,n);
    if(!L)for(int i=1;i<=n;i++)b[i]+=1;
    build(all);
    while(q--){
        int u=read(),v=read(),w=read();
        U(u,v,w);print(tr[1].v,'\n');
    }
    Flush();
}