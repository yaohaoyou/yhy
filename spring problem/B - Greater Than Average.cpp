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
ll suf[maxn],pre[maxn];
// bool check(int l,int r){return (pre[l-1])}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=n;i;i--)   suf[i]=suf[i+1]+a[i];
    for(int i=1;i<=n;i++)   pre[i]=pre[i-1]+a[i];
    int ans=0;
    for(int i=1;i<=n;i++){
        double del=1.0*pre[i]/i;
        ans=max(ans,i-int(upper_bound(a+1,a+i+1,del)-a)+1);
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}