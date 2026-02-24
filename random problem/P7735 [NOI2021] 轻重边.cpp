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
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){cnt=1;mems(head,0);}
}
using namespace Graph;namespace BetaCutShit{
    namespace Dfs{
        int dfsn[maxn],rnk[maxn],son[maxn],dep[maxn],siz[maxn],f[maxn],tp[maxn];
        int tot;
        void dfs1(int u,int fa){
            son[u]=0;
            f[u]=fa;dep[u]=dep[fa]+1;siz[u]=1;
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(t==fa)   continue;
                dfs1(t,u);
                siz[u]+=siz[t];
                if(!son[u]||siz[t]>siz[son[u]]) son[u]=t;
            }
        }
        void dfs2(int u){
            dfsn[u]=++tot;rnk[tot]=u;
            if(!son[u]) return;
            tp[son[u]]=tp[u];
            dfs2(son[u]);
            for(int i=head[u];i;i=e[i].nxt){
                int t=e[i].to;
                if(t==son[u]||t==f[u])   continue;
                tp[t]=t;
                dfs2(t);
            }
        }
    }
    using namespace Dfs;
    namespace SegmentTree{
        #define ls p<<1
        #define rs p<<1|1
        #define lson ls,l,mid
        #define rson rs,mid+1,r
        #define all 1,1,n
        #define pos p,l,r
        #define setmid int mid=(l+r)>>1
        #define setpos int p,int l,int r
        int tag[maxn<<2];
        struct tree{int L,R,s;}tr[maxn<<2];
        tree operator+(tree x,tree y){return x.L?y.L?(tree){x.L,y.R,x.s+y.s+(x.R==y.L)}:x:y;}
        inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
        inline void pt(setpos,int s){tr[p]={s,s,r-l};tag[p]=s;}
        inline void pd(setpos){if(tag[p]){setmid;pt(lson,tag[p]);pt(rson,tag[p]);tag[p]=0;}}
        void build(setpos){tr[p].s=tag[p]=0;if(l==r)return tr[p].L=tr[p].R=l,void();setmid;build(lson);build(rson);pu(p);}
        void upd(setpos,int pl,int pr,int k){if(l>=pl&&r<=pr)return pt(pos,k);setmid;pd(pos);if(pl<=mid)upd(lson,pl,pr,k);if(pr>mid)upd(rson,pl,pr,k);pu(p);}
        tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;tree res={0,0,0};pd(pos);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=res+query(rson,pl,pr);return res;}
    }
    using namespace SegmentTree;
    inline int LCA(int x,int y){
        while(tp[x]^tp[y]){
            if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
            x=f[tp[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
    inline void updpath(int x,int y,int k){
        while(tp[x]^tp[y]){
            if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
            upd(all,dfsn[tp[x]],dfsn[x],k);
            x=f[tp[x]];
        }
        if(dfsn[x]>dfsn[y]) swap(x,y);
        upd(all,dfsn[x],dfsn[y],k);
    }
    inline int askpath(int x,int y){
        int l=LCA(x,y),ans=0;
        tree res={0,0,0};
        while(tp[x]^tp[l]){
            res=query(all,dfsn[tp[x]],dfsn[x])+res;
            x=f[tp[x]];
        }
        res=query(all,dfsn[l],dfsn[x])+res;
        ans=res.s;res={0,0,0};
        while(tp[y]^tp[l]){
            res=query(all,dfsn[tp[y]],dfsn[y])+res;
            y=f[tp[y]];
        }
        res=query(all,dfsn[l],dfsn[y])+res;
        ans+=res.s;
        return ans;
    }
}
using namespace BetaCutShit;
void clear(){rebuild();tot=0;}
void matt(){
    clear();
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);tp[1]=1;dfs2(1);
    build(all);
    for(int i=1;i<=q;i++){
        int op,x,y;scanf("%d%d%d",&op,&x,&y);
        if(op==1)   updpath(x,y,i+n);
        else    printf("%d\n",askpath(x,y));
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}