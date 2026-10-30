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
mt19937 matt(chrono::system_clock::now().time_since_epoch().count());
inline int rd(){return abs(int(matt()));}
int n,q;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=rd()%10+1;q=rd()%10+1;printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++){
    	int len=rd()%10+1;
    	while(len--)putchar(rd()%4+'a');
    	printf(" %d\n",rd()%1000);
    }
    while(q--){
    	int len=rd()%10+1;
    	while(len--)putchar(rd()%4+'a');
    	printf(" %d\n",rd()%n+1);
    }
}