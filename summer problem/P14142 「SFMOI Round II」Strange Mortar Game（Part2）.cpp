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
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        if(i%3==1) printf("%d %d %d %d\n",i,n-1,i,n-1);
        else if(i%3==2) printf("%d %d %d %d\n",i,2,i,n-1);
        else if(i+3<=n) printf("%d %d %d %d\n",i,2,i,2);
        else printf("%d %d %d %d\n",i,1,i,1);
    }
}