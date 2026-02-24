#include<cstdio>
#include<algorithm>
#define ll long long
#define pii pair<int,int>
#define if(sth) if(__builtin_expect(sth,1))
#define while(sth) while(__builtin_expect(sth,1))
#define rep(i,x,y) i=x-1,Y=y+1;while(++i^Y)
#define repp(i,x,y) i=y+1,X=x-1;while(--i^X)
#define fi first
#define se second
using namespace std;
const int maxn=1e5+10;
int n,q;
ll W;
namespace Graph{
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    int tt[maxm];
    struct edge{int nxt,to;ll w;}e[maxm];
    inline void add(int u,int v,ll w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}
using namespace Graph;
namespace IO{
    char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf,cc[20];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    inline ll read(){
        ll x=0;char c=getchar();
        while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
        return x;
    }
    inline void print(ll x){ 
        int len=0;
        while(x)cc[len++]=x%10+'0',x/=10;
        while(len--)putchar(cc[len]);
    }
}
using namespace IO;
ll lstans;
int tot;
ll dep[maxn];
int dfsn[maxn],siz[maxn],rnk[maxn];
int lg[maxn<<1],st[maxn<<1][21];
int dfn[maxn<<1],pos[maxn<<1],drnk[maxn];
int cur;
void dfs(int u,int fa)
{
    dfsn[u]=++tot;siz[u]=1;rnk[tot]=u;

    ++cur;
    dfn[cur]=cur;
    // 不能写成 dfsn[++cur]=cur，可以写成 dfsn[cur]=++cur;
    drnk[u]=cur;pos[cur]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa) continue;
        tt[i]=tt[i^1]=t;
        dep[t]=dep[u]+e[i].w;
        dfs(t,u);
        dfn[++cur]=drnk[u];
        siz[u]+=siz[t];
    }
}
void init_LCA() {
    for(int i=2;i<=cur;i++) lg[i]=lg[i/2]+1;
    for(int i=1;i<=cur;i++) st[i][0]=dfn[i];
    for(int j=1;j<=20;j++)
        for(int i=1;i+(1<<j)-1<=cur;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<j>>1)][j-1]);
}
inline int query(int a,int b){if(a>b)swap(a,b);return min(st[a][lg[b-a+1]],st[b-(1<<lg[b-a+1])+1][lg[b-a+1]]);}
inline int LCA(int x,int y){return pos[query(drnk[x],drnk[y])];}
namespace BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline void upd(int l,int r,ll s){add(l,s);add(r+1,-s);}
    inline ll que(int x){ll res=dep[rnk[x]];while(x){res+=tr[x];x-=lowbit(x);}return res;}
}
inline ll dis(pii t){return dep[t.fi]+dep[t.se]-(dep[dfsn[LCA(t.fi,t.se)]]<<1);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii tr[maxn<<2];ll trr[maxn<<2];
    inline void pushup(int p){
        pii res[6]={tr[ls],tr[rs],pii(tr[ls].fi,tr[rs].fi),pii(tr[ls].fi,tr[rs].se),pii(tr[ls].se,tr[rs].fi),pii(tr[ls].se,tr[rs].se)};
        ll dx0=BIT::que(dfsn[tr[ls].fi]),dx1=BIT::que(dfsn[tr[ls].se]),dy0=BIT::que(dfsn[tr[rs].fi]),dy1=BIT::que(dfsn[tr[rs].se]);

        ll mx=dis(res[5]);
        int id=5;
        if(trr[ls]>mx){mx=trr[ls];id=0;}
        if(trr[rs]>mx){mx=trr[rs];id=1;}
        ll tmp=dis(res[2]);
        if(tmp>mx){mx=tmp;id=2;}
        tmp=dis(res[3]);
        if(tmp>mx){mx=tmp;id=3;}
        tmp=dis(res[4]);
        if(tmp>mx){mx=tmp;id=4;}
        tr[p]=res[id];
        trr[p]=mx;
    }
    void build(setpos){
        // printf("%d %d %d\n",p,l,r);
        if(l==r)    return tr[p]={rnk[l],rnk[l]},void();
        setmid;
        build(lson);build(rson);pushup(p);
    }
    void update(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return;
        setmid;
        if(pl<=mid)update(lson,pl,pr);if(pr>mid) update(rson,pl,pr);
        pushup(p);
    }
}
using namespace SegmentTree;
signed main(){
    n=read();q=read();W=read();
    for(int i=1,u,v;i<n;i++){
        u=read();v=read();
        ll w=read();
        add(u,v,w);add(v,u,w);
    }
    pos[0]=1;
    dfs(1,0);
    init_LCA();
    build(all);
    while(q--){
        ll d=read(),E=read();
        d=(d+lstans)%(n-1)+1;E=(E+lstans)%W;
        d<<=1;
        int u=tt[d];
        BIT::upd(dfsn[u],dfsn[u]+siz[u]-1,E-e[d].w);
        e[d].w=E;
        update(all,dfsn[u],dfsn[u]+siz[u]-1);
        print(lstans=dis(tr[1]));
        putchar('\n');
    }
    fwrite(obuf,p3-obuf,1,stdout);
}