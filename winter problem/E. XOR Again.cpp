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
const int maxn=2e6+10,N=1048575;
int n;
int a[maxn];
int fwt[maxn],ans[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),a[i]^=a[i-1];
    for(int i=1;i<=n;i++)   fwt[a[i]]++;
    for(int i=0;i<20;i++)
        for(int j=0;j<=N;j++)if(!(j&(1<<i)))fwt[j|(1<<i)]+=fwt[j];
    mems(ans,0x3f);
    for(int i=0;i<=N;i++)gmn(ans[fwt[i]],i|a[n]);
    for(int i=n-1;i;i--)  gmn(ans[i],ans[i+1]);
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);
}