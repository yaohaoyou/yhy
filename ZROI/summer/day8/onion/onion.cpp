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
const int maxn=3e5+10;
int n,q;
int a[maxn];
struct st{
    int st[20][maxn],Log[maxn];
    void build(int arr[]){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=arr[i];
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}mn,mx,stl;
inline int qmn(int l,int r){return mn.query(l,r);}
inline int qmx(int l,int r){return -mx.query(l,r);}
inline int ql(int l,int r){return -stl.query(l,r);}
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline void upd(int l,int r,int s){if(l<=r)add(l,s),add(r+1,-s);}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T[3];
int p[maxn],R[maxn],L[maxn];
vector<int> v[maxn];
vector<pii> Q[maxn];
ll query(int l,int r){
    ll ans=0;
    for(int i=l;i<=r;i++)   ans+=min(r,p[i])-i+1;
    return ans;
}
ll ans[maxn];
int main(){
    freopen("onion.in","r",stdin);freopen("onion.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    mn.build(a);
    for(int i=1;i<=n;i++)a[i]=-a[i];mx.build(a);for(int i=1;i<=n;i++)a[i]=-a[i];
    for(int i=1;i<=n;i++){
        int l=i,r=n,p=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(qmn(i,mid)==a[i]||qmx(i,mid)==a[i])  p=mid,l=mid+1;
            else r=mid-1;
        }
        R[i]=p;
        l=1,r=i,p=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(qmn(mid,i)==a[i]||qmx(mid,i)==a[i])  p=mid,r=mid-1;
            else l=mid+1;
        }
        L[i]=-p;
    }
    stl.build(L);for(int i=1;i<=n;i++)  L[i]=-L[i];
    p[n]=n;
    for(int i=n-1;i;i--){
        if(R[i]>=p[i+1]){p[i]=p[i+1];continue;}
        int l=R[i]+1,r=n,pp;
        while(l<=r){
            int mid=(l+r)>>1;
            if(ql(R[i]+1,mid)<=i)   pp=mid,l=mid+1;
            else    r=mid-1;
        }
        p[i]=pp;
    }
    for(int i=1;i<=n;i++)   v[p[i]].eb(i);
    for(int i=1;i<=q;i++){
        int l,r;scanf("%d%d",&l,&r);
        Q[r].eb(l,i);
    }
    for(int i=1;i<=n;i++)   T[0].add(i,p[i]-i+1);
    for(int i=n;i;i--){
        for(auto [l,id]:Q[i])ans[id]=T[0].query(l,i)+T[1].query(l,i)*(i+1)-T[2].query(l,i);
        for(int j:v[i]) T[0].add(j,-(p[j]-j+1)),T[1].add(j,1),T[2].add(j,j);
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}