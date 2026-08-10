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
const int maxn=1e5+10;
int n,q;
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
int a[maxn];
int fa[maxn],dep[maxn],tp[maxn],siz[maxn],son[maxn],ff[20][maxn];
int dfn[maxn],rnk[maxn],tot;
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;siz[u]=1;
    go(u,i)if(t^ft){
        dfs(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs2(int u,int ft){
    rnk[dfn[u]=++tot]=u;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u],u);
    go(u,i)if((t^ft)&&(t^son[u])){tp[t]=t;dfs2(t,u);}
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{
        int c0,c1,res,ic0,ic1,ires,rc0,rc1,rres,ric0,ric1,rires;
        tree operator+(tree y){
            tree ret={
                c0+y.c0,c1+y.c1,res+y.res,
                ic0+y.ic0,ic1+y.ic1,ires+y.ires,
                rc0+y.rc0,rc1+y.rc1,rres+y.rres,
                ric0+y.ric0,ric1+y.ric1,rires+y.rires};
            int d=min(c0,y.c1);
            ret.c0-=d;ret.c1-=d;ret.res+=d;
            d=min(ic0,y.ic1);
            ret.ic0-=d;ret.ic1-=d;ret.ires+=d;
            d=min(rc1,y.rc0);
            ret.rc0-=d;ret.rc1-=d;ret.rres+=d;
            d=min(ric1,y.ric0);
            ret.ric0-=d;ret.ric1-=d;ret.rires+=d;
            return ret;
        }
    }tr[maxn<<2];
    bool tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p){
        swap(tr[p].c0,tr[p].ic0);swap(tr[p].c1,tr[p].ic1);swap(tr[p].res,tr[p].ires);
        swap(tr[p].rc0,tr[p].ric0);swap(tr[p].rc1,tr[p].ric1);swap(tr[p].rres,tr[p].rires);
        tag[p]^=1;
    }
    inline void pd(int p){if(tag[p])pt(ls),pt(rs),tag[p]=0;}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;if(pl>mid)return query(rson,pl,pr);if(pr<=mid)return query(lson,pl,pr);return query(lson,pl,pr)+query(rson,pl,pr);}
    void build(setpos){
        if(l==r){
            if(a[rnk[l]])   tr[p]={0,1,0,1,0,0,0,1,0,1,0,0};
            else    tr[p]={1,0,0,0,1,0,1,0,0,0,1,0};
            return;
        }
        setmid;build(lson);build(rson);
        pu(p);
    }
}
using namespace SegmentTree;
inline int LCA(int x,int y){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])swap(x,y);
        x=fa[tp[x]];
    }
    return dep[x]<dep[y]?x:y;
}
void upd(int x,int y){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        upd(all,dfn[tp[x]],dfn[x]);
        x=fa[tp[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    upd(all,dfn[x],dfn[y]);
}
tree query(int x,int y){
    vector<tree> res;
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        res.eb(query(all,dfn[tp[x]],dfn[x]));
        x=fa[tp[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    res.eb(query(all,dfn[x],dfn[y]));
    reverse(res.begin(),res.end());
    tree ret={0,0,0,0,0,0,0,0,0,0,0,0};
    for(tree i:res) ret=ret+i;
    return ret;
}
inline int stp(int x,int d){for(int i=19;~i;i--)if(d&(1<<i))x=ff[i][x];return x;}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    tp[1]=1;dfs2(1,0);
    memc(ff[0],fa);
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)ff[i][j]=ff[i-1][ff[i-1][j]];
    // for(int i=1;i<=n;i++)   printf("%d %d\n",dfn[i],tp[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    while(q--){
        int op,x,y;scanf("%d%d%d",&op,&x,&y);
        if(op==1)   upd(x,y);
        else{
            int l=LCA(x,y);
            tree xx=query(x,l);
            // printf("! %d %d %d\n",x,l,y);
            // printf("%d %d\n",xx.res,xx.rres);
            tree yy=l==y?(tree){0,0,0,0,0,0,0,0,0,0,0,0}:query(stp(y,dep[y]-dep[l]-1),y);
            swap(xx.c0,xx.rc0);swap(xx.c1,xx.rc1);swap(xx.res,xx.rres);
            printf("%d\n",(xx+yy).res<<1);
        }
        // int l=LCA(x,y);
        // if(op==1){
        //     while(x)    a[x]^=1,x=fa[x];
        //     while(y)    a[y]^=1,y=fa[y];
        //     a[l]^=1;
        // }
        // else{
        //     vector<int> v,v2;
        //     while(x^l)  v.eb(a[x]),x=fa[x];
        //     v.eb(a[l]);
        //     while(y^l)  v2.eb(a[y]),y=fa[y];
        //     reverse(v2.begin(),v2.end());
        //     for(int i:v2)   v.eb(i);
        //     int ans=0;
        //     // for(int i:v)    printf("%d ",i);puts("");
        //     for(int i=0,j=0;i<v.size();i++){
        //         if(!v[i]){
        //             j=max(i,j);
        //             while(j<v.size()&&!v[j])    j++;
        //             if(j==v.size()) break;
        //             ans+=2;j++;
        //         }
        //     }
        //     printf("%d\n",ans);
        // }
    }
}