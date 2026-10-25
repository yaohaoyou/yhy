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
int n;
int a[maxn],b[maxn];
inline ll rd(){return 1ll*rand()*rand();}
int main(){
    srand(chrono::system_clock().now().time_since_epoch().count());
    int V;
    if(rd()&1)  V=10;else V=100;
    n=rd()%V+1;
    printf("%d\n",n);
    while(true){
        for(int i=1;i<=n;i++)   a[i]=rd()%V;
        for(int i=1;i<=n;i++)   b[i]=rd()%V;
        b[n]=accumulate(a+1,a+n+1,0)-accumulate(b+1,b+n,0);
        if(b[n]>=0)break;
    }
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    for(int i=1;i<=n;i++)   printf("%d ",b[i]);puts("");
}