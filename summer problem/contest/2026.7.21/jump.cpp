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
const int maxn=5e5+10;
int n;
int a[maxn],f[maxn];
stack<int> stk;
int main(){
    freopen("jump.in","r",stdin);freopen("jump.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    a[0]=1e9+1;stk.ep(0);
    for(int i=1;i<=n;i++){
        while(a[stk.top()]<=a[i])    stk.pop();
        f[i]=f[stk.top()]+1;stk.ep(i);
    }
    for(int i=1;i<=n;i++)   printf("%d ",f[i]);
}