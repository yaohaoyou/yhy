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
const int maxn=1e6+10;
int n,cnt;
int a[maxn],b[maxn];
int buc[maxn],lst[maxn];
ll sum[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=n;i;i--)
        if(!lst[a[i]])  lst[a[i]]=i;
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(lst[a[i]]==i)    ans+=sum[a[i]];
        cnt+=(!buc[a[i]]);
        buc[a[i]]++;
        b[i]=cnt-1;
        sum[a[i]]=b[i];
    }
    printf("%lld\n",ans);
}