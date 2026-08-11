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
const int maxn=1e5+10;
int n;
struct node{int l,r,h;}a[maxn];
bool cov[maxn][2];
void divide(int l,int r){
    int p=0;
    for(int i=l;i<=r;i++)if(cov[])
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].h);
    sort(a+1,a+n+1,[&](node x,node y){return x.l<y.l;});
    divide(1,n);
}