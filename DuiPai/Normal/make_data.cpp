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
int a[maxn];
inline ll rd(){return 1ll*rand()*rand();}
int main(){
    srand(chrono::system_clock::now().time_since_epoch().count());
    if(rand()&1)n=rd()%20+1;
    else    n=rd()%1000+1;
    printf("%d %d\n",n,rd()%1001);
    for(int i=2;i<=n;i++)   printf("%d %d\n",rd()%(i-1)+1,i);
}