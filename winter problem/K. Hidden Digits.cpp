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
int n;
inline int ask(int x){printf("? %d\n",x);fflush(stdout);scanf("%d",&x);return x;}
int main(){
    scanf("%d",&n);
    if(n==1){
        int x=ask(1);
        printf("! %d\n",x%3==0);
    }
    else if(n==2){
        int x=ask(1),y=ask(2);
        if(x%3==0||y%3==0||(x+y)%3==0)printf("! 1");
        else printf("! 0");
    }
    else printf("! 1");
    fflush(stdout);
}