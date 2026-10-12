#include<bits/stdc++.h>
#define int long long
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n;
piii a[maxn];
int b[maxn];
set<int> liv;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],rk[maxn<<2],as[maxn<<2],ad[maxn<<2],trk[maxn<<2],len[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];rk[p]=rk[ls]+rk[rs];len[p]=len[ls]+len[rs];}
    inline void pt(int p,int s){as[p]=s;tr[p]=s*len[p];ad[p]=0;}
    inline void pt2(int p,int s){ad[p]+=s;tr[p]+=s*len[p];}
    inline void pa(int p,int s){rk[p]+=s*len[p];trk[p]+=s;}
    inline void pd(int p){if(~as[p])pt(ls,as[p]),pt(rs,as[p]),as[p]=-1;if(ad[p])pt2(ls,ad[p]),pt2(rs,ad[p]),ad[p]=0;if(trk[p])pa(ls,trk[p]),pa(rs,trk[p]),trk[p]=0;}
    void build(setpos){as[p]=-1;if(l==r)return tr[p]=a[l].fi.fi-l,rk[p]=l,len[p]=1,void();setmid;build(lson);build(rson);pu(p);}
    inline int RK(int x){int p=1,l=1,r=n;while(l^r){setmid;pd(p);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return rk[p];}
    inline int TR(int x){int p=1,l=1,r=n;while(l^r){setmid;pd(p);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p];}
    inline int pos(int x){int p=1,l=1,r=n;while(l^r){setmid;pd(p);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p]+rk[p];}
    int Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p]+rk[p];pd(p);setmid,res=0;if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)res+=Q(rson,pl,pr);return res;}
    void U(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)U(lson,pl,pr,s);if(pr>mid)U(rson,pl,pr,s);pu(p);}
    void A(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt2(p,s);setmid;pd(p);if(pl<=mid)A(lson,pl,pr,s);if(pr>mid)A(rson,pl,pr,s);pu(p);}
    void K(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pa(p,s),pt2(p,-s);setmid;pd(p);if(pl<=mid)K(lson,pl,pr,s);if(pr>mid)K(rson,pl,pr,s);pu(p);}
    inline void kil(int x){liv.erase(x);int p=1,l=1,r=n;while(l^r){setmid;pd(p);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=rk[p]=len[p]=0;while(p>>=1)pu(p);}
}
using namespace SegmentTree;
inline int sum(int l,int r){return (l+r)*(r-l+1)/2;}
inline int bry(int x){
    int l=1,r=n,p=0;
    while(l<=r){
        int mid=(l+r)>>1;
        auto it=liv.lower_bound(mid);
        if(it==liv.end()){r=mid-1;continue;}
        if(TR(*it)+1<x) p=mid,l=mid+1;
        else    r=mid-1;
    }
    return p;
}
bool mem2;
main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i].fi.fi);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i].fi.se);
    sort(a+1,a+n+1);
    build(all);
    for(int i=1;i<=n;i++)   a[i].se=i,swap(a[i].fi.fi,a[i].fi.se),liv.ep(i);
    sort(a+1,a+n+1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        int id=a[i].se,x=pos(id),y=a[i].fi.fi;
        // printf("%d %d : %d\n",a[i].fi.se,y,x);
        if(x>=y){
            int k=bry(y);
            // printf("! %d %d %d\n",k,TR(id),RK(id));
            if(k){
                ans+=sum(y,y+RK(k)-1)-Q(all,1,k);
                U(all,1,k,y-1);
                x=pos(id);assert(x>=y);
                ans+=x-y;
                kil(id);A(all,1,id,1);K(all,id,n,-1);
            }
            else{
                ans+=x-y;
                kil(id);A(all,1,id,1);K(all,id,n,-1);
            }
        }
        else{
            int k=bry(y);assert(k);
            ans+=sum(y,y+RK(k)-1)-Q(all,1,k);
            U(all,1,k,y-1);
            x=pos(id);//assert(x>=y);;
            ans+=x-y;
            kil(id);A(all,1,id,1);K(all,id,n,-1);
        }
        // printf("%lld\n",ans);
    }
    printf("%lld\n",ans);
}