#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,maxm=maxn*5,maxq=maxn;
int n,m,q,now;
int dfsn[maxq],rnk[maxq];
bool ans[maxq];
vector<int> era[maxq];  
struct node{int op,u,v,l,r;}a[maxq];
inline int id(int x,int y){return (x-1)*5+y+1;}
namespace Graph{
    const int maxe=maxq;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxq];
    struct edge{int nxt,to;}e[maxe];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
bool f[maxm];
struct DSU{
    stack<pii> stk;
    bool flag;
    int fa[maxm],siz[maxm];
    void init(){iota(fa+1,fa+m+1,1);fill(siz+1,siz+m+1,1);flag=true;}
    int find(int x){return fa[x]==x?x:find(fa[x]);}
    inline void check(int u){
        if(!flag)   return;
        for(int i=0;i<5;i++){
            int x=find(id(u,i));
            if(f[x])  flag=false;
            f[x]=true;
        }
        for(int i=0;i<5;i++)    f[find(id(u,i))]=false;
    }
    inline void merge(int x,int y){
        x=find(x);y=find(y);if(x==y)return;
        if(siz[x]>siz[y])   swap(x,y);
        stk.ep(x,flag);siz[y]+=siz[x];fa[x]=y;
    }
    inline void bac(int k){while(stk.size()^k){int x=stk.top().fi,y=stk.top().se;stk.pop();siz[fa[x]]-=siz[x];fa[x]=x;flag=y;}}
}U;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,(q+1)
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<piii> tr[maxq<<2];
    void upd(setpos,int pl,int pr,piii x){if(l>=pl&&r<=pr)return tr[p].eb(x),void();setmid;if(pl<=mid)upd(lson,pl,pr,x);if(pr>mid)upd(rson,pl,pr,x);}
    inline void upd(int pl,int pr,piii x){if(pl<=pr)upd(all,pl,pr,x);}
    void dfs(setpos){
        int siz=U.stk.size();
        for(piii x:tr[p]){
            int u=x.se.fi,v=x.se.se;
            if(x.fi==1){
                for(int i=0;i<5;i++)    U.merge(id(u,i),id(v,(i+1)%5));
            }
            else{
                for(int i=0;i<5;i++)    U.merge(id(u,i),id(v,(i+2)%5));
            }
            U.check(u);U.check(v);
        }
        if(l==r)    ans[rnk[l]]=U.flag;
        else{setmid;dfs(lson);dfs(rson);}
        U.bac(siz);
    }
}
using namespace SegmentTree;
int tot;
int R[maxq];
void dfs(int u){
    dfsn[u]=++tot;rnk[tot]=u;
    go(u,i)dfs(t);
    R[u]=tot;
    if(a[u].op^3){
        piii x=piii(a[u].op,pii(a[u].u,a[u].v));
        if(era[u].empty())  upd(dfsn[u],R[u],x);
        else{
            sort(era[u].begin(),era[u].end(),[&](int x,int y){return dfsn[x]<dfsn[y];});
            upd(dfsn[u],dfsn[era[u].front()]-1,x),upd(R[era[u].back()]+1,R[u],x);
            for(int i=0;i+1<era[u].size();i++)upd(R[era[u][i]]+1,dfsn[era[u][i+1]]-1,x);
        }
    }
}
int main(){
    scanf("%d%d",&n,&q);m=5*n;
    a[0].op=3;
    for(int i=1;i<=q;i++){
        int k,op,x,y;scanf("%d%d%d",&k,&op,&x);
        if(op^3)    scanf("%d",&y);
        add(k,i);
        a[i]={op,x,y,i,q};
        if(op==3)   era[x].eb(i);
    }
    U.init();dfs(0);dfs(all);
    for(int i=1;i<=q;i++)   puts(ans[i]?"excited":"naive");
}