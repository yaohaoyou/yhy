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
const int maxn=1e6+10;
bool mem1;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],pos[maxn];
    inline int mrg(int x,int y){if(!x)return y;if(!y)return x;return x==y?x:-1;}
    inline void pu(int p){tr[p]=mrg(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=pos[x];tr[p]=s;while(p>>=1)pu(p);}
    void build(setpos){if(l==r)return pos[l]=p,void();setmid;build(lson);build(rson);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=mrg(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
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
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int tot;
int L[maxn],R[maxn],fa[maxn],c[maxn];
vector<pii> E[maxn];
vector<int> v[maxn];
int bel[maxn],cur[maxn];
bool vis[maxn];
vector<int> s;
bool in[maxn];
void dfs(int u,int ft){fa[u]=ft;L[u]=++tot;go(u,i)if(t^ft)dfs(t,u);R[u]=tot;}
void dfs2(int u,int ft){go(u,i)if(t^ft)c[t]+=c[u],dfs2(t,u);}
void dfs3(int u,int ft,int c=0){
    if(c)   v[c].eb(u);
    go(u,i)if(t^ft){
        if(w==c)    bel[t]=0;
        else    bel[t]=w,cur[w]++;
        dfs3(t,u,w);
    }
}
bool mem2;
void matt(int _cases){
    for(int i=1;i<=n;i++)   E[i].clear(),v[i].clear(),c[i]=bel[i]=cur[i]=vis[i]=0;
    rebuild();tot=0;
    n=read();m=read();
    for(int i=1;i<n;i++){int u=read(),v=read(),w=read();adde(u,v,w);E[w].eb(u,v);}
    dfs(1,0);build(all);
    U.init();
    for(int i=1;i<=m;i++){
        s.clear();
        for(auto [u,v]:E[i]){
            if(!in[u])s.eb(u),in[u]=true;
            if(!in[v])s.eb(v),in[v]=true;
            U.merge(u,v);
        }
        for(int u:s)    upd(L[u],U[u]);
        for(auto [u,v]:E[i]){
            if(fa[u]==v)    swap(u,v);
            if(query(all,L[v],R[v])==-1){c[1]++;c[v]--;}
            int w=0;
            if(L[v]^1)  w=query(all,1,L[v]-1);
            if(R[v]^n)  w=mrg(w,query(all,R[v]+1,n));
            if(w==-1)   c[v]++;
        }
        for(int u:s)    upd(L[u],0),U.fa[u]=u,in[u]=false;
    }
    dfs2(1,0);
    int rt=0;
    for(int i=1;i<=n;i++)if(!c[i]){rt=i;break;}
    if(rt){
        queue<int> q;
        dfs3(rt,0);
        q.ep(rt);vis[rt]=true;
        while(!q.empty()){
            int u=q.front();q.pop();
            go(u,i)if(bel[t]){
                cur[bel[t]]--;
                if(!cur[bel[t]]){
                    for(int j:v[bel[t]])if(!vis[j])vis[j]=true,q.ep(j);
                }
                bel[t]=0;
            }
        }
        if(count(vis+1,vis+n+1,1)!=n)   fill(c+1,c+n+1,1);
    }
    for(int i=1;i<=n;i++)putc('0'+bool(!c[i]));putc('\n');
}
int main(){freopen("b.in","r",stdin);freopen("b.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);Flush();}