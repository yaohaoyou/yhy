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
bool mem1;
const int maxn=1e5+10;
int n;
ll a[maxn],b[maxn];
ll f[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&b[i]);
    int mx=max(a[n],b[n]);ll dp=1e18,ans=mx*2-a[1];
    mems(f,0x3f);f[0]=0;
    for(int i=1;i<=n;i++){
        // for(int j=1;j<=i;j++)   gmn(f[i],f[j-1]+max(a[i],b[i])*2+a[i]-a[j-1]-a[j]-a[j]);
        gmn(dp,f[i-1]-a[i-1]-a[i]-a[i]);
        // printf("%lld\n",dp+a[i]+max(a[i],b[i])*2);
        gmn(f[i],max(a[i],b[i])*2+a[i]+dp);
        if(a[i]>=b[i])  gmn(f[i],f[i-1]+a[i]-a[i-1]);
        gmn(ans,f[i]+mx*2-a[i]-a[i+1]);
        // printf("%lld\n",f[i]);
    }
    printf("%lld\n",ans);
}