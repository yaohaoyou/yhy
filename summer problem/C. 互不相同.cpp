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
const int maxn=2e5+10;
int n;
map<int,int> mp;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);mp[x]++;}
    int ans=0;
    for(auto [i,j]:mp)  ans=max(ans,int(ceil(log10(j)/log10(2))));
    printf("%d\n",ans);
}
// 1 1 1 1 1 1 1
// 1 1 1 a a a a
// 1 b b a a a+b a+b
// 1 b c a+c a a+b+c a+b