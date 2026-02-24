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
const int maxn=5e5+10;
int n,m,lb,lc;
int a[maxn],b[maxn],c[maxn],d[maxn];
int da[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,lc
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tag[p]+=s;tr[p]+=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    void clear(setpos){tr[p]=tag[p]=0;if(l==r)return;setmid;clear(lson);clear(rson);}
    void update(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)update(lson,pl,pr,s);if(pr>mid)update(rson,pl,pr,s);pu(p);}
}
using namespace SegmentTree;
vector<int> v[maxn];
inline void upd(int i,int s){
    int ul=lower_bound(c+1,c+lc+1,i)-c,ur=lower_bound(d+1,d+lc+1,a[i],greater<int>())-d-1;
    // if(ul<=ur)  printf("%d %d %d %d\n",i,ul,ur,s);
    if(ul<=ur)update(all,ul,ur,s);
}
void discrete(){
    for(int i=1;i<=n;i++)   da[i]=a[i];
    sort(da+1,da+n+1);
    m=unique(da+1,da+n+1)-da-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(da+1,da+m+1,a[i])-da;
}
bool check(){for(int i=2;i<=n;i++)if(a[i]>a[i-1])return false;return true;}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(check()) return puts("1"),void();
    discrete();
    for(int i=1;i<=n;i++)   v[a[i]].eb(i);
    a[0]=m+1;
    lb=lc=0;
    for(int i=1;i<=n;i++)
        if(a[i]<a[b[lb]])  b[++lb]=i;
    for(int i=n;i;i--)
        if(!lc||a[i]>a[c[lc]])  c[++lc]=i,d[lc]=a[i];
    reverse(c+1,c+lc+1);reverse(d+1,d+lc+1);
    // puts("abstract");
    // for(int i=1;i<=lc;i++)   printf("%d ",d[i]);puts("");
    int ans=1;
    for(int i=1;i<=lb;i++){
        int r=a[b[i-1]],l=a[b[i]]+1;
        for(int j=r;j>=l;j--)
            for(int k:v[j]) upd(k,1);
        for(int j=b[i-1];j<b[i];j++)   upd(j,-1);
        ans=max(ans,tr[1]+2);
    }
    printf("%d\n",ans);
    for(int i=1;i<=m;i++)   v[i].clear();
    clear(all);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}