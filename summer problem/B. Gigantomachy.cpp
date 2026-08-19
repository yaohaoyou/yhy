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
int n,m;
int a[maxn],b[maxn];
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);a[n+1]=0;
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);b[m+1]=0;
    ll s=0;
    for(int i=1;i<=n;i++)s+=a[i]-a[i+1]+1;
    for(int i=1;i<=m;i++)s-=b[i]-b[i+1]+1;
    puts(s>=0?"1":"2");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}