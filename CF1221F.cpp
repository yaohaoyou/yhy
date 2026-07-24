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
const int maxn=5e5+10,V=1e9,inf=1e9;
const ll INF=1e18;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
bool mem1;
int n,m;
ll ans;
struct node{int x,y,c;}a[maxn];
map<int,ll> s;
int b[maxn<<1];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    const int maxp=maxn<<3;
    ll sum[maxp],mx[maxp];int mxp[maxp];
    inline void pu(int p){sum[p]=sum[ls]+sum[rs];if(mx[ls]>mx[rs]-sum[ls])mxp[p]=mxp[ls];else mxp[p]=mxp[rs];mx[p]=max(mx[ls],mx[rs]-sum[ls]);}
    void build(setpos){if(l==r)return mxp[p]=l,void();setmid;build(lson);build(rson);pu(p);}
    void upd(setpos,int x,int s){if(l==r)return sum[p]+=s,mx[p]-=s,void();setmid;(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(p);}
    void upd2(setpos,int x){if(l==r)return mx[p]+=b[l],void();setmid;(x<=mid)?upd2(lson,x):upd2(rson,x);pu(p);}
}
using namespace SegmentTree;
set<int> st;
bool mem2;
void discrete(){
    for(int i=1;i<=n;i++)   b[++m]=a[i].y,b[++m]=a[i].y+1;
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].y=lower_bound(b+1,b+m+1,a[i].y)-b;
}
int main(){
    // maker();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].c);
        if(a[i].x==a[i].y)  st.ep(a[i].y);
        if(a[i].x<a[i].y)   swap(a[i].x,a[i].y);
    }
    // return baoli(),0;
    // puts("-1");
    sort(a+1,a+n+1,[&](node x,node y){return x.x<y.x;});
    discrete();build(all);
    ll now=0;
    // for(int i=1;i<=n;i++)printf("(%d,%d,%d)\n",a[i].x,b[a[i].y],a[i].c);
    int a1=0,a2;while(st.find(a1)!=st.end())a1++;a2=a1;
    for(int i=1,nw=1;i<=n;i++){
        while(nw<=m&&b[nw]<=a[i].x) upd2(all,nw++);
        int j=i;while(j<=n&&a[i].x==a[j].x)now+=a[j].c,j++;j--;
        for(int k=i;k<=j;k++)   upd(all,a[k].y+1,a[k].c);
        if(ans<now-a[i].x+mx[1])ans=now-a[i].x+mx[1],a1=b[mxp[1]],a2=a[i].x;
        i=j;
    }
    printf("%lld\n%d %d %d %d\n",ans,a1,a1,a2,a2);
}