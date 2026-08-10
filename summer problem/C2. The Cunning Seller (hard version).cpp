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
int n,k;
inline ll calc(ll x,int p){
    ll s=1162261467ll,ans=0;ll c=0;
    for(int i=19;i>=p;i--,s/=3);
    for(int i=p-1;~i;i--,s/=3){
        if(s<=x)    ans+=(x/s)*(s*3+i*s/3),c+=x/s,x%=s;
    }
    return x?1e9+10:c;
}
void matt(){
    scanf("%d%d",&n,&k);
    if(calc(n,20)>k)   return puts("-1"),void();
    ll s=1162261467ll,ans=0;ll c=0;
    for(int i=19;~i;i--,s/=3){
        if(s>n) continue;
        ll l=0,r=n/s,p=-1;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(calc(n-s*mid,i)+mid+c<=k)  p=mid,r=mid-1;
            else    l=mid+1;
        }
        // printf("%d %d %d %d : %d\n",n,p,s,ans,calc(n-p*s,i));
        ans+=p*(s*3+i*s/3);c+=p;n-=p*s;
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}