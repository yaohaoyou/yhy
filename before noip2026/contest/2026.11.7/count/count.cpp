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
ll a[3];int n;
inline ll sqr(int x){return 1ll*x*x;}
bool mem2;
void matt(int _cases){
    scanf("%lld%lld%lld%d",&a[0],&a[1],&a[2],&n);
    sort(a,a+3);
    if(n<=3){
        ll ans=0;
        for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)for(int k=0;i+j+k<=n;k++)
            gmx(ans,sqr(a[0]+i)+sqr(a[1]+j)+sqr(a[2]+k)+7*min({a[0]+i,a[1]+j,a[2]+k}));
        printf("%lld\n",ans);
    }
    else    printf("%lld\n",sqr(a[0])+sqr(a[1])+sqr(a[2]+n)+a[0]*7);
}
int main(){freopen("count.in","r",stdin);freopen("count.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}