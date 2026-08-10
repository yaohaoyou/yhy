#include<bits/stdc++.h>
#define db double
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
const int maxn=4e5+10,inf=2e9;
int n,m;
db p[maxn],c[maxn];
int d[maxn];
struct node{int x,y,a,b;}A[maxn];
struct line{int k,b;}L[maxn];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];bool o;
    inline bool cmp(line a,line b,db x){return a.k*x+a.b<=b.k*x+b.b;}
    void upd(setpos,int u){
        setmid,&v=tr[p];
        if(!v)  return v=u,void();
        if(cmp(L[u],L[v],c[mid])==o)   swap(u,v);
        if(l==r)    return;
        if(cmp(L[u],L[v],c[l])==o)  upd(lson,u);
        if(cmp(L[u],L[v],c[r])==o)  upd(rson,u);
    }
    inline ll query(int x,int a,int b){
        int p=1,l=1,r=m;ll res=-4e18;
        while(l^r){
            if(tr[p])res=max(res,1ll*L[tr[p]].k*a+1ll*L[tr[p]].b*b);
            setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        if(tr[p])res=max(res,1ll*L[tr[p]].k*a+1ll*L[tr[p]].b*b);
        return res;
    }
}T[2];
void discrete(){
    for(int i=1;i<=n;i++)   c[i]=p[i];
    sort(c+1,c+n+1);m=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;i++)   d[i]=lower_bound(c+1,c+m+1,p[i])-c;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x,y,a,b;scanf("%d%d%d%d",&x,&y,&a,&b);
        L[i]={x,y};if(b)p[i]=1.0*a/b;A[i]={x,y,a,b};
    }
    discrete();
    T[0].o=1;T[1].o=0;
    int mx=-inf,mn=inf;
    for(int i=1;i<=n;i++){
        auto [x,y,a,b]=A[i];
        mx=max(mx,x);mn=min(mn,x);
        T[0].upd(all,i);T[1].upd(all,i);
        if(!b)  printf("%lld\n",max(1ll*mx*a,1ll*mn*a));
        else    printf("%lld\n",max(T[0].query(d[i],a,b),T[1].query(d[i],a,b)));
    }
}