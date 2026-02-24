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
const int maxn=1610,mod=1e9+7;
int n,k;
int a[maxn];
bool check()
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    int x=0;
    for(int i=k;i;i--)  x=x<<1|a[i];
    if(check(x)){

    }
}