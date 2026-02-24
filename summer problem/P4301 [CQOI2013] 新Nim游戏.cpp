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
const int maxn=110;
int n;ll sum;
int a[maxn];
struct Linear_basis{
    int p[32];
    void ins(int x){
        int X=x;
        for(int i=31;~i;i--){
            if(!(x&(1<<i))) continue;
            if(!p[i])   return p[i]=x,sum-=X,void();
            x^=p[i];
        }
    }
}L;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;i++)sum+=a[i];
    for(int i=1;i<=n;i++)   L.ins(a[i]);
    printf("%lld\n",sum);
}