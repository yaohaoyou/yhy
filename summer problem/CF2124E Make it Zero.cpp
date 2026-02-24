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
const int maxn=5e4+10;
int n;
ll a[maxn],s[maxn];
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    for(int i=1;i<=n;i++)
        if(s[i]+s[i]==s[n]){
            puts("1");
            for(i=1;i<=n;i++)   printf("%lld ",a[i]);
            puts("");
            return;
        }
    if(s[n]&1)  return puts("-1"),void();
    for(int i=1;i<=n;i++)
        if(a[i]+a[i]>s[n])   return puts("-1"),void();
    for(int i=1;i<=n;i++){
        if(s[i-1]+a[i]>=s[n]-s[i]){
            ll y=(s[i-1]-s[n]+s[i]+a[i])/2,z=a[i]-y;
            puts("2");
            for(int j=1;j<=n;j++){
                if(y){
                    ll t=min((ll)a[j],y);
                    printf("%lld ",t);
                    a[j]-=t;y-=t;
                }
                else if(j==i) printf("%lld ",(s[i-1]-s[n]+s[i]+a[i])/2),a[j]-=(s[i-1]-s[n]+s[i]+a[i])/2;
                else printf("0 ");
            }
            puts("");
            for(int j=1;j<=n;j++)   printf("%lld ",a[j]);puts("");
            return;
        }
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}