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
const int maxn=2e5+10;
int n,m;
int a[maxn],b[maxn];
// int dp[maxn][maxn];
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
namespace SegmentTree{
    #define ls(p) lc[p]
    #define rs(p) rc[p]
    #define lson ls(p),l,mid
    #define rson rs(p),mid+1,r
    #define all(x) rt[x],1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int rt[maxn];
    int tr[maxn*20],lc[maxn*20],rc[maxn*20],tag[maxn*20];
    int cur;
    inline void pu(int p){tr[p]=max(tr[ls(p)],tr[rs(p)]);}
    inline void pt(int p,int s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p]){if(ls(p))pt(ls(p),tag[p]);if(rs(p))pt(rs(p),tag[p]);tag[p]=0;}}
    void upd(setpos,int x,int s){if(!p)p=++cur;if(l==r)return tr[p]=s,void();pd(p);setmid;(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(p);}
    int merge(int x,int y,int l,int r,int tx,int ty){
        if(!x&&y)   pt(y,ty);
        if(x&&!y)   pt(x,tx);
        if(!x||!y)  return x|y;
        pd(x);pd(y);setmid;
        ls(x)=merge(ls(x),ls(y),l,mid,max(tx,tr[rs(y)]),max(ty,tr[rs(x)]));
        rs(x)=merge(rs(x),rs(y),mid+1,r,tx,ty);
        pu(x);
        return x;
    }
    int query(setpos,int pl,int pr){
        if(!p)  return 0;
        if(l>=pl&&r<=pr)    return tr[p];
        pd(p);
        setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));
        return res;
    }
}
using namespace SegmentTree;
void discrete(){
    memc(b,a);sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
void dfs(int u){
    go(u,j){
        dfs(t);
        if(!rt[u])  rt[u]=rt[t];
        else    rt[u]=merge(rt[u],rt[t],1,m,0,0);
    }
    int dp=query(rt[u],1,m,a[u],m)+1;
    upd(all(u),a[u],dp);
    // int l=1,r=a[u],p=0;
    // while(l<=r){
    //     int mid=(l+r)>>1;
    //     if(dp[u][mid]<dp[u][a[u]]+1)    p=mid,r=mid-1;
    //     else    l=mid+1;
    // }
    // for(int i=p;i<=a[u];i++)    dp[u][i]=dp[u][a[u]]+1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);add(x,i);}
    discrete();dfs(1);
    int ans=tr[rt[1]];
    printf("%d\n",ans);
}