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
const int maxn=2e5+10;
int n,m;
ll a[maxn],b[maxn],c[maxn];
inline bool chk(ll l,ll r,ll x){return !(min(l,r)<=x&&x<=max(l,r));}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    if(m==2){
        for(int i=1;i<=n;i++)if(a[i]^b[i])return puts("-1"),0;
        puts("0");return 0;
    }
    c[1]=b[1];
    for(int i=2;i<=n;i++){
        b[i]+=(c[i-1]-b[i])/m*m;
        for(ll x:{b[i],b[i]-m,b[i]+m}){
            c[i]=x;
            if(abs(c[i]-c[i-1])<m&&((chk(a[i-1],c[i-1],a[i])&&chk(a[i],c[i],c[i-1]))||(chk(a[i],c[i],a[i-1])&&chk(a[i-1],c[i-1],c[i])))) break;
        }
    }
    for(int i=1;i<=n;i++)   a[i]-=c[i];
    ll ans=1e18,sum=0;
    int p=(n+1)/2;nth_element(a+1,a+p,a+n+1);
    ll k=a[p]/m*m;
    for(ll x:{k-m,k-m-m,k,k+m,k+m+m}){
        sum=0;for(int i=1;i<=n;i++)sum+=abs(a[i]-x);gmn(ans,sum);
    }
    p++;
    nth_element(a+1,a+p,a+n+1);
    k=a[p]/m*m;
    for(ll x:{k-m,k-m-m,k,k+m,k+m+m}){
        sum=0;for(int i=1;i<=n;i++)sum+=abs(a[i]-x);gmn(ans,sum);
    }
    printf("%lld\n",ans);
}