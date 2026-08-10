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
const int maxn=4e5+10,inf=1e9;
int n;
int tot=1,lst=1;
char s[maxn];
int en[maxn],ed[maxn],len[maxn],fa[maxn],nex[maxn][26];
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
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
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    void build(setpos){tr[p]=inf;if(l==r)return pos[l]=p,void();setmid;build(lson);build(rson);}
    void upd(int x,int s){int p=pos[x];tr[p]=s;while(p>>=1)pu(p);}
    int binary(setpos,int pl,int pr,int s){
        if(tr[p]>s) return 0;
        if(l==r)    return l;
        setmid;
        if(l>=pl&&r<=pr)    return tr[rs]<=s?binary(rson,pl,pr,s):binary(lson,pl,pr,s);
        if(pr<=mid)return binary(lson,pl,pr,s);if(pl>mid)return binary(rson,pl,pr,s);
        int x=binary(rson,pl,pr,s);if(x)return x;
        return binary(lson,pl,pr,s);
    }
    void clr(setpos){tr[p]=inf;if(l==r)return;setmid;if(tr[ls]^inf)clr(lson);if(tr[rs]^inf)clr(rson);}
}
using namespace SegmentTree;
struct ques{int l,r,id;ques(int _l=0,int _r=0,int _id=0){l=_l;r=_r;id=_id;}};
void ins(char c,int id){
    int o=c-'a',p=lst,x=++tot;lst=en[id]=x;
    ed[x]=id;len[x]=len[p]+1;
    while(!nex[p][o])   nex[p][o]=x,p=fa[p];
    if(!p)  return fa[x]=1,void();
    int q=nex[p][o];
    if(len[q]==len[p]+1)    return fa[x]=q,void();
    int nw=++tot;memc(nex[nw],nex[q]);len[nw]=len[p]+1;fa[nw]=fa[q];
    fa[q]=fa[x]=nw;
    while(nex[p][o]==q) nex[p][o]=nw,p=fa[p];
}
int cur;
int rk[maxn],L[maxn],R[maxn],siz[maxn],son[maxn],tp[maxn],dep[maxn];
vector<int> v[maxn];
vector<ques> Q[maxn],vq[maxn];
int ans[maxn];
void dfs1(int u){
    dep[u]=dep[fa[u]]+1;
    siz[u]=1;
    go(u,i){
        dfs1(t);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs2(int u){
    v[tp[u]].eb(u);
    rk[L[u]=++cur]=u;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u]);
    go(u,i)if(t^son[u]) tp[t]=t,dfs2(t);
    R[u]=cur;
}
set<int> st;
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)   ins(s[i],i);
    for(int i=2;i<=tot;i++) add(fa[i],i);
    // for(int i=1;i<=tot;i++) printf("%d,%d ",ed[i],len[i]);puts("");
    dfs1(1);tp[1]=1;dfs2(1);build(all);
    int q;scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        if(l==r)    continue;
        int u=en[r];
        while(u){
            Q[u].eb(l,r,i);
            vq[u].eb(l,r,i);
            u=fa[tp[u]];
        }
    }
    for(int u=1;u<=tot;u++){
        if(v[u].empty())    continue;
        st.clear();
        for(int i=v[u].size()-1;~i;i--){
            int x=v[u][i];
            if(son[x]){
                for(int j=L[x];j<L[son[x]];j++)if(ed[rk[j]])st.ep(ed[rk[j]]);
                for(int j=R[son[x]]+1;j<=R[x];j++)if(ed[rk[j]])st.ep(ed[rk[j]]);
            }
            else for(int j=L[x];j<=R[x];j++)if(ed[rk[j]])st.ep(ed[rk[j]]);
            for(auto [l,r,id]:vq[x]){
                auto it=st.upper_bound(min(l+len[x]-1,r-1));
                if(it!=st.begin()&&*(--it)>=l)  gmx(ans[id],*it-l+1);
            }
        }
        for(int i=0;i<v[u].size();i++){
            int x=v[u][i];
            if(son[x]){
                for(int j=L[x];j<L[son[x]];j++)if(ed[rk[j]]){
                    upd(ed[rk[j]],ed[rk[j]]-len[x]+1);
                }
                for(int j=R[son[x]]+1;j<=R[x];j++)if(ed[rk[j]]){
                    upd(ed[rk[j]],ed[rk[j]]-len[x]+1);
                }
            }
            else for(int j=L[x];j<=R[x];j++)if(ed[rk[j]])upd(ed[rk[j]],ed[rk[j]]-len[x]+1);
            
            for(auto [l,r,id]:Q[x]) gmx(ans[id],binary(all,l,r-1,l)-l+1);
        }
        clr(all);
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}