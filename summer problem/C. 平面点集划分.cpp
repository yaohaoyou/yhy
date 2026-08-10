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
const ll INF=1e18;
int n;ll sa[maxn],sb[maxn];
struct node{int x,y,a,b;}p[maxn];
int a[maxn],m;ll c[maxn];
void discrete(){
    m=0;
    for(int i=1;i<=n;i++)   a[++m]=p[i].y;
    a[++m]=0;
    sort(a+1,a+m+1);m=unique(a+1,a+m+1)-a-1;
    for(int i=1;i<=n;i++)   p[i].y=lower_bound(a+1,a+m+1,p[i].y)-a;
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,ll s){tag[p]+=s;tr[p]+=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;ll res=-INF;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
    void upd(setpos,int pl,int pr,ll s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline void upd(int x,ll s){int p=1,l=1,r=m;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=max(tr[p],s);while(p>>=1)pu(p);}
    void build(setpos){tag[p]=0;tr[p]=-INF;if(l==r)return;setmid;build(lson);build(rson);pu(p);}
    void clr(setpos){tag[p]=0;tr[p]=-INF;if(l==r)return;setmid;clr(lson);clr(rson);}
}
using namespace SegmentTree;
void matt(){
    if(m)clr(all);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d%d%d",&p[i].x,&p[i].y,&p[i].a,&p[i].b);
    sort(p+1,p+n+1,[&](node x,node y){return pii(x.x,x.y)<pii(y.x,y.y);});
    discrete();
    for(int i=1;i<=n;i++)   sa[i]=sa[i-1]+p[i].a;
    for(int i=1;i<=n;i++)   sb[i]=sb[i-1]+p[i].b;
    build(all);upd(1,0);
    p[n+1].x=0;
    for(int l=1;l<=n;l++){
        int r=l;while(p[r].x==p[l].x)r++;r--;
        for(int i=r;i>=l;i--){
            upd(p[i].y,query(all,1,p[i].y)+sb[i]-sb[l-1]+sa[r]-sa[i]);
            // 区间查，单点加
            // for(int j=0;j<l;j++){
            //     if(p[j].y<=p[i].y)
            //         dp[r][i]=max(dp[r][i],dp[l-1][j]+sb[i]-sb[l-1]+sa[r]-sa[i]);
            // }
        }

        //  区间加
        // for(int j=0;j<l;j++)
        //     if(p[l].y>p[j].y)   dp[r][j]=max(dp[r][j],dp[l-1][j]+sa[r]-sa[l-1]);
        upd(all,1,p[l].y-1,sa[r]-sa[l-1]);
        for(int i=l;i<=r;i++){
            // for(int j=0;j<l;j++){
            //     // 区间加
            //     if(p[j].y>p[i].y&&(i==r||p[j].y<p[i+1].y))  dp[r][j]=max(dp[r][j],dp[l-1][j]+sb[i]-sb[l-1]+sa[r]-sa[i]);
            // }
            int L=p[i].y+1,R=(i^r)?p[i+1].y-1:m;
            if(L<=R)    upd(all,L,R,sb[i]-sb[l-1]+sa[r]-sa[i]);
        }
        l=r;
    }
    printf("%lld\n",tr[1]);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}