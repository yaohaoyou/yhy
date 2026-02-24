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
const int maxn=1e5+10;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int n;
ll ans;
ll a[maxn],b[maxn];
void divide(int l,int r){
    if(l>=r)    return;
    int mid=(l+r)>>1;
    b[mid]=a[mid];
    vector<int> vec;vec.clear();
    for(int i=mid-1;i>=l;i--){
        b[i]=__gcd(b[i+1],a[i]);
        if(b[i]^b[i+1]) vec.eb(i+1);
    }
    vec.eb(l);
    ll g=0;
    for(int i=mid;i<=r;i++){
        g=__gcd(g,a[i]);
        for(int j:vec)  gmx(ans,__gcd(g,b[j])*(i-j+1));
    }
    divide(l,mid-1);divide(mid+1,r);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    ans=*max_element(a+1,a+n+1);
    divide(1,n);
    printf("%lld\n",ans);
}