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
int n,p,m;
int d[maxn],t[maxn];
int main(){
    scanf("%d%d%d",&n,&p,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&d[i],&t[i]);
    d[0]=1;d[n+1]=m+1;
    ll now=0,ans=0;
    for(int i=0;i<=n;i++){
        // printf("now = %d\n",now);
        now+=t[i];
        ans+=max(0ll,d[i+1]-d[i]-max(0ll,now/p));
        now-=1ll*(d[i+1]-d[i])*p;
    }
    printf("%lld\n",ans);
}