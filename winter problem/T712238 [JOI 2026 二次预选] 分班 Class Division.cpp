#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
int n;
int a[maxn];
map<int,int> mp;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),mp[a[i]]++;
    piii ans=piii(pii(1e9,1e9),1e9);
    int sum=0;
    for(auto [i,j]:mp){
        ans=min(ans,piii(pii(abs(sum-(n-sum)),n-sum),i));
        sum+=j;
    }
    printf("%d\n",ans.se);
}