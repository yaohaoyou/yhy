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
const int maxn=3e5+10,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
int p[maxn],v[maxn],ls[maxn],rs[maxn],rt[maxn];
// int dp[maxn][maxn];
namespace SegmentTree{
    #define ls(p) lc[p]
    #define rs(p) rc[p]
    #define lson ls(p),l,mid
    #define rson rs(p),mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int tot;
    int lc[maxn*20],rc[maxn*20],sum[maxn*20],tag[maxn*20];
    inline void pu(int p){sum[p]=imadd(sum[ls(p)],sum[rs(p)]);}
    inline void pt(int p,int s){mmul(sum[p],s);mmul(tag[p],s);}
    inline void pd(int p){if(tag[p]^1){if(ls(p))pt(ls(p),tag[p]);if(rs(p))pt(rs(p),tag[p]);tag[p]=1;}}
    int merge(int x,int y,int l,int r,int s1,int s2,int P){
        if(x&&!y)   pt(x,s1);
        if(!x&&y)   pt(y,s2);
        if(!x||!y)  return x|y;
        pd(x);pd(y);
        setmid;
        int lsx=sum[ls(x)],lsy=sum[ls(y)];
        ls(x)=merge(ls(x),ls(y),l,mid,imadd(s1,immul(1+mod-P,sum[rs(y)])),imadd(s2,immul(1+mod-P,sum[rs(x)])),P);
        rs(x)=merge(rs(x),rs(y),mid+1,r,imadd(s1,immul(P,lsy)),imadd(s2,immul(P,lsx)),P);
        pu(x);return x;
    }
    void upd(setpos,int x,int s){if(!p)p=++tot,tag[p]=1;if(l==r)return sum[p]=s,void();setmid;pd(p);(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(p);}
    inline int query(int x,int c){int p=rt[c],l=1,r=m;while(l^r){if(!p)return -1;pd(p);setmid;(x<=mid)?(p=ls(p),r=mid):(p=rs(p),l=mid+1);}if(!p)return -1;return sum[p];}
}
using namespace SegmentTree;
void dfs(int u){
    if(ls[u])   dfs(ls[u]),rt[u]=rt[ls[u]];
    else    upd(rt[u],1,m,p[u],1);
    if(rs[u]){dfs(rs[u]);rt[u]=merge(rt[u],rt[rs[u]],1,m,0,0,p[u]);}
}
void discrete(){
    sort(v+1,v+m+1);m=unique(v+1,v+m+1)-v-1;
    for(int i=1;i<=n;i++)if(!ls[i])p[i]=lower_bound(v+1,v+m+1,p[i])-v;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);if(!x)continue;if(!ls[x])ls[x]=i;else rs[x]=i;}
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        if(ls[i])   mmul(p[i],qpow(10000,mod-2));
        else    v[++m]=p[i];
    }
    discrete();
    dfs(1);
    int ans=0;
    for(int i=1;i<=m;i++){
        int d=query(i,1);
        madd(ans,1ull*i*v[i]%mod*d%mod*d%mod);
    }
    printf("%d\n",ans);
}