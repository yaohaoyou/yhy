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
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    frac mx=frac(0,1),mn=frac(1e9,1);
    for(int i=1;i<(1<<n);i++)if(__builtin_popcount(i)>1){
        ll sum=0,cnt=0,w=0;
        for(int j=1;j<=n;j++)if(i&(1<<j-1))sum+=a[j],cnt++;
        for(int j=1;j<=n;j++)if((i&(1<<j-1))&&1ll*a[j]*cnt>sum)w++;
        mn=min(mn,frac(w,cnt));mx=max(mx,frac(w,cnt));
    }
    printf("%d/%d %d/%d\n",mx.p,mx.q,mn.p,mn.q);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}