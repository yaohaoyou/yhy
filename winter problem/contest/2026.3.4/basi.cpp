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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e6+10;
int n,m;
int a[maxn];
void divide(int l,int r){
    if(l==r)    return;
    int mid=(l+r)>>1;
    divide(l,mid);divide(mid+1,r);
    for(int i=l;i<=mid;i++){
        
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    divide(1,n);
}