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
const int maxn=4e5+10;
int n;unsigned seed;
pii a[maxn];
int w[maxn];
unsigned get(unsigned &x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x % 1000;
}
void matt(){
    for(int i=1;i<=n;i++)   w[i]=get(seed);
    
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    int q;
    scanf("%d%u",&q,&seed);
    while(q--)matt();
}