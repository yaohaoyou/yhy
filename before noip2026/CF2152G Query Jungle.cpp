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
const int maxn=2.5e5+10;
bool mem1;
int n,q;
int a[maxn],f[maxn][2];
int tot;
int siz[maxn],son[maxn],dfsn[maxn],rnk[maxn],tp[maxn],fa[maxn];
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
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    bool tag[maxn<<2];
    int ad[maxn<<2][2],tr[maxn<<2][2],cnt[maxn<<2][2];
    inline void pu(int p){cnt[p][0]=cnt[ls][0]+cnt[rs][0];cnt[p][1]=cnt[ls][1]+cnt[rs][1];}
    inline void R(int p){tag[p]^=1;swap(ad[p][0],ad[p][1]);swap(tr[p][0],tr[p][1]);swap(cnt[p][0],cnt[p][1]);}
    inline void A(int p,int s0,int s1){tr[p][0]+=s0;tr[p][1]+=s1;ad[p][0]+=s0;ad[p][1]+=s1;}
    inline void pd(int p){if(tag[p])R(ls),R(rs),tag[p]=false;if(ad[p][0]||ad[p][1])A(ls,ad[p][0],ad[p][1]),A(rs,ad[p][0],ad[p][1]),ad[p][0]=ad[p][1]=0;}
    void rev(setpos,int pl,int pr){if(l>=pl&&r<=pr)return R(p);pd(p);setmid;if(pl<=mid)rev(lson,pl,pr);if(pr>mid)rev(rson,pl,pr);pu(p);}
    void add(setpos,int pl,int pr,int s0,int s1){if(l>=pl&&r<=pr)return A(p,s0,s1);pd(p);setmid;if(pl<=mid)add(lson,pl,pr,s0,s1);if(pr>mid)add(rson,pl,pr,s0,s1);pu(p);}
    int bry(setpos,int pl,int pr,bool o){
        if(!cnt[p][o])  return 0;
        if(l==r)    return l;
        pd(p);setmid;
        if(l>=pl&&r<=pr){
            if(cnt[rs][o])  return bry(rson,pl,pr,o);
            return bry(lson,pl,pr,o);
        }
        if(pr<=mid) return bry(lson,pl,pr,o);
        if(pl>mid)  return bry(rson,pl,pr,o);
        int x=bry(rson,pl,pr,o);if(x)return x;
        return bry(lson,pl,pr,o);
    }
    int qry(setpos,int pl,int pr){if(l>=pl&&r<=pr)return cnt[p][0];pd(p);setmid,res=0;if(pl<=mid)res=qry(lson,pl,pr);if(pr>mid)res+=qry(rson,pl,pr);return res;}
    inline int Q(int x,bool o){x=dfsn[x];int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p][o];}
    void build(setpos){
        tag[p]=ad[p][0]=ad[p][1]=tr[p][0]=tr[p][1]=cnt[p][0]=cnt[p][1]=0;
        if(l==r)return tr[p][0]=f[rnk[l]][0],tr[p][1]=f[rnk[l]][1],cnt[p][!a[rnk[l]]]=1,void();
        setmid;build(lson);build(rson);pu(p);
    }
}
using namespace SegmentTree;
void dfs1(int u,int ft){fa[u]=ft;son[u]=0;siz[u]=1;go(u,i)if(t^ft){dfs1(t,u);siz[u]+=siz[t];if(siz[t]>siz[son[u]])son[u]=t;}}
void dfs2(int u,int ft){rnk[dfsn[u]=++tot]=u;if(son[u])tp[son[u]]=tp[u],dfs2(son[u],u);go(u,i)if((t^ft)&&(t^son[u]))tp[t]=t,dfs2(t,u);}
void dfs(int u,int ft){
    f[u][0]=f[u][1]=0;
    go(u,i)if(t^ft)dfs(t,u),f[u][0]+=f[t][0],f[u][1]+=f[t][1];
    if(!f[u][0]&&a[u])  f[u][0]=1;
    if(!f[u][1]&&!a[u]) f[u][1]=1;
}
int find_top(int x,bool o){
    while(x){
        int res=bry(all,dfsn[tp[x]],dfsn[x],o);if(res)return rnk[res];
        x=fa[tp[x]];
    }
    return 0;
}
void add_path(int x,int s0,int s1){
    while(x){
        add(all,dfsn[tp[x]],dfsn[x],s0,s1);
        x=fa[tp[x]];
    }
}
void ad_path(int x,int y,int s0,int s1){
    while(tp[x]^tp[y]){
        add(all,dfsn[tp[x]],dfsn[x],s0,s1);
        x=fa[tp[x]];
    }
    if(x^y)add(all,dfsn[y]+1,dfsn[x],s0,s1);
}
bool mem2;
void matt(int _cases){
    rebuild();tot=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);dfs2(tp[1]=1,0);
    dfs(1,0);
    build(all);
    printf("%d\n",Q(1,0));
    scanf("%d",&q);
    while(q--){
        int x;scanf("%d",&x);//printf("x = %d\n",x);
        int bf0=Q(x,0),bf1=Q(x,1),c=qry(all,dfsn[x],dfsn[x]+siz[x]-1);
        rev(all,dfsn[x],dfsn[x]+siz[x]-1);
        int d0=Q(x,0)-bf0,d1=Q(x,1)-bf1;
        if(!c||c==siz[x]){
            int u=find_top(fa[x],0),uu=find_top(fa[x],1);
            // printf("u = %d %d\n",u,d0);
            if(fa[x])ad_path(fa[x],u,d0,0),ad_path(fa[x],uu,0,d1);
            if(u){
                if(!c&&qry(all,dfsn[u],dfsn[u]+siz[u]-1)==siz[x]+1)d0--;
                if(c==siz[x]&&qry(all,dfsn[u],dfsn[u]+siz[u]-1)==1)d0++;
                if(d0) add_path(u,d0,0);
            }
            u=uu;
            if(u){
                if(!c&&qry(all,dfsn[u],dfsn[u]+siz[u]-1)==siz[u]-1)d1++;
                if(c==siz[x]&&qry(all,dfsn[u],dfsn[u]+siz[u]-1)==siz[u]-siz[x]-1)d1--;
                if(d1)  add_path(u,0,d1);
            }
        }
        else if(fa[x])add_path(fa[x],d0,d1);
        printf("%d\n",Q(1,0));
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}