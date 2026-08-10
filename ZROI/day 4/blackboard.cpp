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
const int maxn=1e5+10;
int n;
int a[maxn];
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int g=0,mx=0;
    for(int i=1;i<=n;i++)   g=__gcd(g,a[i]),mx=max(mx,a[i]);
    printf("%d\n",mx/g);
}
int main(){freopen("blackboard.in","r",stdin);freopen("blackboard.out","w",stdout);int T;scanf("%d",&T);while(T--)matt();}