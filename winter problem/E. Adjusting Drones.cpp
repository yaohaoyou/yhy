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
const int maxn=1e6+10,inf=1e9;
int n,m,k;
int a[maxn],b[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],sum[maxn<<2],len[maxn<<2];
    bool tag[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);sum[p]=sum[ls]+sum[rs];}
    inline void pt(int p){tag[p]=1;tr[p]=inf;sum[p]=len[p];}
    inline void pd(int p){if(tag[p])pt(ls),pt(rs),tag[p]=0;}
    void build(setpos){tag[p]=0;tr[p]=0;if(l==r){tr[p]=b[l]?inf:l;len[p]=1;sum[p]=b[l];return;}setmid;build(lson);build(rson);pu(p);len[p]=len[ls]+len[rs];}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return sum[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    // int binary(setpos,int x){
    //     if(tr[p]==inf)  return -1;
    //     if(l==r)    return l;
    //     pd(p);setmid;
    //     if(x>mid)   return binary(rson,x);
    //     int res=binary(lson,x);if(res)return res;
    //     return binary(rson,x);
    // }
    inline void upd(int x,int s){int p=1,l=1,r=m;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}sum[p]=s;tr[p]=s?inf:l;while(p>>=1)pu(p);}
}
using namespace SegmentTree;
set<int> s;
void matt(int _cases){
    scanf("%d%d",&n,&k);m=5*n;
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);b[a[i]]++;}
    s.clear();for(int i=1;i<=m;i++)if(!b[i])s.ep(i);
    build(all);
    int ans=0;
    for(int i=n+n;i;i--){
        int p=i;
        while(1){
            if(b[p]<=k)  break;
            int q=*s.lower_bound(p);s.erase(q);
            b[q]=query(all,p,q)-(q-p);
            // printf("%d %d %d\n",p,q,b[q]);
            upd(q,b[q]);upd(all,p,q-1);
            p=q;
        }
        ans=max(ans,p-i);
    }
    printf("%lld\n",ans);
    for(int i=0;i<=m;i++)b[i]=0;
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}