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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=4e5+10,maxp=maxn*20;
int n,m;
int a[maxn];
vector<int> v[maxn];
namespace Graph{
    const int maxm=maxp*10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v^1,u^1);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) root[x],1,(n<<2)
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int tot;
    int root[maxn],lc[maxn*20],rc[maxn*20];
    void upd(int &p,int q,int l,int r,int x,int id){
        p=++tot;tot++;if(q)adde(p,q);
        lc[p]=lc[q];rc[p]=rc[q];
        if(l==r)return adde(p,id);
        setmid;(x<=mid)?upd(ls,lc[q],l,mid,x,id):upd(rs,rc[q],mid+1,r,x,id);
        if(ls)adde(p,ls);
        if(rs)adde(p,rs);
    }
    void ADD(setpos,int pl,int pr,int x){if(!p)return;if(l>=pl&&r<=pr)return adde(x,p);setmid;if(pl<=mid)ADD(lson,pl,pr,x);if(pr>mid)ADD(rson,pl,pr,x);}
}
using namespace SegmentTree;
inline int id(int x,bool o){return (x<<1)|o;}
stack<int> stk;bool instk[maxp];
int cscc;
int dfsn[maxp],low[maxp],scc[maxp],cur;
void tarjan(int u){
    dfsn[u]=low[u]=++cur;
    stk.ep(u);instk[u]=true;
    go(u,i){
        if(!dfsn[t])    tarjan(t),gmn(low[u],low[t]);
        else if(instk[t])   gmn(low[u],dfsn[t]);
    }
    if(low[u]==dfsn[u]){
        int tp;cscc++;
        do{
            tp=stk.top();stk.pop();
            scc[tp]=cscc;instk[tp]=false;
        }while(tp^u);
    }
}
int ans[maxn];
piii vec[maxn];
inline bool contain(int x,int y,int a,int b){return (x<=a&&b<=y)||(a<=x&&y<=b);}
int main(){
    // freopen("C:\\Users\\Administrator\\AppData\\Roaming\\Code\\User\\workspaceStorage\\7d168467b347588a2280fbf45145cee2\\thomasqm.cpu\\testset177\\test2.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=(n<<2);i++){scanf("%d",&a[i]);v[a[i]].eb(i);}
    for(int i=1;i<=n;i++){
        int a=v[i][0],b=v[i][1],c=v[i][2],d=v[i][3];
        vec[++m]=piii(pii(a,b),id(i,0));
        vec[++m]=piii(pii(c,d),id(i,0));
        vec[++m]=piii(pii(a,c),id(i,1));
        vec[++m]=piii(pii(b,d),id(i,1));
    }
    tot=(n<<1)+1;
    sort(vec+1,vec+m+1,[&](piii x,piii y){return x.fi.se<y.fi.se;});
    for(int i=1;i<=m;i++){
        pii j=vec[i].fi;int id=vec[i].se;
        ADD(all(i-1),j.fi,j.se,id);
        upd(root[i],root[i-1],1,(n<<2),j.fi,id^1);
    }
    for(int i=1;i<=tot;i++)if(!dfsn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[id(i,0)]==scc[id(i,1)])return puts("No"),0;
    puts("Yes");
    for(int i=1;i<=n;i++){
        int a=v[i][0],b=v[i][1],c=v[i][2],d=v[i][3];
        if(scc[id(i,0)]<scc[id(i,1)])   ans[a]=ans[c]=1;
        else    ans[a]=ans[b]=1;
    }
    for(int i=1;i<=m;i++)printf("%d",ans[i]);
}