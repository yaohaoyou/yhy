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
int c,x;
bool check(ll n){return n?(n^c)%n==x:false;}
void matt(){
    scanf("%d%d",&c,&x);
    if(check(c^x))  printf("%d\n",c^x);
    else if(check((1ll<<33)+(c-x)/2))  printf("%lld\n",(1ll<<33)+(c-x)/2);
    else puts("-1");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}