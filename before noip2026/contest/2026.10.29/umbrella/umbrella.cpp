#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){if(x<y)x=y;}
using namespace std;
bool mem1;
const int maxn=2e6+10;
int n,m,q,rt;
pii a[maxn];
vector<int> son[maxn];
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
namespace Graph{
    const int maxp=maxn*5,maxm=maxp+maxn*12;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxp],deg[maxp];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int fa[maxn],id[maxn],rk[maxn],tot,cur;
int dep[maxn];
void dfs1(int u,int ft){
    dep[u]=dep[ft]+1;
    if(u<=m) id[u]=++cur,a[u]=pii(id[u],id[u]),rk[id[u]]=u;
    else    a[u]=pii(1e9,-1e9);
    for(int t:son[u])dfs1(t,u),gmn(a[u].fi,a[t].fi),gmx(a[u].se,a[t].se);
}
int c[maxn];
namespace SegmentTree{
    #define ls (p<<1)
    #define rs (p<<1|1)
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii tag[maxn<<2];
    void upd(setpos,int pl,int pr,pii x){if(l>=pl&&r<=pr)return gmx(tag[p],x);setmid;if(pl<=mid)upd(lson,pl,pr,x);if(pr>mid)upd(rson,pl,pr,x);}
    void build(setpos){if(l==r){if(tag[p].fi)add(tag[p].se,rk[l]);return;}setmid;gmx(tag[ls],tag[p]);gmx(tag[rs],tag[p]);build(lson);build(rson);}
}
using namespace SegmentTree;
bool in[maxn];
void dfs(int u,int ft){
    in[u]=true;
    if(u<=m){
        int x=u+m;
        if(in[x]){
            int l=a[x].fi,r=a[x].se;
            for(int t:son[x])if(in[t]){
                if(l<a[t].fi)   upd(all,l,a[t].fi-1,pii(dep[x],u)),c[l]++,c[a[t].fi]--;
                if(a[t].se^r)   upd(all,a[t].se+1,r,pii(dep[x],u)),c[a[t].se+1]++,c[r+1]--;
                break;
            }
        }
    }
    for(int t:son[u])dfs(t,u);
    in[u]=false;
}
bool ans[maxn];
bool vis[maxn];
piii Q[maxn];
pii sq[maxn];
void dfs2(int u){
    assert(!vis[u]);vis[u]=true;
    if(u<=m){
        in[u]=true;
        for(int i=sq[u].fi;i<=sq[u].se;i++)ans[Q[i].se]|=in[Q[i].fi.se];
    }
    go(u,i)dfs2(t);
    if(u<=m)in[u]=false;
}
bool mem2;
int main(){
    freopen("umbrella.in","r",stdin);freopen("umbrella.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();m=n;n<<=1;
    for(int i=1;i<=n;i++){int x=read();if(x)son[x].eb(i),fa[i]=x;else rt=i;}
    dfs1(rt,0);assert(cur==m);
    dfs(rt,0);build(all);
    // for(int i=1;i<=m;i++)printf("id[%d] = %d\n",i,id[i]);
    // exit(0);
    int k=0;
    for(int i=1;i<=q;i++){int x=read(),y=read();if(x==y)ans[i]=true;else Q[++k]=piii(pii(x,y),i),Q[++k]=piii(pii(y,x),i);}
    sort(Q+1,Q+k+1);
    for(int i=1;i<=k;i++){
        if(!sq[Q[i].fi.fi].fi)  sq[Q[i].fi.fi].fi=i;
        sq[Q[i].fi.fi].se=i;
    }
    for(int i=1;i<=m;i++)   c[i]+=c[i-1];
    for(int i=1;i<=m;i++)if(!deg[i])dfs2(i);
    // for(int i=1;i<=m;i++)if(!vis[i])dfs2(i);
    for(int i=1;i<=q;i++)pus(ans[i]?"Yes\n":"No\n");Flush();
}