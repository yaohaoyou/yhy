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
int n,k;
int a[maxn];
void matt(){
    scanf("%d%d",&n,&k);
    if(!k){
        if(n<8)    puts("-1");
        else{
            printf("6 5 1 2 7 8 4 3 ");
            for(int i=9;i<=n;i++)   printf("%d ",i);puts("");
        }
        return;
    }
    if(k==1){
        if(n==1)    puts("1");
        else if(n<=4)    puts("-1");
        else{
            printf("4 1 3 5 2 ");
            for(int i=6;i<=n;i++)   printf("%d ",i);
            puts("");
        }
        return;
    }
    if(n==k){
        for(int i=1;i<=n;i++)  printf("%d ",i);puts("");
        return;
    }
    for(int i=2;i<=k+1;i++)   printf("%d ",i);
    printf("1 ");
    for(int i=k+2;i<=n;i++) printf("%d ",i);
    puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}