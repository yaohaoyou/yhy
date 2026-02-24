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
int n,m;
ll a[maxn],b[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    ll ans=0,lst=0,beg=0,now=m,st=1;
    for(int i=1;i<=m/n;i++){
        lst+=now;now-=n;beg+=st;st+=n;
        // printf("lst = %d\n",lst);
        b[n]=min(lst,a[n]);
        for(int j=n-1;j;j--)    b[j]=min(a[j],b[j+1]-i);
        b[n]=min(b[n],b[1]+m-i);
        ll sum=b[n];
        for(int j=n-1;j;j--)    b[j]=min(a[j],b[j+1]-i),sum+=b[j];
        if(b[1]>=beg)ans=max(ans,sum);
        // ll x=lst-now;
        // for(int j=1;j<=n;j++)   printf("%d ",b[j]);puts("");
        // printf("%d : %d %d %d %d\n",i,b[1],b[n],lst,sum);
    }
    printf("%lld\n",ans);
}