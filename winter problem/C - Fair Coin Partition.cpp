#include<bits/stdc++.h>
#define ll long long
#define LL __int128
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
int a[maxn],b[maxn];
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int nd=0;
    bool flag=false;
    for(int i=1;i<=n;i++)   b[i]=b[i-1]/10+a[i];
    for(int i=n;i;i--){
        nd*=10;
        ll now=(b[i]-nd)/m;
        if(now||flag)   printf("%lld",now),flag=true;
        nd+=max(0ll,1ll*now*m-a[i]);
        a[i]-=1ll*now*m;
        if(a[i]>0)  nd-=a[i];
        nd=max(nd,0);
    }
    if(!flag)   printf("0");
    puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}