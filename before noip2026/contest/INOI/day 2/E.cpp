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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e5+10;
int n,q;
int a[maxn];
ll s[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,ll s){tag[p]+=s;tr[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){if(l==r)return tr[p]=s[l],void();setmid;build(lson);build(rson);pu(p);}
    void upd(setpos,int pl,int pr,ll s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline ll query(int x){if(!x)return 0;int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p];}
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    build(all);
    while(q--){
        char op[5];int x,v;scanf("%s%d",op,&x);
        if(op[0]=='?'){
            ll ans=1e18;
            if(x==1){
                int l=0,r=n-x,p=1;ll sum=query(n);
                while(l<=r){
                    setmid;
                    ll si=query(mid),sx=query(mid+x);
                    if(si+sx>=sum)   p=mid,r=mid-1;
                    else    l=mid+1;
                }
                gmn(ans,abs(query(p)-sum+query(p+x)));
                p--;
                if(p>=0)gmn(ans,abs(query(p)-sum+query(p+x)));
            }
            else{
                int l=0,r=n-x,p=1;ll sum=query(n);
                while(l<=r){
                    setmid;
                    ll si=mid?query(mid):0,sx=query(mid+x);
                    if(si+sx>sum)   p=mid,r=mid-1;
                    else    l=mid+1;
                }
                gmn(ans,abs(query(p)-sum+query(p+x))+query(p+x)-query(p));
                p--;
                if(p>=0)gmn(ans,abs(query(p)-sum+query(p+x))+query(p+x)-query(p));
            }
            printf("%lld\n",ans);
        }
        else{
            scanf("%d",&v);
            upd(all,x,n,-a[x]);
            a[x]=v;
            upd(all,x,n,a[x]);
        }
    }
}