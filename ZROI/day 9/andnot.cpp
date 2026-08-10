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
int n;
int a[maxn];
int sum[30];
int main(){
    // freopen("andnot.in","r",stdin);freopen("andnot.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    unsigned ll ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<30;j++)   sum[j]+=bool(a[i]&(1<<j));
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<30;j++){
            sum[j]-=bool(a[i]&(1<<j));
            if(a[i]&(1<<j)) ans+=(1ll<<j)*(n-i-sum[j]);
        }
        // for(int j=i+1;j<=n;j++){
        //     ans+=(a[i]&(~a[j]));
        // }
    }
    printf("%llu\n",ans);
}