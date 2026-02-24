#include<bits/stdc++.h>
#define ll long long
#define int long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10;
int n,d;
int a[maxn],sum[maxn],b[maxn];
vector<int> v[maxn];
int q[maxn],hd,en;
bool check(int x){
    for(int i=1;i<=n;i++)v[i].clear(),b[i]=a[i];
    for(int i=1;i<=n;i++){
        b[i]=a[i];
        if(a[i]<=0) continue;
        v[max(1ll,i-x*d)].eb(i);
    }
    hd=1;en=0;
    for(int i=1;i<=n;i++){
        for(int j:v[i]) q[++en]=j;
        while(hd<=en&&q[hd]+x*d<i)  hd++;
        while(hd<=en&&b[i]<0){
            int w=min(b[q[hd]],b[i]);
            b[i]-=w;b[q[hd]]-=w;
            if(!b[q[hd]])   hd++;
            if(!b[i])   break;
        }
        if(b[i]<0)    return false;
    }
    return true;
}
void matt(){
    // st.clear();
    scanf("%lld%lld",&n,&d);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    ll s=accumulate(a+1,a+n+1,0ll)/n;
    printf("s = %d\n",s);
    for(int i=1;i<=n;i++)   a[i]-=s;
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    int ans=0;
    int l=0,r=n;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%lld\n",ans);
}
main(){int T;scanf("%lld",&T);while(T--)matt();}