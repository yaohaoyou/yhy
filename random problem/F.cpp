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
const int maxn=1010;
int n;
int a[maxn][maxn];
int buc[maxn*maxn];
vector<int> v[maxn];
int main(){
    scanf("%d",&n);const int m=n*n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)buc[i+j]++;
    for(int i=1;i<=m;i++)v[buc[i]].eb(i);
    mems(buc,0);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)buc[a[i][j]]++;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j])
        }
    }
}