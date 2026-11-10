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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
int n,m,q,T;
inline int rd(int l,int r){return rand()%(r-l+1)+l;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    srand(chrono::system_clock::now().time_since_epoch().count());
    n=rand()%100+1;m=rand()%200000+1;q=1;T=rand()%100+1;
    printf("%d %d %d %d\n",n,m,q,T);
    for(int i=2;i<=n;i++)   printf("%d %d\n",i,rd(max(1,i-10),i-1));
    for(int i=1;i<=m;i++){
        printf("%d %d %d\n",rand()%2+1,rand()%n+1,rand()%100000+1);
    }
    while(q--){
        puts("0");
    }
}