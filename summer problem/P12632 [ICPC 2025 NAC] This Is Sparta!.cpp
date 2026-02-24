#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n;ll k;
ll a[maxn];
int main(){
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    int c=1;
    sort(a+c,a+n+1);
    while(k--){
        for(int i=c;i<=n;i++)   a[i]-=a[i-1];
        if(k)sort(a+c,a+n+1);
        while(c<=n&&!a[c]) c++;
        if(n-c+1<=3)    break;
    }
    if(k&&n-c+1==3){
        sort(a+1,a+n+1);
        ll x=a[n-2],y=a[n-1],z=a[n];
        while(k>0){
            ll l=1,r=k,p=0;
            while(l<=r){
                ll mid=(l+r)>>1;
                if(y-LL(x)*mid>=x&&z-LL(y)*mid+LL(mid)*(mid+1)/2*x>=y)  p=mid,l=mid+1;
                else r=mid-1;
            }
            // printf("p = %lld\n",p);
            k-=p;z-=y*p-p*(p+1)/2*x;y-=x*p;
            if(k){y-=x;z-=y;k--;}
            if(!k)  break;
            if(y>z)swap(y,z);if(x>y)swap(x,y);
            if(!x)  break;
            // exit(0);
        }
        // printf("%d %d %d %lld\n",x,y,z,k);
        a[n-2]=x;a[n-1]=y;a[n]=z;
        if(!a[n-2]) c++;
    }
    if(k&&n-c+1==2){
        sort(a+1,a+n+1);
        ll x=a[n-1],y=a[n];
        while(true){
            if(y/x<k)  k-=y/x,y%=x,swap(x,y);
            else y-=k*x,k=0;
            if(!x||!y||!k)  break;
        }
        a[n-1]=x;a[n]=y;
    }
    for(int i=1;i<=n;i++)   printf("%lld ",a[i]);puts("");
}