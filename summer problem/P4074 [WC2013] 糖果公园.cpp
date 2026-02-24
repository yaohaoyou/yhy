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
using namespace std;
const int maxn=1e5+10,B=2048;
int n,m,q;
int a[maxn],b[maxn],c[maxn],buc[maxn];
vector<pii> col[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int tot,cur;
int in[maxn],out[maxn],dfn[maxn],rnk[maxn<<1];
bool f[maxn];
ll qans[maxn];
namespace ST_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using ST_LCA::LCA;
struct oper{int x,y,id;};
struct ques{int l,r,lc,id;};
vector<oper> S;vector<ques> Q;
void dfs(int u,int ft){
    in[u]=++tot;dfn[u]=++cur;rnk[tot]=u;
    ST_LCA::st[0][dfn[u]]=ft;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
    }
    out[u]=++tot;rnk[tot]=u;
}
ll ans=0;int now;
inline void add(int x){buc[x]++;ans+=1ll*a[x]*b[buc[x]];}
inline void del(int x){ans-=1ll*a[x]*b[buc[x]];buc[x]--;}
inline void chgx(int x){
    x=rnk[x];
    if(f[x])    del(col[x][c[x]].fi);
    while(c[x]>=0&&col[x][c[x]].se>now)  c[x]--;
    while(c[x]+1<col[x].size()&&col[x][c[x]+1].se<=now)   c[x]++;
    f[x]^=1;
    if(f[x])    add(col[x][c[x]].fi);
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);col[i].eb(x,0);c[i]=0;}
    dfs(1,0);ST_LCA::build();
    for(int i=1;i<=q;i++){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(!op){
            S.eb((oper){x,int(col[x].size()),i});
            col[x].eb(y,i);
        }
        else{
            if(in[x]>in[y])swap(x,y);
            int l=LCA(x,y);
            if(l==x) Q.eb((ques){in[x],in[y],0,i});
            else Q.eb((ques){out[x],in[y],in[l],i});
        }
    }
    sort(Q.begin(),Q.end(),[&](ques x,ques y){return x.l/B==y.l/B?x.r/B==y.r/B?x.id<y.id:x.r<y.r:x.l<y.l;});
    mems(qans,-1);
    int l=1,r=0,tim=0;
    for(int i=0;i<Q.size();i++){
        int ql=Q[i].l,qr=Q[i].r;
        now=Q[i].id;
        while(tim<S.size()&&S[tim].id<=now){
            int x=S[tim].x;
            if(f[x]){del(col[x][c[x]].fi);c[x]++;add(col[x][c[x]].fi);}
            tim++;
        }
        while(tim>0&&S[tim-1].id>now){
            tim--;
            int x=S[tim].x;
            if(f[x]){del(col[x][c[x]].fi);c[x]--;add(col[x][c[x]].fi);}
        }
        while(r<qr) chgx(++r);
        while(l>ql) chgx(--l);
        while(r>qr) chgx(r--);
        while(l<ql) chgx(l++);
        if(Q[i].lc){
            chgx(Q[i].lc);
            qans[now]=ans;
            chgx(Q[i].lc);
        }
        else qans[now]=ans;
    }
    for(int i=1;i<=q;i++)if(~qans[i])printf("%lld\n",qans[i]);
}