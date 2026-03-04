#include<bits/stdc++.h>
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
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n,m,k;
struct node{
    int a,b,c,k,ans;
    bool operator<(const node &x)const{return piii(pii(a,b),c)<piii(pii(x.a,x.b),x.c);}
    bool operator==(const node &x){return a==x.a&&b==x.b&&c==x.c;}
}a[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=k){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
node b[maxn];
int ans[maxn];
void divide(int l,int r){
    if(l==r)    return;
    int mid=(l+r)>>1;
    divide(l,mid);divide(mid+1,r);
    sort(a+l,a+mid+1,[&](node x,node y){return x.b<y.b;});
    sort(a+mid+1,a+r+1,[&](node x,node y){return x.b<y.b;});
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid&&a[j].b<=a[i].b)   T.add(a[j].c,a[j].k),j++;
        a[i].ans+=T.que(a[i].c);
    }
    while(--j>=l)   T.add(a[j].c,-a[j].k);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c),b[i]=a[i];
    sort(a+1,a+n+1);
    m=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;i++)   a[lower_bound(a+1,a+m+1,b[i])-a].k++;
    divide(1,m);
    sort(a+1,a+m+1);
    // for(int i=1;i<=m;i++)   printf("%d,%d,%d %d %d\n",a[i].a,a[i].b,a[i].c,a[i].k,a[i].ans);
    for(int i=1;i<=n;i++){
        int p=lower_bound(a+1,a+m+1,b[i])-a;
        ans[a[p].ans+a[p].k-1]++;
    }
    for(int i=0;i<n;i++)    printf("%d\n",ans[i]);
}