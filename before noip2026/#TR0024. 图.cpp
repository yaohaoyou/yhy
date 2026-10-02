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
bool mem1;
int n;
vector<pii> G0,G1;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    if(n<7) return puts("NO"),0;
    for(int i=1;i<=7;i++)   G0.eb(i,i%7+1),G1.eb(i,i%7+1);
    for(int i=8;i<=n;i++)   G0.eb(i==8?1:i-1,i),G1.eb(i==8?1:i-1,i);
    G0.eb(4,6);G0.eb(2,4);G0.eb(2,7);G0.eb(1,3);
    G1.eb(4,7);G1.eb(2,4);G1.eb(2,6);G1.eb(1,3);
    puts("YES");
    printf("%d\n",G0.size());
    for(auto [i,j]:G0)  printf("%d %d\n",i,j);
    printf("%d\n",G1.size());
    for(auto [i,j]:G1)  printf("%d %d\n",i,j);
}