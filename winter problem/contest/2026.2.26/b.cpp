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
const int maxn=6e5+10;
int n,q;
ll ans[maxn];
int all,rt;bool vis[maxn];
int siz[maxn],dep[maxn];
int fa[20][maxn];
struct ques{
    int r,id,k;
    ques(int _r,int _id,int _k){r=_r;id=_id;k=_k;}
};
vector<ques> Q[maxn];
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
namespace tree_LCA{
    const int lgV=20;
    int tot;
    int dfn[maxn],st[lgV+1][maxn],Log[maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){
        st[0][dfn[u]=++tot]=ft;
        go(u,i)if(t^ft)dfs(t,u);
    }
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=lgV;i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
}
using tree_LCA::LCA;
using tree_LCA::dis;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){x++;while(x<=n+1){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){x++;int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
void dfs1(int u,int ft){dep[u]=dep[fa[0][u]=ft]+1;go(u,i)if(t^ft)dfs1(t,u);}
#define __div(u,s) all=s,findWC(u,0),divide(rt)
void findWC(int u,int ft){
    siz[u]=1;int mx=0;
    go(u,i)if((t^ft)&&!vis[t]){
        findWC(t,u);
        mx=max(mx,siz[t]);
        siz[u]+=siz[t];
    }
    mx=max(mx,all-siz[u]);
    if(mx+mx<=all)  rt=u;
}
void dfs2(int u,int ft){dep[u]=dep[ft]+1;go(u,i)if((t^ft)&&!vis[t])dfs2(t,u);}
vector<int> v[maxn];
void dfs3(int u,int ft,int fr){v[fr].eb(u);go(u,i)if((t^ft)&&!vis[t])dfs3(t,u,fr);}
void calc(int u){
    dfs2(u,0);
    vector<int> son;son.clear();
    go(u,i)if(!vis[t])son.eb(t);
    for(int t:son)  v[t].clear(),dfs3(t,u,t);
    // printf("%d : ",u);for(int t:son)for(int i:v[t])printf("%d ",i);puts("");
    if(u<=(n+1)/2)T.add(0,1);
    for(int t:son){
        for(int i:v[t])
            for(auto [r,id,k]:Q[i])if(r>=dep[i]){
                // printf("#%d %d %d %d : %d\n",u,i,r,id,T.que(r-dep[i]));
                ans[id]+=1ll*k*T.que(r-dep[i]);
            }
        for(int i:v[t])if(i<=(n+1)/2)T.add(dep[i],1);
    }
    if(u<=(n+1)/2)T.add(0,-1);for(int t:son)for(int i:v[t])if(i<=(n+1)/2)T.add(dep[i],-1);
    reverse(son.begin(),son.end());
    for(int t:son){
        for(int i:v[t])
            for(auto [r,id,k]:Q[i])if(r>=dep[i]){
                // printf("#%d %d %d %d : %d\n",u,i,r,id,T.que(r-dep[i]));
                ans[id]+=1ll*k*T.que(r-dep[i]);
            }
        for(int i:v[t])if(i<=(n+1)/2)T.add(dep[i],1);
    }
    if(u<=(n+1)/2)    T.add(0,1);
    for(auto [r,id,k]:Q[u])if(r>=dep[u]){
        // printf("%d %d %d : %d\n",u,r,id,T.que(r-dep[u]));
        ans[id]+=1ll*k*T.que(r-dep[u]);
    }
    for(int t:son)for(int i:v[t])if(i<=(n+1)/2)T.add(dep[i],-1);
    if(u<=(n+1)/2)    T.add(0,-1);
}
void divide(int u){
    vis[u]=true;
    calc(u);findWC(u,0);
    go(u,i)if(!vis[t])__div(t,siz[t]);
}
inline int jump(int x,int d){if(!d)return x;for(int i=__lg(d);~i;i--)if(d&(1<<i))x=fa[i][x];return x;}
inline pii mrg(pii x,pii y){
    if(!x.fi||!y.fi)    return pii(0,0);
    if(dep[x.fi]<dep[y.fi]) swap(x,y);
    int u=x.fi,v=y.fi,r1=x.se,r2=y.se;
    int d=dis(u,v);
    if(r1+r2<d) return pii(0,0);
    if(r1-d>=r2)    return y;
    if(r2-d>=r1)    return x;
    // u up  (r1-r2+d)/2
    assert(!((r1-r2+d)&1));
    int l=LCA(u,v),up=(r1-r2+d)/2;
    if(dep[u]-dep[l]>=up)   return pii(jump(u,up),r1-up);
    up=d-up;return pii(jump(v,up),r2-up);
}
pii pre[maxn],suf[maxn];
int main(){
    freopen("b.in","r",stdin);freopen("b.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,i+n);adde(i+n,v);}
    n=(n<<1)-1;
    dep[0]=-1;dfs1(1,0);tree_LCA::build();
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    scanf("%d",&q);
    for(int _=1;_<=q;_++){
        int k;scanf("%d",&k);
        for(int i=1;i<=k;i++){int u,r;scanf("%d%d",&u,&r);pre[i]=pii(u,r<<1);}
        suf[k]=pre[k];
        for(int i=k-1;i;i--)  suf[i]=mrg(suf[i+1],pre[i]);
        for(int i=2;i<=k;i++)   pre[i]=mrg(pre[i-1],pre[i]);
        // for(int i=1;i<=k;i++)   printf("%d,%d ",suf[i].fi,suf[i].se);puts("");
        // for(int i=1;i<=k;i++)   printf("%d,%d ",pre[i].fi,pre[i].se);puts("");
        for(int i=1;i<=k;i++){
            pii p;
            if(i==1)    p=suf[i+1];
            else if(i==k)   p=pre[i-1];
            else    p=mrg(pre[i-1],suf[i+1]);
            // printf("%d : %d %d\n",i,p.fi,p.se);
            if(p.fi)    Q[p.fi].eb(p.se,_,1);
        }
        if(pre[k].fi)   Q[pre[k].fi].eb(pre[k].se,_,-k+1);
        // if(pre[k].fi)   printf("! %d %d\n",pre[k].fi,pre[k].se);
    }
    __div(1,n);
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}