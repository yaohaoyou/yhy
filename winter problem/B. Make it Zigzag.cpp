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
int n;
int a[maxn];
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int mx=0;
    for(int i=1;i<=n;i++){
        mx=max(mx,a[i]);
        if(!(i&1))  a[i]=mx;
    }
    ll ans=0;
    a[0]=1e9;
    for(int i=1;i<=n;i++){
        if(i&1){
            ans+=max(0,a[i]-a[i-1]+1);a[i]=min(a[i],a[i-1]-1);
            if(i<n&&a[i]==a[i+1])    ans++;
        }
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}