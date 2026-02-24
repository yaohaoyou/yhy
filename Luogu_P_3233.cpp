#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#define pii pair<int,int>
#define piii pair<int,pii>
#define eb emplace_back
#define fi first
#define se second
using namespace std;
const int maxn=3e5+10,inf=1e9;
int n,m;
int a[maxn],b[maxn];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    vector<int> son[maxn];
}
using namespace Graph;
set<pii> st[maxn];
namespace PreSolve{
    int tot;
    int dep[maxn],pos[maxn],siz[maxn],rnk[maxn],mxdep[maxn];
    int nex[20][maxn];  // dfsn 是欧拉序（不是 dfsn 序）
    void dfs(int u,int fa){
        siz[u]=1;mxdep[u]=dep[u]=dep[nex[0][u]=fa]+1;
        pos[u]=++tot;rnk[tot]=u;
        for(int t:son[u]){
            if(t==fa)   continue;
            dfs(t,u);
            siz[u]+=siz[t];
            st[u].insert(pii(mxdep[t]-dep[u],t));
            mxdep[u]=max(mxdep[u],mxdep[t]);
        }
    }
    inline void initLCA(){for(int i=1;i<=19;i++)for(int j=1;j<=n;j++)nex[i][j]=nex[i-1][nex[i-1][j]];}
    inline int LCA(int u,int v){
        if(dep[u]<dep[v])   swap(u,v);
        for(int i=19;~i;i--){
            if(dep[nex[i][u]]>=dep[v])  u=nex[i][u];
        }
        if(u==v)    return u;
        for(int i=19;~i;i--){
            if(nex[i][u]^nex[i][v])    u=nex[i][u],v=nex[i][v];
        }
        return nex[0][u];
    }
    inline int dis(int u,int v){return  dep[u]+dep[v]-(dep[LCA(u,v)]<<1);}
    inline int getfa(int u,int d){
        for(int i=19;~i;i--)
            if(d&(1<<i))    u=nex[i][u];
        return u;
    }
}
using PreSolve::pos;
using PreSolve::dep;
using PreSolve::siz;
using PreSolve::rnk;
using PreSolve::mxdep;
using PreSolve::LCA;
using PreSolve::dis;
using PreSolve::getfa;
inline int dis(pii x){return dep[x.fi]+dep[x.se]-(dep[LCA(x.fi,x.se)]<<1);}
int ans;
namespace ST{
    pii st[20][maxn];
    int Log[maxn];
    inline pii pushup(pii ls,pii rs){
        pii tmp[6]={ls,rs,pii(ls.fi,rs.fi),pii(ls.fi,rs.se),pii(ls.se,rs.fi),pii(ls.se,rs.se)};
        piii res[6];
        for(int j=0;j<6;j++){
            res[j].se=tmp[j];
            res[j].fi=dis(tmp[j]);
        }
        sort(res,res+6);
        return res[0].se;
    }
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pii(rnk[i],rnk[i]);
        for(int i=1;i<20;i++){
            for(int j=1;j<=n;j++){
                pii ls=st[i-1][j],rs=st[i-1][j+(1<<i-1)];
                st[i][j]=pushup(ls,rs);
            }
        }
    }
    pii query(int l,int r){
        int k=Log[r-l+1];
        return pushup(st[k][l],st[k][r-(1<<k)+1]);
    }
}
namespace VirtualTree{
    int v[maxn],len;
    int dp[maxn],id[maxn];
    bool mark[maxn];
    inline void build(){
        len=0;
        if(!mark[1])    a[++m]=1;
        sort(a+1,a+m+1,[&](int x,int y){return pos[x]<pos[y];}); 
        for(int i=1;i<m;i++){v[++len]=a[i];v[++len]=LCA(a[i],a[i+1]);}
        v[++len]=a[m];
        sort(v+1,v+len+1,[&](int x,int y){return pos[x]<pos[y];});
        len=unique(v+1,v+len+1)-v-1;
        for(int i=1;i<len;i++){
            int l=LCA(v[i],v[i+1]);
            if(l==v[i+1])   continue;
            add(l,v[i+1]);add(v[i+1],l);
        }
    }
    void dfs1(int u,int fa){
        dp[u]=mark[u]?0:inf;id[u]=mark[u]?u:inf;
        go(u,i){
            int t=e[i].to;
            if(t==fa)   continue;
            dfs1(t,u);
            if(dp[t]+dis(u,t)<dp[u]||(dp[t]+dis(u,t)==dp[u]&&id[t]<id[u])){id[u]=id[t];dp[u]=dp[t]+dis(u,t);}
        }
    }
    void dfs2(int u,int fa){
        go(u,i){
            int t=e[i].to;
            if(t==fa)   continue;
            if(dp[u]+dis(u,t)<dp[t]||(dp[u]+dis(u,t)==dp[t]&&id[u]<id[t])){id[t]=id[u];dp[t]=dp[u]+dis(u,t);}
            dfs2(t,u);
        }
    }
    void dfs3(int u,int fa){
        set<pii> tmp=st[u];
        go(u,i){
            int t=e[i].to;
            if(t==fa)   continue;
            int x=getfa(t,dep[t]-dep[u]-1);
            tmp.erase(pii(mxdep[x]-dep[u],x));
            dfs3(t,u);
        }
        auto it=tmp.end();it--;
        ans=max(ans,dis(pii(id[u],it->second)));
    }
    void dfs4(int u,int fa){
        go(u,i){
            int t=e[i].to;
            if(t==fa)   continue;
            dfs4(t,u);
            int l=dep[u],r=dep[t],res=l,len=dis(u,t),d1=dis(u,id[u]),d2=dis(t,id[t]);
            while(l<=r){
                int mid=(l+r)>>1;
                int y=dep[t]-mid,x=len-y;
                x+=d1;y+=d2;
                if((x<y)||(x==y&&id[u]<id[t])){
                    res=mid;
                    l=mid+1;
                }
                else    r=mid-1;
            }
            res=getfa(t,dep[t]-res-1);
            int v=getfa(t,dep[t]-dep[u]-1);
            // (v,v+siz[v]-1),(res,res+siz[res]-1);
            pii tmp;
            if(v<=res-1){
                tmp=ST::query(v,res-1);
                ans=max(ans,dis(pii(tmp.fi,id[u])));
                ans=max(ans,dis(pii(tmp.se,id[u])));
            }
            if(res+siz[res]<=v+siz[v]-1){
                tmp=ST::query(res+siz[res],v+siz[v]-1);
                ans=max(ans,dis(pii(tmp.fi,id[u])));
                ans=max(ans,dis(pii(tmp.se,id[u])));
            }
            // ans[id[u]]+=(siz[getfa(t,dep[t]-dep[u]-1)]-siz[res]);
            
            // (res,res+siz[res]-1),(t,t+siz[t]-1)
            if(res<=t-1){
                tmp=ST::query(res,t-1);
                ans=max(ans,dis(tmp.fi,id[t]));
                ans=max(ans,dis(tmp.se,id[t]));
            }
            if(t+siz[t]<=res+siz[res]-1){
                tmp=ST::query(t+siz[t],res+siz[res]-1);
                ans=max(ans,dis(tmp.fi,id[t]));
                ans=max(ans,dis(tmp.se,id[t]));
            }
            // ans[id[t]]+=(siz[res]-siz[t]);
        }
    }
    void clear(int u,int fa){
        mark[u]=false;
        go(u,i){
            int t=e[i].to;
            if(t==fa)   continue;
            clear(t,u);
        }
        head[u]=0;
    }
    inline void solve(){
        scanf("%d",&m);
        for(int i=1;i<=m;i++){scanf("%d",&a[i]);mark[a[i]]=true;b[i]=a[i];}
        build();dfs1(1,0);dfs2(1,0);
        dfs3(1,0);dfs4(1,0);
        printf("%d\n",ans);
        cnt=1;clear(1,0);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        son[u].eb(v);
        son[v].eb(u);
    }
    PreSolve::dfs(1,0);PreSolve::initLCA();
    for(int i=1;i<=n;i++)   son[i].clear();
    int q;
    scanf("%d",&q);
    while(q--)  VirtualTree::solve();
}