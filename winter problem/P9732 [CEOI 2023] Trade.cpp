#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2.5e5+10;
int n,m,K;
int a[maxn],b[maxn],c[maxn],p[maxn];
ll s[maxn],F1[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,lc[q],l,mid
    #define rson rs,rc[q],mid+1,r
    #define all(x,y) rt[x],rt[y],1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int q,int l,int r
    const int maxp=maxn*20;
    int tot;
    int rt[maxn],tr[maxp],lc[maxp],rc[maxp];
    ll sum[maxp];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];sum[p]=sum[ls]+sum[rs];}
    void upd(setpos,int x){
        p=++tot;
        tr[p]=tr[q]+1;sum[p]=sum[q]+c[x];lc[p]=lc[q];rc[p]=rc[q];
        if(l==r)    return;
        setmid;(x<=mid)?upd(lson,x):upd(rson,x);
    }
    pli binary(setpos,int k){
        if(l==r)    return pli(1ll*c[l]*k,l);
        setmid;
        if(tr[rs]-tr[rc[q]]>=k)  return binary(rson,k);
        pli res=binary(lson,k-(tr[rs]-tr[rc[q]]));
        res.fi+=sum[rs]-sum[rc[q]];
        return res;
    }
}
using namespace SegmentTree;
int Log[maxn];
struct ST{
    int st[20][maxn];
    inline void upd(int l,int r,int s){int k=Log[r-l+1];gmn(st[k][l],s);gmn(st[k][r-(1<<k)+1],s);}
    void build(){
        for(int i=Log[n];i;i--)
            for(int j=1;j+(1<<i)-1<=n;j++)  gmn(st[i-1][j],st[i][j]),gmn(st[i-1][j+(1<<i>>1)],st[i][j]);
    }
}st;
void discrete(){
    memc(c,b);
    sort(c+1,c+n+1);m=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;i++)   b[i]=lower_bound(c+1,c+m+1,b[i])-c;
}
void divide(int l,int r,int opl,int opr){
    if(l>r) return;
    int mid=(l+r)>>1;
    for(int i=opl;i<=opr&&i<=mid;i++){
        if(mid-i+1<K)   break;
        pli tmp=binary(all(mid,i-1),K);
        ll w=tmp.fi-(s[mid]-s[i-1]);
        if(w>=F1[mid]) F1[mid]=w,p[mid]=i;
    }
    divide(l,mid-1,opl,p[mid]);divide(mid+1,r,p[mid],opr);
}
int main(){
    scanf("%d%d",&n,&K);
    for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;mems(st.st,0x3f);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    discrete();
    for(int i=1;i<=n;i++)   upd(all(i,i-1),b[i]);
    mems(F1,-0x3f);divide(K,n,1,n);
    ll ans1=*max_element(F1+1,F1+n+1);
    printf("%lld\n",ans1);
    for(int i=K+1;i<=n;i++) assert(p[i]>=p[i-1]);
    int lst=0;
    for(int i=K+1;i<=n;i++)if(F1[i]==ans1){
        for(int l=p[lst];l<=p[i];l++){
            pli tmp=binary(all(i,l-1),K);
            if(tmp.fi-(s[i]-s[l-1])==ans1)  st.upd(l,i,tmp.se);
        }
        lst=i;
    }
    st.build();
    for(int i=1;i<=n;i++)   printf("%d",b[i]>=st.st[0][i]);
}