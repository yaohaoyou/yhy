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
const int maxn=5e5+10;
bool mem1;
int n;
int a[maxn];
ll s[maxn];
struct frac{
    int p,q;
    frac(int _p=0,int _q=0){p=_p;q=_q;int g=__gcd(p,q);if(g)p/=g,q/=g;}
    bool operator<(frac y)const{return 1ll*p*y.q<1ll*q*y.p;}
};
bool mem2;
int main(){
    srand(chrono::system_clock::now().time_since_epoch().count());
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=100;printf("%d\n",T);
    while(T--){
        n=rand()%20+2;printf("%d\n",n);
        for(int i=1;i<=n;i++)printf("%d ",rand()%100+1);puts("");
    }
}