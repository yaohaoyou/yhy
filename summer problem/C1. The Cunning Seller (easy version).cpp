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
int n;
void matt(){
    scanf("%d",&n);
    ll s=1162261467ll,ans=0;
    for(int i=19;~i;i--,s/=3){
        if(s<=n)    ans+=(n/s)*(s*3+i*s/3),n%=s;
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}