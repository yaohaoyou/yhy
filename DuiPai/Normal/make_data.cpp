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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
int V=100;
int n;
int a[maxn];
inline ll rd(){return 1ll*rand()*rand();}
int main(){
    srand(chrono::system_clock::now().time_since_epoch().count());
    n=rd()%5+1;int q=1000;
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++)   printf("%d ",rd()%1000);puts("");
    while(q--){
        int l=rd()%n+1,r=rd()%n+1;
        if(l>r)swap(l,r);
        printf("%d %d\n",l,r);
    }
}