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
const int maxn=210;
ll n;int m;
int a[maxn];
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=100;i++) a[++m]=i;
    int x=1;ll pw=1;
    while(pw*2-1<=n)    a[++m]=(x++)*2,pw*=2;
    n-=pw-1;
    for(int i=39;~i;i--) if(n&(1ll<<i)) a[++m]=i<<1|1;
    printf("%d\n",m);for(int i=1;i<=m;i++) printf("%d ",a[i]);
}