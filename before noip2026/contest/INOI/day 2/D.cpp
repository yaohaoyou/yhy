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
bool mem1;
const int maxn=2e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,ans;
int a[maxn],b[maxn],d[maxn];
vector<int> v[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    // inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    inline void upd(int l,int r,int s){add(l,s);add(r+1,-s);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
void discrete(){
    for(int i=1;i<=n;i++)   d[++m]=b[i];
    sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=n;i++)   b[i]=lower_bound(d+1,d+m+1,b[i])-d;
}
int Log[maxn];
struct ST{
    pii st[20][maxn];
    void build(int* arr){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pii(arr[i],i);
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline pii query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}sa,sb;
void dvd(int l,int r){
    if(l>r) return;
    int p=sb.query(l,r).se;
    int pl,pr;
    for(pl=p;pl>=l&&a[pl]>b[p];pl--);pl++;
    for(pr=p;pr<=r&&a[pr]>b[p];pr++);pr--;
    int mx=b[p];
    if(pr==n)   madd(ans,qpow(2,mx));
    else    madd(ans,qpow(2,mx+1));
    dvd(l,pl-1);dvd(pr+1,r);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    sb.build(b);
    dvd(1,n);
    printf("%d\n",ans);
    // discrete();sa.build(a);
    // for(int i=1;i<=n;i++)   b[i]*=-1;
    // sb.build(b);
    // for(int i=1;i<=n;i++)   b[i]*=-1;
    // for(int i=1;i<=n;i++)   v[b[i]].eb(i);
    // for(int i=m;i;i--){
    //     for(int j:v[i])if(!T.que(j)){
    //         int l=j,r=n,p=0;
    //         while(l<=r){
    //             int mid=(l+r)>>1;
    //             if(sa.query(j,mid)>d[i]&&-sb.query(j,mid)==i)  p=mid,l=mid+1;
    //             else    r=mid-1;
    //         }
    //         assert(p);
    //         T.upd(j,p,1);
    //         if(p==n)    madd(ans,qpow(2,d[i]));
    //         else    madd(ans,qpow(2,d[i]+1));
    //     }
    // }
    // printf("%d\n",ans);
}