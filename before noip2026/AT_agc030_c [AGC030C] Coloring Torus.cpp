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
bool mem1;
const int maxn=510;
int n,k;
int a[maxn][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&k);
    if(k<=500){
        printf("%d\n",k);
        for(int i=1;i<=k;i++,puts(""))for(int j=1;j<=k;j++)printf("%d ",i);
        return 0;
    }
    n=(k+3)/4*2;
    printf("%d\n",n);
    for(int i=0;i<n;i++,puts("")){
        for(int j=0;j<n;j++){
            int c=(i+j)%n+1;
            if((i&1)&&c+n<=k)  c+=n;
            printf("%d ",c);
        }
    }
}