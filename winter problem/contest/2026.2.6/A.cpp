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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn];
int mn,mx;
inline int chk(int l,int r,int x){
    for(int i=1;i<=n;i++)   b[i]=a[i];
    for(int i=l;i<=r;i++)   b[i]+=x;
    return *max_element(b+1,b+n+1)-*min_element(b+1,b+n+1);
}
inline bool check(int x){
    int L=n,R=1;
    for(int i=1;i<=n;i++){
        if(a[i]>x+mn)   gmn(L,i),gmx(R,i);
    }
    if(L>R||chk(L,R,-mx+mn+x)<=x)    return true;
    L=n,R=1;
    for(int i=1;i<=n;i++){
        if(a[i]<mx-x)   gmn(L,i),gmx(R,i);
    }
    if(L>R||chk(L,R,mx-mn-x)<=x)    return true;
    return false;
}
void matt(int _cases){
    mn=1e9;mx=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),gmn(mn,a[i]),gmx(mx,a[i]);
    int l=0,r=1e9,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}