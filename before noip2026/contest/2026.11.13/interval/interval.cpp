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
inline void gmx(auto &x,auto y){if(x<y)x=y;}
using namespace std;
const int maxn=2e5+10,inf=2e9;
bool mem1;
int n;
int f[maxn],b[maxn];
bool in[maxn];
pii a[maxn];
vector<int> v;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii mx[maxn<<2];
    int mn[maxn<<2],tag[maxn<<2],pos[maxn];
    inline void pu(int p){mx[p]=max(mx[ls],mx[rs]);}
    inline void pt(int p,int s){tag[p]+=s;mx[p].fi+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){tag[p]=0;if(l==r)return mx[p]=pii(b[l]-l,-l),mn[p]=a[l].se,pos[l]=p,void();setmid;build(lson);build(rson);pu(p);mn[p]=min(mn[ls],mn[rs]);}
    inline void upd(int x){int p=pos[x];mn[p]=inf;while(p>>=1)mn[p]=min(mn[ls],mn[rs]);}
    int bry(setpos,int pr){
        if(l==r)    return l;
        setmid;
        if(r<=pr)   return mn[p]==mn[ls]?bry(lson,pr):bry(rson,pr);
        if(pr<=mid) return bry(lson,pr);
        int x=bry(lson,pr),y=bry(rson,pr);
        if(in[x])return y;if(in[y])return x;
        return a[x].se<a[y].se?x:y;
    }
    void U(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)U(lson,pl,pr,s);if(pr>mid)U(rson,pl,pr,s);pu(p);}
    pii Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mx[p];pd(p);setmid;pii res=pii(-inf,0);if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)gmx(res,Q(rson,pl,pr));return res;}
}
using namespace SegmentTree;
bool check(int k){
    v.clear();fll(f,n,n);fll(b,0,n);fll(in,0,n);
    b[n]=n-1;
    build(all);
    v.eb(0);for(int i=1;i<=n;i++)if(a[i].se<a[v[0]].se)v[0]=i;
    in[v[0]]=true;upd(v[0]);
    int p=1;
    while(v.size()^n){
        while(p<=n&&a[p].fi<=a[v.back()].se){
            if(v.size()+k>=n)    break;
            if(!in[p]){
                f[p]=v.size()+k;
                U(all,f[p],n-1,1);
            }
            else    f[p]=v.size()+k;
            p++;
        }
        pii t=Q(all,v.size()+1,n);
        if(t.fi>-int(v.size()))  return false;
        assert(t.fi==-int(v.size()));
        int nw=-t.se;
        assert(nw);
        int l=1,r=n,R=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(f[mid]<=nw)  R=mid,l=mid+1;
            else    r=mid-1;
        }
        v.eb(bry(all,R));
        assert(v.back());U(all,f[v.back()],n,-1);in[v.back()]=true;
        upd(v.back());
    }
    return true;
}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    bool fl=true;for(int i=2;i<=n;i++)fl&=a[i-1].se<a[i].fi;
    if(fl){
        puts("0");
        for(int i=1;i<=n;i++)printf("%d %d\n",a[i].fi,a[i].se);
        return;
    }
    a[0].se=inf;
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else    l=mid+1;
    }
    printf("%d\n",ans);
    check(ans);for(int i:v)printf("%d %d\n",a[i].fi,a[i].se);
}
int main(){freopen("interval.in","r",stdin);freopen("interval.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}