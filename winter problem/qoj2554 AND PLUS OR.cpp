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
const int maxn=25,maxN=(1<<20)+10;
int n,m;
int a[maxN];
int main(){
    scanf("%d",&n);m=1<<n;
    for(int i=0;i<m;i++)    scanf("%d",&a[i]);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i&(1<<j))    continue;
            for(int k=0;k<n;k++){
                if((i&(1<<k))||j==k)    continue;
                int x=i|(1<<j),y=i|(1<<k);
                if(a[x]+a[y]<a[x&y]+a[x|y]) return printf("%d %d\n",x,y),0;
            }
        }
    }
    puts("-1");
}