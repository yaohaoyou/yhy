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
const int maxn=5e5+10;
int n,D,q,qq;
int a[maxn],fa[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],id=e[i].to;i;i=e[i].nxt,id=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) rt[x],1,n
    #define al 1,1,D
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int cur;
    int rt[maxn<<2];
    int len[maxn*40],lc[maxn*40],rc[maxn*40];
    ll tr[maxn*40],tag[maxn*40];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int &p,ll s){if(!p)p=++cur;tr[p]+=s*len[p];tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    inline void U(int &p,int x,int s){
        if(!p)p=++cur;int l=1,r=n,P=p;
        while(l^r){
            len[p]++;tr[p]+=s;
            printf("%d += %d\n",p,s);
            setmid;
            if(x<=mid){
                if(!ls)ls=++cur;
                p=ls,r=mid;
            }
            else{
                if(!rs)rs=++cur;
                p=rs,l=mid+1;
            }
        }
        printf("%d += %d\n\n",p,s);
        len[p]++;tr[p]+=s;
        p=P;
    }
    void upd(setpos,int pl,int pr,int s){if(!p)p=++cur;if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    ll qry(setpos,int pl,int pr){if(!p)return 0;if(l>=pl&&r<=pr)return printf("[%d,%d] %d : %d\n",l,r,p,tr[p]),tr[p];pd(p);setmid;ll res=0;if(pl<=mid)res=qry(lson,pl,pr);if(pr>mid)res+=qry(rson,pl,pr);return res;}
    #define ls p<<1
    #define rs p<<1|1
    #define setpos int p,int l,int r
    void add(setpos,int x,int pl,int pr,ll s,bool fl){if(r<=x)return fl?U(rt[p],pl,s):upd(all(p),pl,pr,s);setmid;add(lson,x,pl,pr,s,fl);if(x>mid)add(rson,x,pl,pr,s,fl);}
    ll que(setpos,int x,int pl,int pr){if(r<=x)return qry(all(p),pl,pr);setmid;ll res=que(lson,x,pl,pr);if(x>mid)res+=que(rson,x,pl,pr);return res;}
}
using namespace SegmentTree;
// struct BIT{
//     ll tr[maxn];
//     inline int lowbit(int x){return x&-x;}
//     inline void add(int x,int l,int r,ll s){while(x){upd(all(x),l,r,s);x^=lowbit(x);}}
//     inline ll que(int x,int l,int r){ll res=0;while(x<=D){res+=qry(all(x),l,r);x+=lowbit(x);}return res;}
//     void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
// }T;
ll ans[maxn];
int L[maxn],R[maxn],rk[maxn],dep[maxn],tot;
struct ques{
    int l,r,d,v,id;
}Q[maxn<<1];
void dfs(int u){
    rk[L[u]=++tot]=u;
    dep[L[u]]=dep[L[fa[u]]]+1;gmx(D,dep[L[u]]);
    go(u,i)dfs(id);
    R[u]=tot;
}
// void dvd(int l,int r){
//     if(l==r)return;
//     int mid=(l+r)>>1;
//     vector<ques> vec;
//     for(int i=l;i<=mid;i++)if(~Q[i].v)vec.eb(Q[i]);
//     for(int i=mid+1;i<=r;i++)if(!~Q[i].v)vec.eb(Q[i]);
//     sort(vec.begin(),vec.end(),[&](ques x,ques y){return x.d==y.d?x.id<y.id:x.d<y.d;});
//     printf("[%d,%d]\n",l,r);
//     for(auto [L,R,d,v,id]:vec){
//         if(~v)   U(L,R,v);
//         else    ans[id]+=qry(L,R);
//     }
//     for(auto [L,R,d,v,id]:vec)if(~v)U(L,R,-v);
//     dvd(l,mid);dvd(mid+1,r);
// }
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=2;i<=n;i++)   scanf("%d",&fa[i]),add(fa[i],i);
    dfs(1);
    for(int i=1;i<=n;i++)   add(al,dep[L[i]],L[i],L[i],a[i],1);
    for(int i=1;i<=q;i++){
        int op,x,d,v;scanf("%d%d%d",&op,&x,&d);
        if(op==1){
            scanf("%d",&v);
            add(al,dep[L[x]]+d,L[x],R[x],v,0);
            // Q[++qq]={L[x],R[x],dep[L[x]]+d,v,i};
            // for(int i=L[x];i<=R[x];i++)
            //     if(dep[i]<=dep[L[x]]+d) a[i]+=v;
        }
        else{
            printf("%lld\n",que(al,dep[L[x]]+d,L[x],R[x]));
            // Q[++qq]={L[x],R[x],dep[L[x]]+d,-1,i};
            // ll ans=0;
            // for(int i=L[x];i<=R[x];i++)
            //     if(dep[i]<=dep[L[x]]+d) ans+=a[i];
            // printf("%lld\n",ans);
        }
    }
    // dvd(1,qq);
    // for(int i=1;i<=q;i++)if(!~Q[i+n].v)printf("%lld\n",ans[i]);
}