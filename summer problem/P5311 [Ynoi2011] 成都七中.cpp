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
const int maxn=1e6+10;
int n,q;
int a[maxn];
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
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
vector<piii> Q[maxn];
bool vis[maxn],vvis[maxn];
int lst[maxn],ans[maxn];
int siz[maxn];int all,rt;
vector<piii> vec,vq;
void findWC(int u,int ft);
void divide(int u);
void __div(int u,int al){all=al;findWC(u,0);assert(rt);divide(rt);}
void findWC(int u,int ft){
    siz[u]=1;
    int mx=0;
    go(u,i){
        if(t==ft||vis[t])   continue;
        findWC(t,u);
        mx=max(mx,siz[t]);
        siz[u]+=siz[t];
    }
    mx=max(mx,all-siz[u]);
    if(mx*2<=all)    rt=u;
}
void dfs(int u,int ft,int mn,int mx){
    mn=min(mn,u);mx=max(mx,u);
    vec.eb(pii(mn,mx),u);
    for(piii i:Q[u]){
        int l=i.fi.fi,r=i.fi.se,id=i.se;
        if((!~ans[id])&&l<=mn&&r>=mx)vq.eb(i),vvis[i.se]=true;
    }
    go(u,i){
        if(t==ft||vis[t])   continue;
        dfs(t,u,mn,mx);
    }
}
void calc(int u){
    vq.clear();vec.clear();dfs(u,0,u,u);
    auto cmp=[&](piii x,piii y){return x.fi.se<y.fi.se;};
    sort(vec.begin(),vec.end(),cmp);
    sort(vq.begin(),vq.end(),cmp);
    vector<int> col;col.clear();
    for(int i=0,j=0;i<vq.size();i++){
        int l=vq[i].fi.fi,r=vq[i].fi.se,id=vq[i].se;
        while(j<vec.size()&&vec[j].fi.se<=r){
            int c=a[vec[j].se];
            if(!lst[c]) lst[c]=vec[j].fi.fi,T.add(lst[c],1),col.eb(c);
            else if(lst[c]<vec[j].fi.fi)    T.add(lst[c],-1),lst[c]=vec[j].fi.fi,T.add(lst[c],1);
            j++;
        }
        ans[id]=T.query(l,r);
    }
    for(int i:col)  T.add(lst[i],-1),lst[i]=0;
}
void divide(int u){
    vis[u]=true;
    calc(u);
    findWC(u,0);
    go(u,i){
        if(vis[t])  continue;
        __div(t,siz[t]);
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=q;i++){int l,r,x;scanf("%d%d%d",&l,&r,&x);Q[x].eb(pii(l,r),i);}
    mems(ans,-1);
    __div(1,n);
    for(int i=1;i<=n;i++)   assert(vis[i]);
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}