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
using namespace std;
const int maxn=3e5+10,B=8,BB=64*B;
mt19937_64 matt(20250806);
int n,m;
int a[maxn];
ull c[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace SegmentTree{
    #define ls(p) lc[p]
    #define rs(p) rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    int cur;
    ull tr[maxn*20];int lc[maxn*20],rc[maxn*20],rt[maxn];
    inline void pu(int p){tr[p]=tr[ls(p)]^tr[rs(p)];}
    void upd(int &p,int q,int l,int r,int x,ull s){
        p=++cur;
        tr[p]=tr[q]^s;lc[p]=lc[q];rc[p]=rc[q];
        if(l==r)return;
        setmid;(x<=mid)?upd(ls(p),ls(q),l,mid,x,s):upd(rs(p),rs(q),mid+1,r,x,s);pu(p);
    }
    int binary(int a,int b,int c,int d,int l,int r,int pl,int pr){
        if(!(tr[a]^tr[b]^tr[c]^tr[d]))    return -1;
        setmid;
        if(l==r)    return l;
        int ret=-1;
        if(pl<=mid) ret=binary(ls(a),ls(b),ls(c),ls(d),l,mid,pl,pr);
        if(~ret)    return ret;
        if(pr>mid)  ret=binary(rs(a),rs(b),rs(c),rs(d),mid+1,r,pl,pr);
        return ret;
    }
}
using namespace SegmentTree;
struct ques{int u,v,l,r,lca;}Q[maxn];
int tot,fa[maxn],dfn[maxn],ans[maxn];
int st[20][maxn],Log[maxn];
vector<int> buc[maxn];
void dfs(int u,int ft){
    upd(rt[u],rt[ft],1,n,a[u],c[a[u]]);
    dfn[u]=++tot;st[0][tot]=fa[u]=ft;
    go(u,i)if(t^ft)dfs(t,u);
}
inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
void build(){
    for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
    for(int i=1;i<=Log[n];i++)
        for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
}
inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   buc[a[i]].eb(i);
    for(int i=1;i<n;i++)    adde(read(),read());
    for(int i=1;i<=n;i++)   c[i]=matt();
    dfs(1,0);build();
    while(m--){
        int u=read(),v=read(),l=read(),r=read();
        print(binary(rt[u],rt[v],rt[LCA(u,v)],rt[fa[LCA(u,v)]],1,n,l,r));putc('\n');
    }
    flush();
}