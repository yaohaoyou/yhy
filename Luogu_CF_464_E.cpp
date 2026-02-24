#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#define eb emplace_back
using namespace std;
const int maxn=1e5+50,mod=1e9+7,R=1e5+50;
int n,m,S,T;
int a[maxn];
int qp[R+10];
namespace Graph{
    const int maxm=maxn;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm<<1];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}
using namespace Graph;
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
namespace SegmentTree{
    #define ls(p) lc[p]
    #define rs(p) rc[p]
    #define lson ls(p),ls(q),l,mid
    #define rson rs(p),rs(q),mid+1,r
    #define plson ls(p),l,mid
    #define prson rs(p),mid+1,r
    #define setmid int mid=(l+r)>>1
    int tot;
    int rt[maxn];
    int lc[R*80],rc[R*80];
    int hs[R*80];bool all1[R*80];
    inline void copy(int &p,int q){p=++tot;lc[p]=lc[q];rc[p]=rc[q];hs[p]=hs[q];all1[p]=all1[q];}
    inline void pushup(int p){hs[p]=imadd(hs[ls(p)],hs[rs(p)]);all1[p]=all1[ls(p)]&all1[rs(p)];}
    void build(int &p,int l,int r,int s){
        p=++tot;
        if(l==r)    return hs[p]=s*qp[l],all1[p]=s,void();
        setmid;
        build(plson,s);build(prson,s);
        pushup(p);
    }
    void update(int &p,int q,int l,int r,int x){
        copy(p,q);
        if(l==r)    return hs[p]=qp[l],all1[p]=true,void();
        setmid;
        if(x<=mid) update(lson,x);
        else    update(rson,x);
        pushup(p);
    }
    void updateclear(int &p,int q,int l,int r,int pl,int pr){  // 区间覆盖成 0
        copy(p,q);
        if(l>=pl&&r<=pr)    return p=0,void();
        setmid;
        if(pl<=mid) updateclear(lson,pl,pr);
        if(pr>mid)  updateclear(rson,pl,pr);
        pushup(p);
    }
    bool query0(int p,int l,int r,int pl,int pr){  // 查询区间内有没有 0
        if(l>=pl&&r<=pr)    return !all1[p];
        setmid,res=0;
        if(pl<=mid) res=query0(plson,pl,pr);
        if(res) return true;
        if(pr>mid)  res=query0(prson,pl,pr);
        return res;
    }
    int querysame(int p,int q,int l,int r){  // 二分两棵树的极长连续前缀
        if(l==r)    return l;
        setmid;
        if(hs[rs(p)]==hs[rs(q)])    return querysame(lson);
        return querysame(rson);
    }
    int querys(int p,int l,int r,int x){  // 单点查询值
        if(l==r)    return all1[p];
        setmid;
        if(x<=mid)  return querys(plson,x);
        return querys(prson,x);
    }
    int queryhs(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return hs[p];
        setmid,res=0;
        if(pl<=mid) madd(res,queryhs(plson,pl,pr));
        if(pr>mid)  madd(res,queryhs(prson,pl,pr));
        return res;
    }
}
using namespace SegmentTree;
inline bool comp(int x,int y){  // 比较 x,y  x<y : 1
    int k=querysame(x,y,0,R);
    return querys(x,0,R,k)<querys(y,0,R,k);
}
inline void add(int x,int v){  // dis[i] += 1^v
    int l=v,r=R,res=v;
    rt[n+1]=rt[x];
    while(l<=r){
        int mid=(l+r)>>1;
        if(query0(rt[n+1],0,R,v,mid)){res=mid;r=mid-1;}
        else    l=mid+1;
    }
    if(res!=v) updateclear(rt[n+1],rt[n+1],0,R,v,res-1);
    // printf("(%d,%d) = %d\n",x,v,res);
    update(rt[n+1],rt[n+1],0,R,res);
}
struct point{
    int rt,id;
    bool operator<(point x)const{return !comp(rt,x.rt);}
};
bool vis[maxn];
priority_queue<point> q;
int pre[maxn];
void dijkstra(){
    build(rt[S],0,R,0);build(rt[0],0,R,1);
    for(int i=1;i<=n;i++)if(i!=S)rt[i]=rt[0];
    q.push({rt[S],S});
    while(!q.empty()){
        int u=q.top().id;q.pop();
        if(vis[u])  continue;
        vis[u]=true;
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            add(u,e[i].w);
            // printf("u = %d,t = %d\n",u,t);
            // printf("dis[%d] = %d\n\n",t,hs[rt[n+1]]);
            if(comp(rt[n+1],rt[t])){
                rt[t]=rt[n+1];
                pre[t]=u;
                if(!vis[t]) q.push({rt[t],t});
            }
        }
    }
}
void init(){
    qp[0]=1;
    for(int i=1;i<=R;i++)   qp[i]=immul(qp[i-1],2);
}
vector<int> ans;
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    scanf("%d%d",&S,&T);
    dijkstra();
    if(all1[rt[T]]) return puts("-1")&0;
    printf("%d\n",hs[rt[T]]);
    int p=T;ans.eb(T);
    while(p!=S){
        p=pre[p];
        ans.eb(p);
    }
    reverse(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(int i:ans)  printf("%d ",i);
}