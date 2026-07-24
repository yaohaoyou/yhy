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
using namespace std::chrono;
const int maxn=1010;
auto millisec_since_epoch=duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
mt19937 matt(millisec_since_epoch);
mt19937_64 matt64(millisec_since_epoch);
int rd(){return abs(int(matt()));}
int n,m,k;
int a[maxn];
int main(){
    srand(millisec_since_epoch);
    int T=10;
    printf("%d\n",T);
    while(T--){
        n=rd()%100+1;m=rd()%10+1;
        printf("%d %d\n",n,m);
        for(int i=1;i<=n;i++) printf("%d ",rd());puts("");
    }
}