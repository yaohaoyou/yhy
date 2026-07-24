#include<bits/stdc++.h>
#define int long long
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
int a[maxn];
void matt(int _cases){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    LL nd=0;int lst;
    bool flag=false;
    // debug("Cases : %d\n",_cases);
    for(int i=n;i;i--){
        // debug("a[%d] = %d,nd = %lld\n",i,a[i],(ll)nd);
        if(i^n){
            LL bs=1,sum=0;
            for(int j=lst;j<i;j++,bs*=10)  sum+=bs*a[j];
            ll cost=max(LL(0),nd-sum+bs-1)/bs;
            a[i]-=cost;nd-=cost*bs;
            // debug("cost = %d %lld\n",cost,(ll)bs);
            if(lst^1)nd*=10;
        }
        // debug("a[%d] = %d,nd = %lld\n",i,a[i],(ll)nd);
        LL sum=-nd,bs=1;
        for(int j=max(1ll,i-10);j<=i;j++,bs*=10)  sum+=bs*a[j];bs/=10;
        lst=max(1ll,i-10);
        ll now=sum/(bs*m);
        if(now<0)while(1);
        if(flag&&now>9)    while(1);
        if(flag||now)   printf("%lld",now),flag=true;
        nd+=max(LL(0),now*bs*m-bs*a[i]);
        ll cost=now*m;a[i]-=cost;
        if(a[i]>0){nd-=a[i]*bs;nd=max(nd,LL(0));a[i]=0;}
    }
    if(!flag)   printf("0");
    puts("");
}
main(){int T;scanf("%lld",&T);for(int i=1;i<=T;i++)matt(i);}