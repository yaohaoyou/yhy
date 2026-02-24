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
int n;
inline int calc(ll x){
    int ret=0;
    while(x)ret+=x%10,x/=10;
    return ret;
}
void solve2(){
    ll cc=calc(n);
    for(ll i=1;1;i++){
        if((n-calc(i*n))%cc==0){
            int k=(n-calc(i*n))/cc;
            printf("%lld",i*n);
            while(k--)printf("%d",n);
            puts("");
            return;
        }
    }
}
void matt(int c){
    n=c;
    scanf("%d",&n);
    // solve2();
    ll p=0;
    for(ll i=1;1;i++){
        if(i>100000ll){
            solve2();
            return;
        }
        if(n%calc(i*n)==0){
            p=i*n;break;
        }
    }
    debug("%lld,",p);
    int t=n/calc(p);
    while(t--)  printf("%lld",p);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}