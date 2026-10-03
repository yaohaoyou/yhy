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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
bool mem1;
int n;
int a[maxn];
ll s[maxn];
bool mem2;
inline ll calc(int l,int r){return l>r?0:s[l]-s[r+1];}
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);n--;
    s[n+1]=0;
    for(int i=n;i;i--)   s[i]=s[i+1]+a[i];
    if(n==1)    return printf("%lld\n",a[1]*2ll),void();
    if(n==2)    return printf("%lld\n",a[1]*3ll+a[2]),void();
    ll ans=s[2]+1ll*a[1]*(n-1);
    for(int i=n;i>=3;i-=3){
        int x=(n-i)/3;
        // printf("[%d,%d] [%d,%d]\n",2,1+x,1+x+1,1+3*x);
        gmn(ans,1ll*a[1]*(i-1)+s[n-i+2]+calc(2,1+x)*2+calc(1+x+1,1+3*x));
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}