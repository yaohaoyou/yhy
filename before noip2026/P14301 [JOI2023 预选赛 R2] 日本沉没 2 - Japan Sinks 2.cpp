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
const int maxn=3e5+10;
int n,q;
int a[maxn],c[maxn],pr[maxn],sf[maxn];
set<int> s;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii tl[maxn<<2],tr[maxn<<2];
    int mn[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tl[p]=max(tl[ls],tl[rs]);tr[p]=max(tr[ls],tr[rs]);mn[p]=min(mn[ls],mn[rs]);}
    inline void pt(int p,int s){tl[p].fi+=s;tr[p].fi+=s;mn[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){
        if(l==r){
            tl[p]=pii(c[l],-l),tr[p]=pii(c[l],l);
            if(a[l]==c[l])  mn[p]=1e9;
            else    mn[p]=c[l]-a[l];
            return;
        }
        setmid;build(lson);build(rson);pu(p);
    }
    inline int binary(){
        int p=1,l=1,r=n;
        while(l^r){
            pd(p);setmid;
            if(!mn[ls]) p=ls,r=mid;
            else    p=rs,l=mid+1;
        }
        mn[p]=1e9;
        while(p>>=1)    pu(p);
        return l;
    }
    void U(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)U(lson,pl,pr,s);if(pr>mid)U(rson,pl,pr,s);pu(p);}
    inline int Q(int x){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p].fi;}
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),pr[i]=max(pr[i-1],a[i]);
    for(int i=n;i;i--)  sf[i]=max(sf[i+1],a[i]);
    for(int i=1;i<=n;i++){
        c[i]=min(pr[i],sf[i]);
        if(a[i]==c[i])  s.ep(i);
    }
    build(all);
    while(q--){
        int t,x;scanf("%d%d",&t,&x);
        int l=-tl[1].se,r=tr[1].se;
        if(t==1){
            if(x>=r)    U(all,1,r,-1);
            else    U(all,1,*s.upper_bound(x)-1,-1);
        }
        else if(t==2){
            x=n-x+1;
            if(x<=l)    U(all,l,n,-1);
            else    U(all,*prev(s.lower_bound(x))+1,n,-1);
        }
        else    printf("%d\n",min(a[x],Q(x)));
        while(!mn[1])   s.ep(binary());
    }
}