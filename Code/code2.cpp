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
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n,m,q;
int a[maxn];
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
int tot,len;
int siz[maxn],son[maxn],dfsn[maxn],tp[maxn],fa[maxn],dep[maxn];
int L[maxn],R[maxn],ans[maxn];
vector<pii> Q[maxn];
pii p[maxn*20];
set<piii> st;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=len){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=len;i++)tr[i]=0;}
}T;
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;
    siz[u]=1;
    go(u,i)if(t^ft){
        dfs(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs2(int u,int ft){
    dfsn[u]=++tot;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u],u);
    go(u,i)if((t^ft)&&(t^son[u])){tp[t]=t;dfs2(t,u);}
}
inline vector<pii> path(int x,int y){
    vector<pii> res;
    if(x==y)    return res;
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        res.eb(dfsn[tp[x]],dfsn[x]);
        x=fa[tp[x]];
    }
    if(dfsn[x]>dfsn[y]) swap(x,y);
    res.eb(dfsn[x],dfsn[y]);
    return res;
}
set<piii>::iterator split(int x){
    auto it=--st.lower_bound(piii(pii(x,1e9),1e9));
    int l=it->fi.fi,r=it->fi.se,k=it->se;
    if(l==x)    return it;
    st.erase(it);
    st.ep(pii(l,x-1),k);return st.ep(pii(x,r),k).fi;
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);tp[1]=1;dfs2(1,0);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]);
    for(int i=1;i<m;i++){
        vector<pii> tmp=path(a[i],a[i+1]);
        L[i]=len+1;
        for(pii j:tmp)  p[++len]=j;
        R[i]=len;
    }
    for(int i=1;i<=len;i++) printf("[%d,%d]\n",p[i].fi,p[i].se);
    for(int i=1;i<=q;i++){
        int l,r;scanf("%d%d",&l,&r);
        if(L[l]<=R[r-1])    Q[R[r-1]].eb(L[l],i);
        else    ans[i]=1;
    }
    st.ep(pii(1,len),0);
    for(int i=1;i<=len;i++){
        auto itr=split(p[i].se+1),itl=split(p[i].fi);
        for(auto it=itl;it!=itr;it++)
            if(it->se)  T.add(it->se,-(it->fi.se-it->fi.fi+1));
        st.erase(itl,itr);
        st.ep(p[i],i);
        T.add(i,p[i].se-p[i].fi+1);
        for(auto [l,id]:Q[i])   ans[id]=T.query(l,i);
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}