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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e5+10,inf=1e9;
int n;
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
struct SET{
    priority_queue<int,vector<int>,greater<int>> q1,q2;
    inline void clear(){while(!q1.empty())q1.pop();while(!q2.empty())q2.pop();}
    inline void ep(int x){q1.ep(x);}
    inline void erase(int x){q2.ep(x);}
    inline int top(){while(!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();return q1.top();}
    inline void pop(){q1.pop();}
    inline bool empty(){return q1.size()==q2.size();}
}st[maxn];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
    int Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=inf;if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)gmn(res,Q(rson,pl,pr));return res;}
    void clear(){mems(tr,0x3f);}
}T[2];
int tot;
int a[maxn];
int dfn[maxn],rk[maxn],dep[maxn],fa[maxn],tp[maxn],son[maxn],siz[maxn],R[maxn];
void dfs1(int u,int ft){dep[u]=dep[fa[u]=ft]+1;siz[u]=1;go(u,i)if(t^ft){dfs1(t,u);siz[u]+=siz[t];if(siz[t]>siz[son[u]])son[u]=t;}}
void dfs2(int u,int ft){
    rk[dfn[u]=++tot]=u;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u],u);
    go(u,i)if((t^ft)&&(t^son[u]))   tp[t]=t,dfs2(t,u);
    R[u]=tot;
}
void mdf(int x,bool o){
    int dx=dep[x];
    if(o)   st[x].ep(dx);
    else    st[x].erase(dx);
    if(!st[x].empty())  T[0].upd(dfn[x],st[x].top()-2*dep[x]);
    else    T[0].upd(dfn[x],inf);
    if(o)   T[1].upd(dfn[x],dx);
    else    T[1].upd(dfn[x],inf);
    while(x){
        int l=fa[tp[x]];
        if(l){
            if(o)   st[l].ep(dx);
            else    st[l].erase(dx);
            if(!st[l].empty())  T[0].upd(dfn[l],st[l].top()-2*dep[l]);
            else    T[0].upd(dfn[l],inf);
        }
        x=l;
    }
}
int qry(int x){
    int dx=dep[x],res=inf;
    gmn(res,T[1].Q(all,dfn[x],R[x])-dep[x]);
    while(x){
        int l=fa[tp[x]];
        gmn(res,T[0].Q(all,dfn[tp[x]],dfn[x])+dx);
        if(l){
            if(dfn[l]<=dfn[tp[x]]-1)    gmn(res,T[1].Q(all,dfn[l],dfn[tp[x]]-1)+dx-2*dep[l]);
            if(R[tp[x]]+1<=R[l])    gmn(res,T[1].Q(all,R[tp[x]]+1,R[l])+dx-2*dep[l]);
        }
        x=l;
    }
    return res>n?-1:res;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);tp[1]=1;dfs2(1,0);
    T[0].clear();T[1].clear();
    int q;scanf("%d",&q);
    while(q--){
        int op,x;scanf("%d%d",&op,&x);
        if(!op){a[x]^=1;mdf(x,a[x]);}
        else    printf("%d\n",qry(x));
    }
}